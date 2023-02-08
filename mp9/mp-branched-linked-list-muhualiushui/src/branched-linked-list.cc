#include "branched-linked-list.hpp"

BLL::BLL(const BLL& to_copy) {
  if (to_copy.head_ == nullptr) {
    return;
  }
  Node* origin = to_copy.head_;
  head_ = new Node(origin->data_);
  if (origin->next_bll_ != nullptr) {
    head_->next_bll_ = new BLL(*origin->next_bll_);
  }
  Node* find = head_;
  while (origin->next_node_ != nullptr) {
    origin = origin->next_node_;
    find->next_node_ = new Node(origin->data_);
    if (origin->next_bll_ != nullptr) {
      find->next_node_->next_bll_ = new BLL(*origin->next_bll_);
    }
    find = find->next_node_;
  }
}

BLL& BLL::operator=(const BLL& rhs) {
  if (this == &rhs) {
    return *this;
  }
  this->~BLL();
  if (rhs.head_ == nullptr) {
    return *this;
  }
  Node* origin = rhs.head_;
  head_ = new Node(origin->data_);
  if (origin->next_bll_ != nullptr) {
    head_->next_bll_ = new BLL(*origin->next_bll_);
  }
  Node* find = head_;
  while (origin->next_node_ != nullptr) {
    origin = origin->next_node_;
    find->next_node_ = new Node(origin->data_);
    if (origin->next_bll_ != nullptr) {
      find->next_node_->next_bll_ = new BLL(*origin->next_bll_);
    }
    find = find->next_node_;
  }
  return *this;
}

BLL::~BLL() {
  Node* current = head_;
  while (current != nullptr) {
    Node* temp = current->next_node_;
    delete current->next_bll_;
    delete current;
    current = temp;
  }
  head_ = nullptr;
}

Node* BLL::PushBack(char dat) {
  Node* value = new Node(dat);
  if (head_ == nullptr) {
    head_ = value;
    return head_;
  }
  Node* find = head_;
  while (find->next_node_ != nullptr) {
    find = find->next_node_;
  }
  find->next_node_ = value;
  return find->next_node_;
}

char BLL::GetAt(size_t idx) const {
  if (idx >= this->Size()) {
    throw std::runtime_error("out of bound");
  }
  Node* find = head_;
  while (idx != 0) {
    if (find->next_bll_ != nullptr) {
      if (find->next_bll_->Size() >= idx) {
        idx--;
        return find->next_bll_->GetAt(idx);
      }
      idx -= find->next_bll_->Size();
    }
    find = find->next_node_;
    idx--;
  }
  return find->data_;
}
void BLL::SetAt(size_t idx, char dat) {
  if (idx >= this->Size()) {
    throw std::runtime_error("out of bound");
  }
  Node* find = head_;
  while (idx != 0) {
    if (find->next_bll_ != nullptr) {
      if (find->next_bll_->Size() >= idx) {
        idx--;
        find->next_bll_->SetAt(idx, dat);
        return;
      }
      idx -= find->next_bll_->Size();
    }
    find = find->next_node_;
    idx--;
  }
  find->data_ = dat;
}

void BLL::Join(size_t idx, BLL* list) {
  if (idx >= this->Size()) {
    throw std::runtime_error("out of bound");
  }
  Node* find = head_;
  while (idx != 0) {
    if (find->next_bll_ != nullptr) {
      if (find->next_bll_->Size() >= idx) {
        idx--;
        find->next_bll_->Join(idx, list);
        return;
      }
      idx -= find->next_bll_->Size();
    }
    find = find->next_node_;
    idx--;
  }
  if (find->next_bll_ != nullptr) {
    throw std::runtime_error("already exist");
  }
  find->next_bll_ = list;
  if (!list->IsBLLAcyclic()) {
    find->next_bll_ = nullptr;
    throw std::invalid_argument("circle");
  }
}

bool BLL::IsBLLAcyclic() const {
  if (head_ != nullptr) {
    Node* find = head_;
    if (head_->next_node_ == nullptr) {
      return true;
    }
    Node* find2 = (head_->next_node_->next_bll_ == nullptr)
                      ? head_->next_node_
                      : head_->next_node_->next_bll_->head_;
    while (find->next_node_ != nullptr && find2->next_node_ != nullptr) {
      if (find == find2) {
        return false;
      }
      find = (find->next_node_->next_bll_ == nullptr)
                 ? find->next_node_
                 : find->next_node_->next_bll_->head_;
      find2 = (find2->next_node_->next_bll_ == nullptr)
                  ? find2->next_node_
                  : find2->next_node_->next_bll_->head_;
      if (find2->next_node_ == nullptr || find->next_node_ == nullptr) {
        return true;
      }
      if (find2->next_node_ == nullptr) {
        return true;
      }
      find2 = (find2->next_node_->next_bll_ == nullptr)
                  ? find2->next_node_
                  : find2->next_node_->next_bll_->head_;
    }
  }
  return true;
}
std::string BLL::ToString() const {
  Node* find = head_;
  std::string answer;
  while (find != nullptr) {
    answer += find->data_;
    if (find->next_bll_ != nullptr) {
      answer += find->next_bll_->ToString();
    }
    find = find->next_node_;
  }
  return answer;
}


std::string BLL::ToStringHelper(Node* n){
  if(n==nullptr){
    return "";
  }
  return n->data_+((!n->next_bll_)? "": ToStringHelper(n->next_bll_->head_))
  +ToStringHelper(n->next_node_)); 
}
size_t BLL::Size() const {
  Node* find = head_;
  size_t count = 0;
  while (find != nullptr) {
    count++;
    if (find->next_bll_ != nullptr) {
      count += find->next_bll_->Size();
    }
    find = find->next_node_;
  }
  return count;
}