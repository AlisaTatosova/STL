// #include "forward_list.h"
// #include <stdexcept>
// #include <iostream>

// template <typename T>
// List<T>::Iterator::Iterator(Node* node) : node_(node) {}

// template <typename T>
// T& List<T>::Iterator::operator*() {
//     return node_ -> value_;
// }

// template <typename T>
// typename List<T>::Iterator& List<T>::Iterator::operator++() {
//     node_ = node_ -> next_;
//     return *this;
// }

// template <typename T>
// typename List<T>::Iterator List<T>::Iterator::operator++(int) {
//     Iterator tmp = *this;
//     ++*this;
//     return tmp;
// }

// template <typename T>
// bool List<T>::Iterator::operator!=(const Iterator& other) const {
//     return !(*this == other);
// }

// template <typename T>
// bool List<T>::Iterator::operator==(const Iterator& other) const {
//     return node_ == other.node_;
// }


// template <typename T>
// List<T>::List() : head_(nullptr), size_(0) {}

// template <typename T>
// List<T>::List(std::size_t size) : size_(size) {
//     head_ = nullptr;
//     Node* curr = head_;
//     for (std::size_t i = 0; i < size; ++i) {
//         if (!head_) {
//             head_ = new Node();
//             curr = head_;
//         } else {
//             head_ -> next_ = new Node();
//             head_ = head_ -> next_;
//         }
//     }
//     head_ = curr;
// }

// template <typename T>
// List<T>::List(std::size_t size, const T& val) : size_{size} {
//     head_ = nullptr;
//     Node* curr = head_;
//     for (std::size_t i = 0; i < size; ++i) {
//         if (!head_) {
//             head_ = new Node(val);
//             curr = head_;
//         } else {
//             head_ -> next_ = new Node(val);
//             head_ = head_ -> next_;
//         }
//     }
//     head_ = curr;
// }

// template <typename T>
// List<T>::~List() {
//     clean();
// }

// template <typename T>
// void List<T>::push_front(const T& value) {
//     Node* new_node = new Node(value);
//     if (!head_) {
//         head_ = new_node;
//     } else {
//         new_node -> next_ = head_;
//         head_ = new_node;
//     }
//     ++size_;
// }

// template <typename T>
// void List<T>::push_back(const T& value) {
//     Node* new_node = new Node(value);

//     if (!head_) {
//         head_ = new_node;
//     } else {
//         Node* current = head_;
//         while (current -> next_) {
//             current = current -> next_;
//         }
//         current -> next_ = new_node;
//     }
//     ++size_;
// }

// template <typename T>
// void List<T>::pop_back() {
//     if (!head_) {
//         throw std::runtime_error("Forward List is empty. Cannot pop.");
//     }

//     if (!head_ -> next_) {
//         delete head_;
//         head_ = nullptr;
//     } else {
//         Node* current = head_;
//         while (current -> next_ -> next_) {
//             current = current -> next_;
//         }
//         delete current -> next_;
//         current -> next_ = nullptr;
//     }
//     --size_;
// }

// template <typename T>
// void List<T>::insert(const Iterator& it, const T& value) {
//     if (it == begin()) {
//         push_front(value);
//     }
//     else if (it == end()) {
//         push_back(value); 
//     }
//     else {
//         Node* new_node = new Node(value);
//         Node* curr = head_;
//             while (curr && curr -> next_ != it.node_) {
//             curr = curr -> next_;
//         }

//         if (curr) {
//             new_node -> next_ = curr -> next_;
//             curr -> next_ = new_node;
//         }
//     }

//     ++size_;
// }

// template <typename T>
// void List<T>::pop_front() {
//     if (!head_) {
//         throw std::runtime_error("Forward List is empty. Cannot pop.");
//     }

//     Node* next = head_ -> next_;
//     delete head_;
//     head_ = next;
//     --size_;
// }

// template <typename T>
// void List<T>::erase(const Iterator& it) {
//     if (it == begin()) {
//         pop_front();
//     }
//     else if (it == end()) {
//         pop_back();
//     }
//     else {
//         Node* current = head_;
//         while (current && current -> next_ != it.node_) {
//             current = current -> next_;
//         }

//         if (current) {
//             current -> next_ = it.node_ -> next_;
//             delete it.node_;
//             --size_;
//         }
//     }    
// }

// template <typename T>
// void List<T>::reverse() {
//     Node* reversed = nullptr;
//     Node* curr = head_;
//     while (curr) {
//         Node* tmp = curr -> next_;
//         curr -> next_ = reversed;
//         reversed = curr;
//         curr = tmp;
//     }
//     head_ = reversed;
// }

// template <typename T>
// typename List<T>::Node* List<T>::merge_two_lists(Node* list1, Node* list2) {
//     if (!list1) {
//         return list2;
//     }
//     if (!list2) {
//         return list1;
//     }
//     if (list1 -> value_ < list2 -> value_) {
//         list1 -> next_ = merge_two_lists(list1 -> next_, list2);
//         return list1;
//     }
//     else {
//         list2 -> next_ = merge_two_lists(list1, list2 -> next_);
//         return list2;
//     }
// }

// template <typename T>
// void List<T>::merge(List& other) {
//     head_ = merge_two_lists(head_, other.head_); 
//     size_ += other.size_;
// }

// template <typename T>
// typename List<T>::Node* List<T>::sort_lists(Node* head) {
//     if (!head || !head -> next_) {
//         return head;
//     }
//     Node* slow = head;
//     Node* fast = head -> next_;
//     while (fast && fast -> next_) {
//         slow = slow -> next_;
//         fast = fast -> next_ -> next_;
//     }
//     fast = slow -> next_;
//     slow -> next_ = nullptr;
//     Node* left = sort_lists(head);
//     Node* right = sort_lists(fast);
//     return merge_two_lists(left, right);
// }

// template <typename T>
// void List<T>::sort() {
//     head_ = sort_lists(head_);
// }


// template <typename T>   
// void List<T>::clean() {
//     while (head_) {
//         Node* curr = head_ -> next_;
//         delete head_;
//         head_ = curr;
//     }
//     size_ = 0;
// }

// template <typename T>
// std::size_t List<T>::size() const {
//     return size_;
// }

// template <typename T>
// void List<T>::print() {
//     Node* it = head_;
//     while (it != nullptr) {
//         std::cout << it -> value_ << " ";
//         it = it -> next_;
//     }
//     std::cout << std::endl;
// }

// template <typename T>
// typename List<T>::Iterator List<T>::begin() {
//     return Iterator(head_);
// }

// template <typename T>
// typename List<T>::Iterator List<T>::end() {
//     return Iterator(nullptr);
// }