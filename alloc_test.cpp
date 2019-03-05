#include <cassert>
#include "alloc.h"

void testCopy();
void testMove();

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

    testCopy();
    testMove();
}

void catchExcepton(StackAllocator<int>* alloc) {
    bool caught = false;
    try{
        alloc->allocate(1);
    }
    catch(...) {
        caught = true;
    }
    assert(caught);
}

void testCopy() {
    StackAllocator<int> alloc(2);
    alloc.allocate(2);
    catchExcepton(&alloc);
    auto a(alloc);
    a.allocate(2);
}

void testMove() {
    StackAllocator<int> alloc(2);
    int* p = alloc.allocate(2);
    alloc.construct<int, int>(p, 28);
    
    auto a(std::move(alloc));
    
    catchExcepton(&a);
    alloc.allocate(2);
    assert(*p == 28);
}