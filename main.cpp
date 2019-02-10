#include <iostream>
#include <map>
#include <functional>
#include <utility>

#include "alloc.h"
#include "stack.h"


int factorial(int n) {
    if(n == 0) {
        return 1;
    }
    return n * factorial(n - 1);
}

template<typename... Types> 
void fill(std::map<Types...>* map, int n) {
    for(int i = 0; i < n; i++) {
        (*map)[i] = factorial(i);
    }
}

template<typename... Types>
void print(const std::map<Types...>& map) {
    for(auto p : map) {
        std::cout << p.first << " " << p.second << std::endl;
    }
}

template<typename... Types> 
void fill(Stack<Types...>* stack, int n) {
    for(int i = 0; i < n; i++) {
        stack->push(i);
    }
}

template<typename... Types>
void print(Stack<Types...>* stack) {
    while(!stack->empty()) {
        std::cout << stack->top() << " ";
        stack->pop();
    }
    std::cout << std::endl;
}

int main() {

    const int n = 10;

    std::map<int, int> map;
    fill(&map, n);
    // print(map);

    std::map<int, int, 
        std::less<int>, 
        StackAllocator< std::pair<const int, int>, n >
    > map_alloc;

    fill(&map_alloc, n);
    std::cout << "std::map with my allocator:" << std::endl;
    print(map_alloc);

    Stack<int> stack;
    fill(&stack, n);
    // print(&stack);

    Stack<int, StackAllocator<int, n>> stack_alloc;
    fill(&stack_alloc, n);
    std::cout << "my stack with my allocator:" << std::endl;
    print(&stack_alloc);
    
    return 0; 
}