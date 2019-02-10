#include <cstdlib>
#include <new>
#include <utility>


template<typename T, std::size_t N>
class Allocator {

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
        using other = Allocator<U, N>;
    };

    Allocator() : buffer(nullptr), offset(nullptr) {}

    T* allocate(std::size_t n) {
        if(!buffer) {
            reserve(N);
        }
        if(offset + n > buffer + N) {
            throw std::bad_alloc();
        }
        auto p = offset;
        offset += n;        
        return reinterpret_cast<T*>(p);
    }

    void deallocate(T* p, std::size_t n) {
        if(p == buffer) {
            std::free(buffer);
            buffer = nullptr;
            return;
        }
        offset -= n;
    }

    template<class U, class... Args>
    void construct(U* p, Args&&... args) {
        new(p) U(std::forward<Args>(args)...);
    }

    template<class U>
    void destroy(U* p) {
        p->~U();
    }
};
