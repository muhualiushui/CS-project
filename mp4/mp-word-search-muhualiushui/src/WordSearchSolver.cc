#include "WordSearchSolver.hpp"

#include <iostream>
bool WordSearchSolver::LocationInBounds(size_t row, size_t col) const {
  return ((row < puzzle_height_) && (col < puzzle_width_));
}

WordSearchSolver::WordSearchSolver(  // initialize the vector
    const std::vector<std::vector<char>>& puzzle) {
  WordSearchSolver::puzzle_height_ = puzzle.size();
  WordSearchSolver::puzzle_width_ = puzzle[0].size();
  for (size_t i = 0; i < puzzle.size(); i++) {
    WordSearchSolver::puzzle_.push_back(puzzle[i]);
  }
}

CharPositions SingleChar(char charactor,
                         size_t i,
                         size_t j) {  // add element of char and position
  CharPositions single_char = {};
  single_char.character = charactor;
  single_char.row = i;
  single_char.col = j;
  return single_char;
}

WordLocation WordSearchSolver::Horizontal(const std::string& word,
                                          int& test) {  // horizontal direction
  WordLocation valid_result;
  valid_result.word = word;
  for (size_t i = 0; i < WordSearchSolver::puzzle_height_; i++) {
    size_t count = 0;
    for (size_t j = 0; j < WordSearchSolver::puzzle_width_; j++) {
      if (WordSearchSolver::puzzle_[i][j] == word.at(count)) {
        valid_result.char_positions.push_back(SingleChar(word.at(count), i, j));
        count++;
        if (count == word.length()) {
          test = 1;
          return valid_result;
        }
      } else {
        valid_result.char_positions.clear();
        count = 0;
      }
    }
    valid_result.char_positions.clear();
  }
  return WordLocation{};
}

WordLocation WordSearchSolver::Vertical(const std::string& word,
                                        int& test) {  // vertical direction
  WordLocation valid_result;
  valid_result.word = word;
  for (size_t j = 0; j < WordSearchSolver::puzzle_width_; j++) {
    size_t count = 0;
    for (size_t i = 0; i < WordSearchSolver::puzzle_height_; i++) {
      if (WordSearchSolver::puzzle_[i][j] == word.at(count)) {
        valid_result.char_positions.push_back(SingleChar(word.at(count), i, j));
        count++;
        if (count == word.length()) {
          test = 1;
          return valid_result;
        }
      } else {
        if (count > 0) {
          i--;
        }
        valid_result.char_positions.clear();
        count = 0;
      }
    }
    valid_result.char_positions.clear();
  }
  return WordLocation{};
}

bool WordSearchSolver::LeftCheck(WordLocation& valid_result,
                                 std::string word) {  // initial check
  size_t row = 0;
  size_t col = WordSearchSolver::puzzle_width_ - 1;
  size_t times = 0;
  while (times < WordSearchSolver::puzzle_width_) {
    size_t count = 0;
    while (WordSearchSolver::LocationInBounds(row, col)) {
      if (WordSearchSolver::puzzle_[row][col] == word.at(count)) {
        valid_result.char_positions.push_back(
            SingleChar(word.at(count), row, col));
        count++;
        if (count == word.length()) {
          return true;
        }
      } else {
        if (count > 0) {
          row--;
          col++;
        }
        valid_result.char_positions.clear();
        count = 0;
      }
      row++;
      col--;
    }
    valid_result.char_positions.clear();
    times++;
    col = WordSearchSolver::puzzle_width_ - 1 - times;
    row = 0;
  }
  valid_result.char_positions.clear();
  return false;
}

