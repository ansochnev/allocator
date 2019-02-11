#include <cassert>
#include "alloc.h"

int main() {
    StackAllocator<int> alloc(3);
    
    int* p = alloc.allocate(3);

    alloc.construct<int, int>(p, 28);
    alloc.construct<int, int>(++p, 42);
    alloc.construct<int, int>(++p, 13);
    
    assert(*p-- == 13);
    assert(*p-- == 42);
    assert(*p == 28);

    p += 2;

    alloc.destroy(p);
    alloc.deallocate(p, 1);

    alloc.allocate(1);
    alloc.construct(p, 35);

    assert(*p == 35);

    alloc.destroy(p--);
    alloc.destroy(p--);
    alloc.destroy(p);

    alloc.deallocate(p, 3);

    p = alloc.allocate(1);
    alloc.construct<int, int>(p, 100);

    assert(*p == 100);
}