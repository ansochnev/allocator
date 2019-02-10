#include <cassert>
#include "stack.h"

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

    return 0;
}