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

template<typename M> 
void fill(M* map, int n) {
    for(int i = 0; i < n; i++) {
        (*map)[i] = factorial(i);
    }
}

template<typename M>
void print(const M& map) {
    for(auto p : map) {
        std::cout << p.first << " " << p.second << std::endl;
    }
}

int main() {

    std::map<int, int> map;
    fill(&map, 10);
    // print(map);

    std::map<int, int, 
        std::less<int>, 
        StackAllocator< std::pair<const int, int>, 10 >
    > map_alloc;

    fill(&map_alloc, 10);
    std::cout << "std::map with my allocator:" << std::endl;
    print(map_alloc);

    Stack<int> stack;
    for(int i = 0; i < 10; i++) {
        stack.push(i);
    }

    Stack<int, StackAllocator<int, 10>> stack_alloc;
    for(int i = 0; i < 10; i++) {
        stack_alloc.push(i);
    }

    std::cout << "my stack with my allocator:" << std::endl;
    while(!stack_alloc.empty()) {
        std::cout << stack_alloc.top() << " ";
        stack_alloc.pop();
    }
    std::cout << std::endl;
    
    return 0; 
}