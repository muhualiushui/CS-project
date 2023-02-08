#include "dna_strand.hpp"

#include <stdexcept>

DNAstrand::~DNAstrand() {
  while (head_ != nullptr) {
    Node* temp = head_->next;
    delete head_;
    head_ = temp;
  }
}

void DNAstrand::Find(bool& discover,
                     bool& is_first,
                     Node*& find,
                     Node*& figure_first,
                     Node*& figure_end,
                     int length,
                     const char* pattern) {
  int count = 0;
  Node* second_figure_first = nullptr;
  while (find != nullptr) {
    count = (find->data == pattern[count]) ? count + 1 : 0;
    if (count == 0) {
      count = (find->data == pattern[0]) ? count + 1 : 0;
    }
    if (count == 1) {
      if (discover) {
        second_figure_first = find;  // new char
      } else {
        figure_first = find;
      }
    }
    if (count == length) {
      is_first = figure_first == head_;
      count = 0;
      figure_end = find->next;
      if (discover) {
        is_first = false;
        figure_first = nullptr;
        figure_first = second_figure_first;
        second_figure_first = nullptr;
      }
      discover = true;
    }
    find = find->next;
  }
}

void DNAstrand::Replacement(Node*& find,
                            Node*& figure_first,
                            Node*& figure_end) {
  figure_first = nullptr;
  while (find != figure_end) {  // delete next node
    Node* temp = find->next;
    delete find;
    find = temp;
    head_ = temp;
  }
  Node* temp = new Node('b');
  temp->next = head_;
  head_ = temp;
  figure_first = head_;
}
void DNAstrand::Replacement2(Node*& find,
                             Node*& figure_first,
                             Node*& figure_end) {
  figure_first = nullptr;
  while (find->next != figure_end) {  // delete next node
    Node* temp = find->next->next;
    delete find->next;
    find->next = temp;
  }
  figure_first = find;
}
void DNAstrand::SpliceIn(const char* pattern, DNAstrand& to_splice_in) {
  int length = 0;
  if (pattern[0] == '\0' || to_splice_in.head_ == nullptr) {
    return;
  }
  while (pattern[length] != '\0') {  // length pf the pattern;
    length++;
  }
  Node* find = head_;
  Node* figure_first = nullptr;
  Node* figure_end = nullptr;
  bool discover = false;
  bool is_first = false;
  Find(discover, is_first, find, figure_first, figure_end, length, pattern);
  if (!discover) {  // if not match ----stop;
    throw std::invalid_argument("no match");
  }
  find = head_;
  while (find != nullptr) {
    if (is_first) {
      Replacement(find, figure_first, figure_end);
      break;
    }
    if (find->next == figure_first) {
      Replacement2(find, figure_first, figure_end);
      break;
    }
    find = find->next;
  }  // remove useless node
  figure_first->next = to_splice_in.head_;
  to_splice_in.tail_->next = figure_end;
  if (is_first) {
    Node* temp = head_->next;
    delete head_;
    head_ = temp;
  }
  to_splice_in.head_ = nullptr;
  to_splice_in.tail_ = nullptr;
}
