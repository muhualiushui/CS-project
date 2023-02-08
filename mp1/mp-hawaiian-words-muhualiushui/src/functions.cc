#include "functions.hpp"
const int kDaysInAWeek = 5;
// Your function definitions should go in this source file.

bool IsUpperCase(char temp_letter) {
  if (temp_letter + 1 - 1 <= 'Z' + 1 - 1 &&
      temp_letter + 1 - 1 >= 'A' + 1 - 1) {
    return true;
  }
  return (bool)false;
}

char UpcaseToLowercase(char word) {
  word = (char)(word + 'a' - 'A');
  return word;
}

std::vector<std::string> AddWords(std::string ArrangedWords) {
  std::vector<std::string> store_string;
  int count = 0;
  int j = 0;
  for (size_t i = 0; i < ArrangedWords.size(); i++) {
    if (ArrangedWords[i] != ' ') {
      count++;
      if (i + 1 == ArrangedWords.size()) {
        store_string.push_back(ArrangedWords.substr(j, count + 1));
      }
    } else {
      store_string.push_back(ArrangedWords.substr(j, count));
      j = i;
      count = 0;
      j++;
    }
  }
  return store_string;
}

bool IsVowel(char i) {
  if (i == 'a' || i == 'o' || i == 'e' || i == 'i' || i == 'u') {
    return true;
  }
  return (bool)false;
}

bool IsVowelGroup(char i, char j) {
  if (i == 'a') {
    if (j == 'i' || j == 'e' || j == 'o' || j == 'u') {
      return true;
    }
  } else if (i == 'o') {
    if (j == 'i' || j == 'u') {
      return true;
    }
  } else if ((i == 'i' && j == 'u') || (i == 'u' && j == 'i')) {
    return true;
  }
  if (i == 'e') {
    if (j == 'i' || j == 'u') {
      return true;
    }
  }
  return (bool)false;
}

std::string ArrangementFor0(std::string english, size_t i) {
  english += " ";
  for (size_t j = english.size() - 1; j > i; j--) {
    english[j] = english[j - 1];
  }
  return english;
}

std::string ArrangementFor1(std::string english, size_t i) {
  english += " ";
  for (size_t j = english.size() - 1; j > i; j--) {
    english[j] = english[j - 2];
  }
  return english;
}

std::string ArrangementFor2(std::string english, size_t i) {
  english += " ";
  for (size_t j = english.size() - 1; j > i; j--) {
    english[j] = english[j - 3];
  }
  return english;
}

std::string ArrangementFor3(std::string english, size_t i) {
  english += " ";
  for (size_t j = english.size() - 1; j > i; j--) {
    english[j] = english[j - 4];
  }
  return english;
}

std::string AddLetterFor2(std::string english, size_t i, char add1, char add2) {
  english[i] = add1;
  english[i + 1] = add2;
  return english;
}

std::string AddLetterFor3(
    std::string english, size_t i, char add1, char add2, char add3) {
  english[i] = add1;
  english[i + 1] = add2;
  english[i + 2] = add3;
  return english;
}

std::string AddLetterFor4(
    std::string english, size_t i, char add1, char add2, char add3, char add4) {
  english[i] = add1;
  english[i + 1] = add2;
  english[i + 2] = add3;
  english[i + 3] = add4;
  return english;
}

std::string AddLetterFor5(std::string english,
                          size_t i,
                          char add1,
                          char add2,
                          char add3,
                          char add4,
                          char add5) {
  english[i] = add1;
  english[i + 1] = add2;
  english[i + 2] = add3;
  english[i + 3] = add4;
  english[i + 4] = add5;
  return english;
}

std::string Vowel(std::string english, size_t i) {
  english += " ";
  if (i != english.size() - 2) {
    english = ArrangementFor1(english, i);
    english[i + 2] = '-';
  }
  if (english[i] == 'i') {
    english = AddLetterFor2(english, i, 'e', 'e');

  } else if (english[i] == 'u') {
    english = AddLetterFor2(english, i, 'o', 'o');

  } else {
    english[i + 1] = 'h';
  }
  return english;
}

