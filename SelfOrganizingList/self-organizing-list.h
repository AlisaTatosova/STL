#ifndef SELF_ORGANIZING_LIST_H
#define SELF_ORGANIZING_LIST_H
#include <iostream>

template <typename T>
class SelfOrganizingList {
private:
    struct Node {
        Node() 
            : m_next{nullptr}
            , m_prev{nullptr}
            , m_asc{nullptr}
            , m_desc{nullptr} {}
        explicit Node(const T& value)
            : m_value{value}
            , m_next{nullptr}
            , m_prev{nullptr}
            , m_asc{nullptr}
            , m_desc{nullptr} {}

        T m_value;
        Node* m_next;
        Node* m_prev;
        Node* m_asc;
        Node* m_desc;
    };

    Node* m_head;
    Node* m_tail;
    Node* m_asc_head;
    Node* m_desc_head;
    std::size_t m_size;

public:
    SelfOrganizingList() 
        : m_head{nullptr}
        , m_tail{nullptr}
        , m_asc_head{nullptr}
        , m_desc_head{nullptr}
        , m_size{0} {}

    ~SelfOrganizingList() {
        clear();
    }

public:
    void push_back(const T& val) {
        Node* new_node = new Node(val);
        if (!m_tail) {
            m_head = new_node;
            m_tail = new_node;
        } else {
            Node* tmp = m_tail;
            tmp -> m_next = new_node;
            new_node -> m_prev = tmp;
            m_tail = new_node;
        }
        ++m_size;
        put_in_sorted_order(new_node);
    }

    void push_front(const T& val) {
        Node* new_node = new Node(val);
        if (!m_head) {
            m_head = new_node;
            m_tail = new_node;
        } else {
            Node* tmp = m_head;
            new_node -> m_next = tmp;
            tmp -> m_prev = new_node;
            m_head = new_node;
        }
        ++m_size;
        put_in_sorted_order(new_node);
    }

    void pop_back() {
        if (!m_head) {
            throw std::runtime_error("There is no element in list.");
        } 
        Node* tmp = nullptr;
        if (m_head == m_tail) {
            tmp = m_head;
            m_head = nullptr;
            m_tail = nullptr;
        } else {
            tmp = m_tail;
            Node* node = m_tail -> m_prev;
            m_tail = node;
        }
        --m_size;
        remove_from_sorted_order(tmp);
        delete tmp;
    }

    void pop_front() {
        if (!m_head) {
            throw std::runtime_error("There is no element in list.");
        } 
        
        Node* tmp = nullptr;
        if (m_head == m_tail) {
            tmp = m_head;
            m_head = nullptr;
            m_tail = nullptr;
        } else {
            tmp = m_head;
            Node* node = m_head -> m_next;
            m_head = node;
        }
        --m_size;
        remove_from_sorted_order(tmp);
        delete tmp;
    }

    void erase(const std::size_t pos) {
        if (pos < 0 || pos >= m_size) {
            throw std::out_of_range("Invalid postion");
        } else if (pos == 0) {
            pop_front();
        } else if (pos == m_size - 1) {
            pop_back();
        } else {
            Node* to_delete = get_node_at_pos(pos);
            to_delete -> m_next -> m_prev = to_delete -> m_prev;
            to_delete -> m_prev -> m_next = to_delete -> m_next;
            --m_size;
            remove_from_sorted_order(to_delete);
            delete to_delete;
        }
    }

    void insert(const std::size_t pos, const T& val) {
        if (pos < 0 || pos > m_size) {
            throw std::out_of_range("Invalid postion");
        } else if (pos == 0) {
            push_front(val);
        } else if (pos == m_size) {
            push_back(val);
        } else {
            Node* to_insert = new Node(val);
            Node* node = get_node_at_pos(pos);
            node -> m_prev -> m_next =  to_insert;
            to_insert -> m_prev = node -> m_prev;
            to_insert -> m_next = node;
            node -> m_prev = to_insert; 
            ++m_size;
            put_in_sorted_order(to_insert);
        }
    }

    const T get_at(const std::size_t pos) {
        Node* curr = get_node_at_pos(pos);
        advance_node(curr);
        return curr -> m_value;
    }

    void clear() {
        while (m_head) {
            Node* curr = m_head -> m_next;
            delete m_head;
            m_head = curr;
        }
        m_size = 0;
    }