WordLocation WordSearchSolver::LeftDiag(const std::string& word,
                                        int& test) {  // left diagno
  WordLocation valid_result;
  valid_result.word = word;
  if (WordSearchSolver::LeftCheck(valid_result, word)) {
    test = 1;
    return valid_result;
  }
  size_t times = 1;
  size_t col = WordSearchSolver::puzzle_width_ - 1;
  size_t row = times;
  while (times < WordSearchSolver::puzzle_height_) {
    size_t count = 0;
    while (WordSearchSolver::LocationInBounds(row, col)) {
      if (WordSearchSolver::puzzle_[row][col] == word.at(count)) {
        valid_result.char_positions.push_back(
            SingleChar(word.at(count), row, col));
        count++;
        if (count == word.length()) {
          test = 1;
          return valid_result;
        }
      } else {
        if (count > 0) {
          row--;
          col++;
        }
        valid_result.char_positions.clear();
        count = 0;
      }
      row++;
      col--;
    }
    valid_result.char_positions.clear();
    times++;
    col = WordSearchSolver::puzzle_width_ - 1;
    row = times;
  }
  valid_result.char_positions.clear();
  return WordLocation{};
  ;
}

bool WordSearchSolver::RightCheck(WordLocation& valid_result,
                                  std::string word) {  // initial check
  size_t row = 0;
  size_t col = 0;
  size_t times = 0;
  while (times < WordSearchSolver::puzzle_width_) {
    size_t count = 0;
    while (WordSearchSolver::LocationInBounds(row, col)) {
      if (WordSearchSolver::puzzle_[row][col] == word.at(count)) {
        valid_result.char_positions.push_back(
            SingleChar(word.at(count), row, col));
        count++;
        if (count == word.length()) {
          return true;
        }
      } else {
        valid_result.char_positions.clear();
        count = 0;
      }
      row++;
      col++;
    }
    valid_result.char_positions.clear();
    times++;
    col = times;
    row = 0;
  }
  valid_result.char_positions.clear();
  return false;
}

WordLocation WordSearchSolver::RightDiag(const std::string& word,
                                         int& test) {  // Right diagno
  WordLocation valid_result;
  valid_result.word = word;
  if (WordSearchSolver::RightCheck(valid_result, word)) {
    test = 1;
    return valid_result;
  }
  size_t times = 1;
  size_t col = 0;
  size_t row = times;
  while (times < WordSearchSolver::puzzle_height_) {
    size_t count = 0;
    while (WordSearchSolver::LocationInBounds(row, col)) {
      if (WordSearchSolver::puzzle_[row][col] == word.at(count)) {
        valid_result.char_positions.push_back(
            SingleChar(word.at(count), row, col));
        count++;
        if (count == word.length()) {
          test = 1;
          return valid_result;
        }
      } else {
        valid_result.char_positions.clear();
        count = 0;
      }
      row++;
      col++;
    }
    valid_result.char_positions.clear();
    times++;
    col = 0;
    row = times;
  }
  valid_result.char_positions.clear();
  return WordLocation{};
}

WordLocation WordSearchSolver::FindWord(const std::string& word,
                                        CheckDirection direction) {
  int test = 0;
  switch (direction) {
  case CheckDirection::kHorizontal:
    return Horizontal(word, test);
    break;
  case CheckDirection::kLeftDiag:
    return LeftDiag(word, test);
    break;
  case CheckDirection::kRightDiag:
    return RightDiag(word, test);
    break;
  case CheckDirection::kVertical:
    return Vertical(word, test);
    break;
  default:
    return WordLocation{};
    break;
  }
}

WordLocation WordSearchSolver::FindWord(const std::string& word) {
  int test = 0;
  WordLocation valid_result1 = Horizontal(word, test);
  if (test == 1) {
    return Horizontal(word, test);
  }
  WordLocation valid_result2 = LeftDiag(word, test);
  if (test == 1) {
    return LeftDiag(word, test);
  }
  WordLocation valid_result3 = RightDiag(word, test);
  if (test == 1) {
    return RightDiag(word, test);
  }
  WordLocation valid_result4 = Vertical(word, test);
  if (test == 1) {
    return Vertical(word, test);
  }

  return WordLocation{};
}