std::string VowelGroupAI(std::string english, size_t i) {
  english += " ";
  if (i < english.size() - 3) {
    english = ArrangementFor1(english, i);
    english[i + 3] = '-';
  }
  english = AddLetterFor3(english, i, 'e', 'y', 'e');
  return english;
}

std::string VowelGroupAO(std::string english, size_t i) {
  if (i < english.size() - 2) {
    english = ArrangementFor0(english, i);
    english[i + 2] = '-';
  }
  english = AddLetterFor2(english, i, 'o', 'w');
  return english;
}

std::string VowelGroupEI(std::string english, size_t i) {
  if (i < english.size() - 2) {
    english = ArrangementFor0(english, i);
    english[i + 2] = '-';
  }
  english = AddLetterFor2(english, i, 'a', 'y');
  return english;
}

std::string VowelGroupEU(std::string english, size_t i) {
  english += "   ";
  if (i < english.size() - kDaysInAWeek) {
    english = ArrangementFor2(english, i);
    english[i + kDaysInAWeek] = '-';
  }
  english = AddLetterFor5(english, i, 'e', 'h', '-', 'o', 'o');
  return english;
}
std::string VowelGroupOI(std::string english, size_t i) {
  if (i < english.size() - 2) {
    english = ArrangementFor0(english, i);
    english[i + 2] = '-';
  }
  english = AddLetterFor2(english, i, 'o', 'y');
  return english;
}
std::string VowelGroupOU(std::string english, size_t i) {
  if (i < english.size() - 2) {
    english = ArrangementFor0(english, i);
    english[i + 2] = '-';
  }
  english = AddLetterFor2(english, i, 'o', 'w');
  return english;
}

std::string VowelGroupIU(std::string english, size_t i) {
  if (i < english.size() - 2) {
    english = ArrangementFor0(english, i);
    english[i + 2] = '-';
  }
  english = AddLetterFor2(english, i, 'e', 'w');
  return english;
}

std::string VowelGroupUI(std::string english, size_t i) {
  english += "  ";
  if (i < english.size() - 4) {
    english = ArrangementFor2(english, i);
    english[i + 4] = '-';
  }
  english = AddLetterFor4(english, i, 'o', 'o', 'e', 'y');
  return english;
}

std::string EnglishToHawa(std::string english) {
  for (size_t i = 0; i < english.size(); i++) {
    if ((english[i] == 'i' || english[i] == 'e') && english[i + 1] == 'w')
      english[i + 1] = 'v';
    if (IsVowelGroup(english[i], english[i + 1])) {
      if (english[i] == 'a') {                                 // a
        if (english[i + 1] == 'i' || english[i + 1] == 'e') {  // ai ae
          english = VowelGroupAI(english, i);
          i += 1;
        } else if (english[i + 1] == 'o' || english[i + 1] == 'u') {  // ao au
          english = VowelGroupAO(english, i);
        }
      } else if (english[i] == 'e') {  // a
        if (english[i + 1] == 'i') {   // ei
          english = VowelGroupEI(english, i);
        } else if (english[i + 1] == 'u') {  // eu
          english = VowelGroupEU(english, i);
          i += 2;
        }
      } else if (english[i] == 'o') {  // o
        if (english[i + 1] == 'i') {   // oi
          english = VowelGroupOI(english, i);
        } else if (english[i + 1] == 'u') {  // ou
          english = VowelGroupOU(english, i);
        }
      } else if (english[i] == 'i' && english[i + 1] == 'u') {
        english = VowelGroupIU(english, i);
      } else if (english[i] == 'u' && english[i + 1] == 'i') {
        english = VowelGroupUI(english, i);
        i += 2;
      }
      i += 2;
    } else if (IsVowel(english[i]) &&
               !IsVowelGroup(english[i], english[i + 1])) {
      english = Vowel(english, i);
      i++;
    }
  }
  return english;
}
