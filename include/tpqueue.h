// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_
#include <stdexcept>

template<typename T>
class TPQueue {
   public:
  TPQueue() : first(nullptr) {}

  ~TPQueue() {
    while (!isClear()) {
      remove();
    }
  }

  void insert(const T& element) {
    Cell* newCell = new Cell(element);
    if (!first || element.prior > first->value.prior) {
      newCell->next = first;
      first = newCell;
    } else {
      Cell* walker = first;
      while (walker->next && walker->next->value.prior >= element.prior) {
        walker = walker->next;
      }
      newCell->next = walker->next;
      walker->next = newCell;
    }
  }

  T remove() {
    if (!first) throw std::runtime_error("Очередь пуста");
    Cell* oldFirst = first;
    T outVal = oldFirst->value;
    first = first->next;
    delete oldFirst;
    return outVal;
  }

  const T& peek() const {
    if (!first) throw std::runtime_error("Очередь пуста");
    return first->value;
  }

  bool isClear() const {
    return first == nullptr;
  }

 private:
  struct Cell {
    explicit Cell(const T& val) : value(val), next(nullptr) {}
    T value;
    Cell* next;
  };

  Cell* first;
};

struct SYM {
  char ch;
  int prior;
};

#endif  // INCLUDE_TPQUEUE_H_
