#include <cstddef>

template<typename T>
class List {
  private:
    struct Element {
      T* data;
      Element* next;
      Element* previous;
    };
    Element* start = nullptr;
    Element* endElement = nullptr;
    std::size_t m_size = 0;

  class iterator {
    friend class List;

    public:
      T*& operator*() const {
        if (!elem) throw std::runtime_error("Dereferencing invalid iterator");
        return elem->data;
      }

      iterator& operator++() {
        if (!elem) throw std::runtime_error("Incrementing invalid iterator");
        elem = elem->next;
        return *this;
      }

      iterator& operator--() {
        if (!list) throw std::runtime_error("Invalid iterator");

        if (!elem) {
          if (!list->endElement) throw std::runtime_error("Decrementing end() of empty list");
          elem = list->endElement;
          return *this;
        }

        if (!elem->previous) throw std::runtime_error("Decrementing begin() iterator");
        elem = elem->previous;
        return *this;
      }

      bool operator==(const iterator& other) const {return list == other.list && elem == other.elem;};
      bool operator!=(const iterator& other) const{  return !(*this == other);};

    private:
      iterator(List* list, Element* elem) : list(list), elem(elem) {};

      List* list;
      Element* elem;
  };

  public:
    List(){};
    ~List(){while (start != nullptr) pop_back();};

  void push_back(T* data) {
    Element* tmp = new Element{data, nullptr, endElement};

    if (empty()) start = endElement = tmp;
    else {
      endElement->next = tmp;
      endElement = tmp;
    }
    m_size++;
  }

  void push_front(T* data) {
    Element* tmp = new Element{data, start, nullptr};

    if (empty()) start = endElement = tmp;
    else {
      start->previous = tmp;
      start = tmp;
    }

    m_size++;
  }

  void pop_back() {
    if (empty()) throw std::runtime_error("List is empty");;

    Element* toDelete = endElement;

    if (start == endElement) start = endElement = nullptr;
    else {
      endElement = endElement->previous;
      endElement->next = nullptr;
    }

    delete toDelete;
    m_size--;
  }

  void pop_front() {
    if (empty()) throw std::runtime_error("List is empty");;

    Element* toDelete = start;

    if (start == endElement) start = endElement = nullptr;
    else {
      start = start->next;
      start->previous = nullptr;
    }

    delete toDelete;
    m_size--;
  }

  void remove(T* data) {
    Element* current = start;

    while (current != nullptr) {
      Element* next = current->next;

      if (current->data == data) {
        if (current == start) start = current->next;
        if (current == endElement) endElement = current->previous;
        if (current->previous) current->previous->next = current->next;
        if (current->next) current->next->previous = current->previous;

        delete current;
        m_size--;
      }
      current = next;
    }
  }

  T* first() {
    if (empty()) return nullptr;
    return start->data;
  }

  std::size_t size() const {return m_size;};
  bool empty() const {return m_size == 0;};

  iterator begin() {return iterator(this, start);}
  iterator end(){return iterator(this, nullptr);}
};
