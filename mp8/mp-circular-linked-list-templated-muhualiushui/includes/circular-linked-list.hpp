#ifndef CIRCULAR_LINKED_LIST_HPP
#define CIRCULAR_LINKED_LIST_HPP

#include <iostream>

#include "node.hpp"

enum class Order { kASC, kDESC };

template <typename T>
class CircularLinkedList {
public:
  CircularLinkedList() = default;
  CircularLinkedList(const CircularLinkedList<T>& source);  // handled
  CircularLinkedList<T>& operator=(
      const CircularLinkedList<T>& source);  // handled
  ~CircularLinkedList();                     // handled

  void InsertInOrder(const T& data);  // handled
  void Reverse();                     // handled
  void PushFront(const T& data);      // handled
  void PushBack(const T& data);       // handled
  void SmallToBig(const T& data);     // handled
  void BigToSmall(const T& data);     // handled
  void Clear();                       // handled

  template <typename U>
  friend std::ostream& operator<<(std::ostream& os,
                                  const CircularLinkedList<U>& cll);

private:
  Node<T>* head_ = nullptr;
  Node<T>* tail_ = nullptr;
  Order node_order_ = Order::kASC;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const CircularLinkedList<T>& cll) {
  Node<T>* iter = cll.head_;
  // empty list condition
  if (iter == nullptr) {
    os << "Empty list";
    return os;
  }
  // non-empty list condition
  do {
    os << iter->data << '\t';
    iter = iter->next;
  } while (iter != cll.head_);

  return os;
}

///////////////////////////////////Everything need template T
template <typename T>
CircularLinkedList<T>::CircularLinkedList(const CircularLinkedList<T>& source) {
  if (source.head_ == nullptr || source.tail_ == nullptr) {
    node_order_ = source.node_order_;
    return;
  }
  Node<T>* original = source.head_;
  head_ = new Node<T>(original->data);
  Node<T>* temp = head_;
  while (original->next != source.head_) {
    original = original->next;
    temp->next = new Node<T>(original->data);
    temp = temp->next;
  }
  tail_ = temp;
  tail_->next = head_;
  node_order_ = source.node_order_;
}

template <typename T>
CircularLinkedList<T>& CircularLinkedList<T>::operator=(
    const CircularLinkedList<T>& source) {
  if (source.head_ == nullptr || source.tail_ == nullptr || this == &source) {
    node_order_ = source.node_order_;
    return *this;
  }
  Clear();
  Node<T>* original = source.head_;
  head_ = new Node<T>(original->data);
  if (source.tail_->data == source.head_->data) {
    tail_ = head_;
    head_->next = tail_;
    tail_->next = head_;
  } else {
    Node<T>* temp = head_;
    while (original->next != source.head_) {
      original = original->next;
      temp->next = new Node<T>(original->data);
      temp = temp->next;
    }
    tail_ = temp;
    tail_->next = head_;
  }
  node_order_ = source.node_order_;
  return *this;
}

template <typename T>
void CircularLinkedList<T>::InsertInOrder(const T& data) {
  if (head_ == nullptr || tail_ == nullptr) {
    auto* value = new Node<T>(data);
    head_ = tail_ = value;
    head_->next = tail_;
    tail_->next = head_;
  } else {
    if (node_order_ == Order::kASC) {  // small to big
      if (head_->data > data) {        // at head
        PushFront(data);
      } else if (tail_->data <= data) {
        PushBack(data);
      } else {
        SmallToBig(data);
      }
    } else {  // Big to small
      if (head_->data < data) {
        PushFront(data);
      } else if (tail_->data >= data) {
        PushBack(data);
      } else {
        BigToSmall(data);
      }
    }
  }
}

template <typename T>
void CircularLinkedList<T>::PushFront(const T& data) {
  auto* value = new Node<T>(data);
  Node<T>* temp = head_;
  head_ = value;
  head_->next = temp;
  tail_->next = head_;
}

template <typename T>
void CircularLinkedList<T>::PushBack(const T& data) {
  auto* value = new Node<T>(data);
  tail_->next = value;
  tail_ = value;
  tail_->next = head_;
}
template <typename T>
void CircularLinkedList<T>::SmallToBig(const T& data) {
  auto* value = new Node<T>(data);
  Node<T>* find = head_;
  while (find->next != head_) {
    if (find->next->data > data) {
      Node<T>* temp = find->next;
      find->next = value;
      find->next->next = temp;
      break;
    }
    find = find->next;
  }
}
template <typename T>
void CircularLinkedList<T>::BigToSmall(const T& data) {
  auto* value = new Node<T>(data);
  Node<T>* find = head_;
  while (find->next != head_) {
    if (find->next->data <= data) {
      Node<T>* temp = find->next;
      find->next = value;
      find->next->next = temp;
      break;
    }
    find = find->next;
  }
}

template <typename T>
void CircularLinkedList<T>::Reverse() {
  if (node_order_ == Order::kASC) {
    node_order_ = Order::kDESC;
  } else {
    node_order_ = Order::kASC;
  }
  if (head_ == nullptr) {
    return;
  }
  Node<T>* find = head_;
  Node<T>* stored_find = find;
  Node<T>* change1 = head_;
  Node<T>* change2 = tail_;
  head_ = tail_;
  int count = 0;
  while (find != tail_) {  // 5-1-2-3-4-5-1
    stored_find = find;
    find = find->next;
    change1->next = change2;
    if (count == 0) {
      tail_ = change1;
      count++;
    }
    change1 = find;
    change2 = stored_find;
  }
  change1->next = change2;
}

template <typename T>
void CircularLinkedList<T>::Clear() {
  if (head_ == nullptr) {
    return;
  }
  Node<T>* find = head_->next;
  delete head_;
  while (find != head_) {
    Node<T>* temp = find->next;
    delete find;
    find = temp;
  }
}

template <typename T>
CircularLinkedList<T>::~CircularLinkedList() {
  if (head_ == nullptr) {
    return;
  }
  Node<T>* find = head_->next;
  delete head_;
  while (find != head_) {
    Node<T>* temp = find->next;
    delete find;
    find = temp;
  }
}

#endif