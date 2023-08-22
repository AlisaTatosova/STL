#include <iostream>

template <typename T>
class ForwardList {
private:
    struct Node {
        T value;
        Node* next;
        Node(const T& val) : value(val), next(nullptr) {}
        Node() : value{}, next(nullptr) {}
    };
public:
    ForwardList() : size(0) {
        head = new Node();
    }

    ~ForwardList() {
        clear();
        delete head;
    }

    void push_back(const T& val) {
        Node* new_node = new Node(val);
        Node* curr = head;
        while (curr -> next) {
            curr = curr -> next;
        }
        curr -> next = new_node;
        size++;
    }

    void pop_back() {
        if (size == 0) {
            return;
        }

        Node* curr = head;
        while (curr -> next -> next) {
            curr = curr -> next;
        }
        delete curr -> next;
        curr -> next = nullptr;
        size--;
    }

    void clear() {
        Node* curr = head -> next;
        while (curr) {
            Node* temp = curr;
            curr = curr -> next;
            delete temp;
        }
        head -> next = nullptr;
        size = 0;
    }

    void insert(size_t pos, const T& val) {
        if (pos > size) {
            return;
        }

        Node* new_node = new Node(val);
        Node* curr = head;
        while (pos) {
            curr = curr -> next;
            --pos;
        }
        new_node -> next = curr -> next;
        curr -> next = new_node;
        size++;
    }

    void reverse_list() {
        Node* reversed = nullptr;
        Node* curr = head -> next;
        while (curr) {
            Node* tmp = curr -> next;
            curr -> next = reversed;
            reversed = curr;
            curr = tmp;
        }
        head -> next = reversed;
    }

    Node* merge_two_lists(Node* list1, Node* list2) {
        if (!list1) {
            return list2;
        }
        else if (!list2) {
            return list1;
        }
        if (list1 -> value < list2 -> value) {
            list1 -> next = merge_two_lists(list1 -> next, list2);
            return list1;
        }
        else {
            list2 -> next = merge_two_lists(list1, list2 -> next);
            return list2;
        }
    }

    void merge(ForwardList& other) {
        head -> next = merge_two_lists(head -> next, other.head -> next); 
        size += other.size;
    }

    Node* sort_lists(Node* head) {
        if (!head || !head -> next) {
            return head;
        }
        Node* slow = head;
        Node* fast = head -> next;
        while (fast && fast -> next) {
            slow = slow -> next;
            fast = fast -> next -> next;
        }
        fast = slow -> next;
        slow -> next = nullptr;
        Node* left = sort_lists(head);
        Node* right = sort_lists(fast);
        return merge_two_lists(left, right);
    }

    void sort() {
        head -> next = sort_lists(head -> next);
    }

    void print() {
        Node* curr = head -> next;
        while (curr) {
            std::cout << curr -> value << " ";
            curr = curr -> next;
        }
        std::cout << std::endl;
    }

private:
    Node* head;
    size_t size;
};

int main() {
    ForwardList<int> list;
    list.push_back(3);
    list.push_back(2);
    list.push_back(4);
    list.push_back(5);

    std::cout << "Forward List before reverse: " << std::endl;
    list.print();

    list.reverse_list();
    std::cout << "Forward List after reverse: " << std::endl;
    list.print();

    return 0;
}
