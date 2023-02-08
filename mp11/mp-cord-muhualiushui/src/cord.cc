#include "cord.hpp"

#include <string>
#include "cord-utilities.hpp"
using namespace std;

Cord::Cord(const std::string& dat) {
  data_ = dat;
  length_ = dat.length();
}

Cord::Cord(const std::shared_ptr<Cord>& left_cord,
           const std::shared_ptr<Cord>& right_cord) {
  if (left_cord == nullptr || right_cord == nullptr) {
    throw runtime_error("invalid children");
  }
  length_ = right_cord->length_ + left_cord->length_;
  left_ = left_cord;
  right_ = right_cord;
}

size_t Cord::Length() const { return length_; }

std::shared_ptr<Cord> Cord::GetLeft() const { return left_; }

std::shared_ptr<Cord> Cord::GetRight() const { return right_; }

const std::string& Cord::GetData() const { return data_; }

std::string Cord::ToString() const {
  std::string answer;
  if (left_ != nullptr) {
    answer += left_->ToString();
  }
  if (right_ != nullptr) {
    answer += right_->ToString();
  }
  if (!left_ && !right_) {
    answer += data_;
  }
  return answer;
}
std::shared_ptr<Cord> Cord::SubString(size_t lower_idx,
                                      size_t upper_idx) const {
  shared_ptr<Cord> new_card;
  size_t x=lower_idx+upper_idx;
  x++;
//   string prograss = this->ToString().substr(lower_idx, upper_idx - lower_idx);
//   vector<shared_ptr<Cord>> combination;
//   if (prograss == this->ToString()) {
//     throw runtime_error("same with this");
//   }
//   vector<shared_ptr<Cord>> transit;
//   if (left_ != nullptr) {
//     transit.push_back(left_);
//     SubStringHelper(prograss, transit, combination);
//   }

//   if (right_ != nullptr) {
//     transit.push_back(right_);
//     SubStringHelper(prograss, transit, combination);
//   }
//   while (combination.size() > 2) {
//     shared_ptr<Cord> transit_card =
//         make_shared<Cord>(combination[0], combination[1]);
//     combination.erase(combination.begin(), combination.begin() + 1);
//     combination[0] = transit_card;
//   }
//   new_card = make_shared<Cord>(combination[0], combination[1]);
  return new_card;
}
// void Cord::SubStringHelper(string& prograss,
//                            vector<shared_ptr<Cord>>& transit,
//                            vector<shared_ptr<Cord>>& combination) const {
//   map<shared_ptr<Cord>, bool> visited;
//   while (!transit.empty()) {
//     shared_ptr<Cord> back = transit.back();
//     string current = back->ToString();
//     visited[back] = true;
//     if (current ==
//         prograss.substr(0, current.length())) {  // could be generalize
//       prograss = prograss.substr(current.length());
//       combination.push_back(back);
//       transit.pop_back();
//     } else {  // can not be generalized
//       if (back->left_ != nullptr && !visited[back->left_]) {
//         transit.push_back(back->left_);
//       } else if (back->right_ != nullptr && !visited[back->right_]) {
//         transit.push_back(back->right_);
//       } else {  // since can not be generalized, creat new cord
//         if (!back->left_ && !back->right_) {
//           size_t i = 0;
//           shared_ptr<Cord> new_cord;
//           if (back->length_ < prograss.length()) {
//             for (i = 0; i < back->length_; i++) {
//               if (back->data_.at(i) == prograss.at(0)) {
//                 break;
//               }
//             }
//             new_cord = make_shared<Cord>(back->data_.substr(i, back->length_));
//             prograss = prograss.substr(new_cord->length_);
//           } else {
//             new_cord = make_shared<Cord>(prograss);
//             prograss = "";
//           }
//           combination.push_back(new_cord);
//         }
//         transit.pop_back();
//       }
//     }
//   }
// }

char Cord::At(size_t idx) const {
  if(length_==0){
    throw runtime_error("out of bound");
  }
  char answer;
   AtHelper(idx, left_, answer);
   if(idx>=0){
  AtHelper(idx, right_, answer);
   }
   return answer;
}
    void Cord::AtHelper(size_t& idx,  std::shared_ptr<Cord> cords,char& answer)const{
    if(cords->left_==nullptr&& cords->right_==nullptr){
      if(length_>idx){
        answer= data_.at(idx);
      }else{
        idx-=length_;
      }
    }
     if(cords->left_!=nullptr){
       AtHelper(idx,cords->left_,answer);
    }
    if(cords->left_!=nullptr){
       AtHelper(idx,cords->right_,answer);
    }
  }
  // if (!left_ && !right_) {  // whether have a child
  //   if (idx >= data_.length()) {
  //     throw runtime_error("out of bound");
  //   }
  //   return data_.at(idx);
  // }
  // map<shared_ptr<Cord>, bool> visited;
  // vector<shared_ptr<Cord>> stored;
  // vector<shared_ptr<Cord>> transit;
  // if (left_ != nullptr) {
  //   transit.push_back(left_);
  //   AtHelper(visited, stored, transit);
  // }
  // if (right_ != nullptr) {
  //   transit.push_back(right_);
  //   AtHelper(visited, stored, transit);
  // }
  // for (const auto& i : stored) {
  //   if (i->length_ > idx) {
  //     return i->data_.at(idx);
  //   }
  //   idx -= (idx >= i->length_) ? i->length_ : 0;
  // }
  // throw runtime_error("out of bound");
// void Cord::AtHelper(map<shared_ptr<Cord>, bool>& visited,
//                     vector<shared_ptr<Cord>>& stored,
//                     vector<shared_ptr<Cord>>& transit) const {
//   while (!transit.empty()) {
//     shared_ptr<Cord> back = transit.back();
//     visited[back] = true;
//     if (back->left_ != nullptr && !visited[back->left_]) {
//       transit.push_back(back->left_);
//     } else if (back->right_ != nullptr && !visited[back->right_]) {
//       transit.push_back(back->right_);
//     } else {
//       if (!back->left_ && !back->right_) {
//         stored.push_back(back);
//       }
//       transit.pop_back();
//     }
//   }
// }

bool Cord::IsValidCord() const {
//   map<shared_ptr<Cord>, bool> visited;
//   vector<shared_ptr<Cord>> transit{left_, right_};
//   while (!transit.empty()) {
//     shared_ptr<Cord> back = transit.front();
//     transit.erase(transit.begin(), transit.begin() + 1);
//     visited[back] = true;
//     if (back->left_ != nullptr) {
//       if (!data_.empty() || !visited[back->left_]) {
//         return false;
//       }
//       transit.push_back(back->left_);
//     }
//     if (back->right_ != nullptr) {
//       if (!data_.empty() || !visited[back->right_]) {
//         return false;
//       }
//       transit.push_back(back->right_);
//     }
//     if (back->left_ == nullptr && back->right_ == nullptr) {
//       transit.erase(transit.begin(), transit.begin() + 1);
//     }
//   }
  return true;
}
