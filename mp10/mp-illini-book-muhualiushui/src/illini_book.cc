#include "illini_book.hpp"

#include <fstream>
#include <queue>

#include "utilities.hpp"

IlliniBook::IlliniBook(const std::string& people_fpath,
                       const std::string& relations_fpath) {
  std::ifstream ifs{people_fpath};
  std::string value;
  if (!ifs.is_open()) {
    throw std::runtime_error("can not open file");
  }
  while (ifs >> value) {  // initialize map without relation
    people_.push_back(stoi(value));
    relations_.insert({stoi(value), {}});
  }
  std::ifstream ifs2{relations_fpath};
  if (!ifs2.is_open()) {
    throw std::runtime_error("can not open file");
  }
  while (ifs2 >> value) {
    std::vector<std::string> input = utilities::Split(value, ',');
    relations_.find(stoi(input[0]))
        ->second.push_back({stoi(input[1]), input[2]});
    relations_.find(stoi(input[1]))
        ->second.push_back({stoi(input[0]), input[2]});
  }
}

std::map<int, int> IlliniBook::Parent(int uin_1,
                                      const std::string& relationship) const {
  bool test = !relationship.empty();
  std::queue<int> search;
  std::map<int, int> parent;
  std::map<int, bool> visited;
  for (const auto& single : relations_) {
    visited.insert({single.first, false});
  }
  visited.find(uin_1)->second = true;
  search.push(uin_1);
  while (!search.empty()) {
    int input = search.front();
    search.pop();
    for (const auto& single : relations_.find(input)->second) {
      bool add = true;  // whether have condition
      add = test ? (single.second == relationship) : true;  // one condition
      if (!visited.find(single.first)->second) {
        if (add) {
          visited.find(single.first)->second = true;
          search.push(single.first);
          parent.insert({single.first, input});
        }
      }
    }
  }
  return parent;
}

bool IlliniBook::AreRelated(int uin_1, int uin_2) const {  // passed
  std::map<int, int> parent = Parent(uin_1, "");
  int key = uin_2;
  return parent.find(key) != parent.end();
}
bool IlliniBook::AreRelated(int uin_1,
                            int uin_2,
                            const std::string& relationship) const {  // passed
  std::map<int, int> parent = Parent(uin_1, relationship);
  int key = uin_2;
  return parent.find(key) != parent.end();
}
int IlliniBook::GetRelated(int uin_1, int uin_2) const {
  std::map<int, int> parent = Parent(uin_1, "");
  int key = uin_2;
  if (parent.find(key) == parent.end()) {
    return -1;
  }
  int total_path = 0;
  while (key != uin_1) {
    key = parent.find(key)->second;
    total_path++;
  }
  if (total_path == 0) {
    return -1;
  }
  return total_path;
}
int IlliniBook::GetRelated(int uin_1,
                           int uin_2,
                           const std::string& relationship) const {
  std::map<int, int> parent = Parent(uin_1, relationship);
  int key = uin_2;
  if (parent.find(key) == parent.end()) {
    return -1;
  }
  int total_path = 0;
  while (key != uin_1) {
    key = parent.find(key)->second;
    total_path++;
  }
  if (total_path == 0) {
    return -1;
  }
  return total_path;
}

std::vector<int> IlliniBook::GetSteps(int uin, int n) const {
  std::queue<int> search;
  std::map<int, int> parent;
  std::map<int, bool> visited;
  for (const auto& single : relations_) {
    visited.insert({single.first, false});
  }
  visited.find(uin)->second = true;
  search.push(uin);
  while (!search.empty()) {
    int input = search.front();
    search.pop();
    for (const auto& single : relations_.find(input)->second) {
      if (!visited.find(single.first)->second) {
        visited.find(single.first)->second = true;
        search.push(single.first);
        parent.insert({single.first, input});
      }
    }
  }
  std::vector<int> nodes;
  for (const auto& single : parent) {
    int total_path = 0;
    for (int search = single.first; parent.find(search) != parent.end();
         search = parent.find(search)->second) {
      total_path++;
    }
    if (total_path == n) {
      nodes.push_back(single.first);
    }
  }
  return nodes;
}
size_t IlliniBook::CountGroups() const {
  std::vector<int> origin;
  size_t count = 0;
  for (const auto& single : relations_) {
    origin.push_back(single.first);
  }
  while (!origin.empty()) {
    std::map<int, int> parent = Parent(origin[0], "");
    origin.erase(origin.begin(), origin.begin() + 1);
    for (const auto& signal : parent) {
      for (size_t i = 0; i < origin.size(); i++) {
        if (signal.first == origin[i]) {
          origin.erase(origin.begin() + i, origin.begin() + i + 1);
          break;
        }
      }
    }
    count++;
  }
  return count;
}
size_t IlliniBook::CountGroups(const std::string& relationship) const {
  std::vector<int> origin;
  size_t count = 0;
  for (const auto& single : relations_) {
    origin.push_back(single.first);
  }
  while (!origin.empty()) {
    std::map<int, int> parent = Parent(origin[0], relationship);
    origin.erase(origin.begin(), origin.begin() + 1);
    for (const auto& signal : parent) {
      for (size_t i = 0; i < origin.size(); i++) {
        if (signal.first == origin[i]) {
          origin.erase(origin.begin() + i, origin.begin() + i + 1);
          break;
        }
      }
    }
    count++;
  }
  return count;
}

std::map<int, std::vector<std::pair<int, std::string>>> IlliniBook::Parent2(
    const std::vector<std::string>& relationships) const {
  std::map<int, std::vector<std::pair<int, std::string>>> different;
  for (auto single : people_) {
    different.insert({single, std::vector<std::pair<int, std::string>>()});
  }
  for (const auto& relationship : relationships) {
    for (const auto& people : people_) {
      for (const auto& other : relations_.find(people)->second) {
        if (other.second == relationship) {
          different.find(people)->second.push_back(other);
        }
      }
    }
  }
  return different;
}
size_t IlliniBook::CountGroups(
    const std::vector<std::string>& relationships) const {
  size_t count = 0;
  std::map<int, std::vector<std::pair<int, std::string>>> different =
      Parent2(relationships);
  std::map<int, bool> visited;
  for (const auto& single : relations_) {
    visited.insert({single.first, false});
  }
  for (const auto& people : people_) {
    std::queue<int> search;
    if (!visited[people]) {
      count++;
      search.push(people);
      visited[people] = true;
      while (!search.empty()) {
        int person = search.front();
        search.pop();
        for (const auto& other : different.find(person)->second) {
          if (!visited[other.first]) {
            visited[other.first] = true;
            search.push(other.first);
          }
        }
      }
    }
  }
  return count;
}