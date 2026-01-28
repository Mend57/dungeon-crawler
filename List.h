#include <cstddef>

template <typename T>
class List {
private:
    struct Element {
        T data;
        Element* prev;
        Element* next;
    };
    Element* head = nullptr;
    Element* tail = nullptr;
    std::size_t m_size = 0;

public:
    class iterator {
        friend class List;
        private:
            Element* element;
            List* list;
            iterator(Element* element, List* list) : element(element), list(list){}

        public:
            iterator() : element(nullptr), list(nullptr){}
            bool operator==(const iterator& other) {return element == other.element && list == other.list;}
            bool operator!=(const iterator& other) {return !(*this == other);}

            iterator& operator++() {
                if (!list) throw std::runtime_error("Invalid iterator");
                element = element->next;
                return *this;
            }

            iterator& operator--() {
                if (!list) throw std::runtime_error("Invalid iterator");
                if (element == nullptr) {
                    element = list->tail;
                    return *this;
                }
                if (element->prev == nullptr) throw std::runtime_error("Decrementing begin iterator");
                element = element->prev;
                return *this;
            }

            T& operator*() {
                if (!element) throw std::runtime_error("Invalid iterator");
                return element->data;
            }

    };

    List(){};
    std::size_t size() const {return m_size;}
    bool empty() const {return m_size == 0;}
    iterator begin() {return empty() ? end() : iterator(head, this);}
    iterator end() {return iterator(nullptr, this);}
    T& front() {return head->data;}
    T& back() {return tail->data;}

    void push_back(T data) {
        Element* tmp = new Element{data, tail, nullptr};
        if (empty()) head = tail = tmp;
        else {
            tail->next = tmp;
            tail = tmp;
        }
        ++m_size;
    }

    void push_front(T data) {
        Element* tmp = new Element{data, nullptr, head};
        if (empty()) head = tail = tmp;
        else {
            head->prev = tmp;
            head = tmp;
        }
        ++m_size;
    }

    void pop_back() {
        if (empty()) throw std::runtime_error("The list is empty");
        Element* tmp = tail;
        tail = tail->prev;
        if (tail) tail->next = nullptr;
        else head = nullptr;
        delete tmp;
        --m_size;
    }

    void pop_front() {
        if (empty()) throw std::runtime_error("The list is empty");
        Element* tmp = head;
        head = head->next;
        if (head) head->prev = nullptr;
        else tail = nullptr;
        delete tmp;
        --m_size;
    }

    void remove(T data) {
        Element* current = head;
        while (current) {
            Element* next = current->next;
            if (current->data == data) {
                if (current->prev) current->prev->next = current->next;
                else head = current->next;

                if (current->next) current->next->prev = current->prev;
                else tail = current->prev;

                delete current;
                --m_size;
            }
            current = next;
        }
    }
    
    ~List() {while (!empty()) pop_back();}
};
