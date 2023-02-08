#ifndef DNA_STRAND_HPP
#define DNA_STRAND_HPP

#include "node.hpp"

class DNAstrand {
public:
  DNAstrand() = default;
  DNAstrand(const DNAstrand& rhs) = delete;
  DNAstrand& operator=(const DNAstrand& rhs) = delete;
  ~DNAstrand();
  void Addhead(Node* node) { head_ = node; }
  void Addtail(Node* node) { tail_ = node; }
  Node* Gethead() { return head_; }
  void SpliceIn(const char* pattern, DNAstrand& to_splice_in);
  void Replacement(Node*& find, Node*& figure_first, Node*& figure_end);
  void Replacement2(Node*& find, Node*& figure_first, Node*& figure_end);
  void Find(bool& discover,
            bool& is_first,
            Node*& find,
            Node*& figure_first,
            Node*& figure_end,
            int length,
            const char* pattern);

private:
  Node* head_ = nullptr;
  Node* tail_ = nullptr;
};

#endif