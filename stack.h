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

    // Some strange code:)
    Stack(const Stack& s) : nodeAllocator(s.nodeAllocator), head(nullptr) {
        Stack tmp;
        for(Node* it = s.head; it; it = it->next) {
            tmp.push(it->elem);
        }
        for(; !tmp.empty(); tmp.pop()) {
            push(tmp.top());
        }
    }

    Stack(Stack&& s) 
        : nodeAllocator(std::move(s.nodeAllocator)), head(s.head) 
    {
        s.head = nullptr;
    }

    void push(const T& elem) {
        Node* pNode = nodeAllocator.allocate(1); 
        nodeAllocator.construct(pNode, elem, head);
        head = pNode;
    }

    void push(T&& elem) {
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