    std::size_t size() const {
        return m_size;
    }

    void print() {
        Node* curr = m_head;
        while (curr) {
            std::cout << curr -> m_value << " ";
            curr = curr -> m_next;
        }
        std::cout << std::endl;
    }
    
    void print_ascending_order() {
        Node* curr = m_asc_head;
        while (curr) {
            std::cout << curr -> m_value << " ";
            curr = curr -> m_asc;
        }
        std::cout << std::endl;
    }

    void print_descending_order() {
        Node* curr = m_desc_head;
        while (curr) {
            std::cout << curr -> m_value << " ";
            curr = curr -> m_desc;
        }
        std::cout << std::endl;
    }

    void print_from_tail() {
        Node* curr = m_tail;
        while (curr) {
            std::cout << curr -> m_value << " ";
            curr = curr -> m_prev;
        }
        std::cout << std::endl;
    }

private:
    void put_back(Node* node) {
        Node* curr = m_asc_head;
        if (!m_asc_head) {
            m_asc_head = node;
            node -> m_asc = nullptr;
            m_desc_head = node;
            node -> m_desc = nullptr;
        } else {
            while (curr -> m_asc) {
                curr = curr -> m_asc;
            }
            curr -> m_asc = node;
            m_desc_head = node;
            node -> m_desc = curr;
            node -> m_asc = nullptr;
        }
    }

    void put_front(Node* node) {
        Node* curr = m_asc_head;
        if (!m_asc_head) {
            m_asc_head = node;
            node -> m_asc = nullptr;
            m_desc_head = node;
            node -> m_desc = nullptr;
        } else {
            node -> m_asc = curr;
            curr -> m_desc = node;
            m_asc_head = node;
        }
    }

    void put_in_sorted_order(Node* node) {
        Node* curr = m_head;
        Node* asc = m_asc_head;
        Node* desc = m_desc_head; 
        while (asc && asc -> m_value < node -> m_value) {
            asc = asc -> m_asc;
        }

        if (!asc) {
            put_back(node);
        } else if (asc == m_asc_head) {
            put_front(node);
        } else {
            node -> m_asc = asc;
            node -> m_desc = asc -> m_desc;
            asc -> m_desc = node;
            node -> m_desc-> m_asc = node;
        }
    }

    void remove_from_sorted_order(Node* node) {
        if (node == m_asc_head) {
            m_asc_head = m_asc_head -> m_asc;
            m_asc_head -> m_asc -> m_desc = nullptr;
            return;
        } 
        if (node -> m_asc) {
            node -> m_asc -> m_desc = node -> m_desc;
        } 
        if (node -> m_desc){
            node -> m_desc -> m_asc = node -> m_asc;
        }
    }

    Node* get_node_at_pos(const std::size_t pos) {
        if (pos < 0 || pos >= m_size) {
            throw std::invalid_argument("Invalid position");
        }

        Node* curr = nullptr;
        if (pos < m_size / 2) {
            curr = m_head;
            std::size_t count{};
            while (curr && pos != count) {
                ++count;
                curr = curr -> m_next;
            }
        } else {
            curr = m_tail;
            std::size_t count = m_size - 1;
            while (curr && pos != count) {
                --count;
                curr = curr -> m_prev;
            }
        }
        return curr;
    }

    void advance_node(Node* node) {
        if (!node || node == m_head) {
            return;
        }
        Node* lhs = node -> m_prev;
        if (lhs -> m_prev && node -> m_next) {
            lhs -> m_prev -> m_next = node;
            node -> m_prev = lhs -> m_prev;
            lhs -> m_next = node -> m_next;
            node -> m_next -> m_prev = lhs;
            node -> m_next = lhs;
            lhs -> m_prev  = node;
        } else if (!lhs -> m_prev) {
            node -> m_prev = lhs -> m_prev;
            lhs -> m_prev = node;
            lhs -> m_next = node -> m_next;
            node -> m_next -> m_prev = lhs;
            node -> m_next = lhs;
            m_head = node;
        } else {
            lhs -> m_prev -> m_next = node;
            node -> m_prev = lhs -> m_prev;
            lhs -> m_prev = node;
            lhs -> m_next = node -> m_next; 
            node -> m_next = lhs;
            m_tail = lhs;
        }
    }
};

#endif