#include <functional>

template<typename T, typename Allocator = std::allocator<T>>
class Stack {

private:
    struct Node {
        T elem;
        Node* next;

        Node(T elem, Node* next) : elem(elem), next(next) {}
    };

    // Some kind of magic.
    using NodeAllocator = typename Allocator::template rebind<Node>::other;
    
    NodeAllocator nodeAllocator;
    Node* head;

public:
    Stack() : head(nullptr) {}
    
    Stack(const Allocator& alloc) : nodeAllocator(alloc), head(nullptr) {}

    void push(T elem) {
        Node* pNode = nodeAllocator.allocate(1); 
        nodeAllocator.construct(pNode, elem, head);
        head = pNode;
    }

    void pop() {
        if(!head) {
            throw "pop: empty stack";
        }
        Node* next = head->next;
        nodeAllocator.destroy(head);
        nodeAllocator.deallocate(head, 1);
        head = next;
    }

    const T& top() const {
        if(!head) {
            throw "top: empty stack";
        }
        return head->elem;
    }

    bool empty() const {
        return !head;
    }

    ~Stack() {
        while(head) pop();
    }
};