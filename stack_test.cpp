#include <cassert>
#include "stack.h"

void testCopy();
void testMove();

int main() {

    Stack<int> stack;

    assert(stack.empty());
    
    stack.push(1);
    stack.push(2);
    stack.push(3);
    stack.push(4);

    assert(!stack.empty());
    assert(stack.top() == 4);

    stack.pop();
    stack.pop();

    assert(stack.top() == 2);

    stack.pop();
    stack.pop();

    assert(stack.empty());

    testCopy();
    testMove();

    return 0;
}

template<typename T>
void compare(Stack<T>* s, Stack<T>* cp) {
    while(!s->empty()) {
        assert(cp->top() == s->top());
        cp->pop();
        s->pop();
    }
}

void testCopy() {
    Stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);

    auto cp(s);
    compare(&s, &cp);
}

struct Elem {
    int *ptr;

    Elem(int i) : ptr(new int(i)) {}
    
    Elem(const Elem& e) : ptr(new int(*e.ptr))  {}
    
    Elem(Elem&& e) : ptr(e.ptr) { e.ptr = nullptr; }
    
    bool operator== (const Elem& e) const { return *ptr == *e.ptr; }
    
    ~Elem() { delete ptr; }
};

void testMove() {
    Stack<Elem> s, empty;
    s.push(Elem(1));
    s.push(Elem(2));
    s.push(Elem(3));

    auto cp(s);
    auto rcp(std::move(s));
    compare(&rcp, &cp);
    compare(&s, &empty);
}
