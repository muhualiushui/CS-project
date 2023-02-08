#include <iostream>
#include <string>

#include "functions.hpp"

int main(int argc, char** argv) {
  if (argc != 2) {
    std::cerr << "Usage: ./bin/exec word" << std::endl;
    return 1;
  }
  std::string word = argv[1];
  for (std::size_t i = 0; i < word.size();
       i++) {                                // transit all upper case letter to
    if (IsUpperCase(word[i])) {              // if it is upper case letter
      word[i] = UpcaseToLowercase(word[i]);  // turn into lower case
    }
  }
  std::vector<std::string> transitory =
      AddWords(word);  // single word store into vector
  std::string english;
  std::string hawa;

  for (std::size_t i = 0; i < transitory.size();
       i++) {  // translate English to Hawa
    english = transitory[i];
    hawa += EnglishToHawa(english);
    hawa += ' ';
  }
  bool output = true;
  for (size_t j = 0; j < hawa.size(); j++) {
    if (!(bool)isalpha(hawa[j + 1]) && hawa[j] == '-') {
      hawa.erase(j, 1);
    }

    if (hawa[j] == 'z' || hawa[j] == 'd') {
      output = false;
    }
  }
  if (output)
    std::cout << hawa << std::endl;
  else
    std::cout << "contains a character not a part of the Hawaiian language."
              << std::endl;
}