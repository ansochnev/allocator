#include <cstdlib>
#include <new>
#include <utility>

// Default number of allocated objects.
#define DEFAULT_N 10


// It is need to make size of an allocator a runtime parameter.
// It is called Arena, but actually it is only a set of shared 
// parameters for different instantiations of StackAllocator.
class Arena {
protected:
    // void* buffer;
    // void* offset;
    std::size_t N;

public:
    Arena(std::size_t n) : N(n) {}

    Arena(const Arena& a) {
        N = a.N;
    }
};


template<typename T>
class StackAllocator : public Arena {

private:
    T* buffer;
    T* offset;

    void reserve(std::size_t n) {
        auto p = std::malloc(n * sizeof(T));
        if(!p) {
            throw std::bad_alloc();
        }
        buffer = reinterpret_cast<T*>(p);
        offset = buffer;    
    }

public:
    using value_type = T;

    template<typename U>
    struct rebind {
        using other = StackAllocator<U>;
    };

    StackAllocator() 
        : Arena(DEFAULT_N), buffer(nullptr), offset(nullptr) {}

    StackAllocator(std::size_t n) 
        : Arena(n), buffer(nullptr), offset(nullptr) {}

    // This constructor is need to be used by std::map(const Allocator& alloc)
    // It looks strange, so use the constructor defined bellow.
    // template<typename U>
    // StackAllocator(const StackAllocator<U>& u) {}
    StackAllocator(const Arena& a)
        : Arena(a), buffer(nullptr), offset(nullptr) {}


    T* allocate(std::size_t n) {
        if(!buffer) {
            reserve(N);
        }
        if(offset + n > buffer + N) {
            throw std::bad_alloc();
        }
        T* p = offset;
        offset += n;        
        return p;
    }

    void deallocate([[maybe_unused]] T* p, std::size_t n) {
        if(offset > buffer) {
            offset -= n;
        }
    }

    template<class U, class... Args>
    void construct(U* p, Args&&... args) {
        new(p) U(std::forward<Args>(args)...);
    }

    template<class U>
    void destroy(U* p) {
        p->~U();
    }


    ~StackAllocator() {
        while(offset-- > buffer) {
            destroy(offset);
        }
        std::free(buffer);
    }
};
