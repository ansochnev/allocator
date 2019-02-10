#include <iostream>
#include <map>
#include <functional>
#include <utility>

#include "alloc.h"


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
        Allocator< std::pair<const int, int>, 10 >
    > map_alloc;

    fill(&map_alloc, 10);
    std::cout << "std::map with my allocator:" << std::endl;
    print(map_alloc);
    
    return 0; 
}