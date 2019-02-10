#include <cstdlib>
#include <new>
#include <utility>


template<typename T, std::size_t N>
class StackAllocator {

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
        using other = StackAllocator<U, N>;
    };

    StackAllocator() { 
        reserve(N); 
    }

    T* allocate(std::size_t n) {
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
