#include "board.hpp"

// you might need additional includes
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

/**************************************************************************/
/* your function definitions                                              */
/**************************************************************************/

void InitBoard(Board& b) {
  // below was minimal to get tests to actually compile and given test case to
  // fail
  for (int i = 0; i < Board::kBoardHeight; i++) {
    for (int j = 0; j < Board::kBoardWidth; j++) {
      b.board[i][j] = DiskType::kEmpty;
    }
  }
}

void DropDiskToBoard(Board& b, DiskType disk, int col) {
  int i = 0;
  for (i = 0; i < Board::kBoardHeight; i++) {
    if (b.board[i][col] == DiskType::kEmpty) {
      break;
    }
  }
  if (i == Board::kBoardHeight) {
    throw std::runtime_error("invalid value");
  }
  if (col >= Board::kBoardWidth || col < 0) {
    throw std::runtime_error("invalid value");
  }
  b.board[i][col] = disk;
}
bool CheckForWinner(Board& b, DiskType disk) {
  if (SearchForWinner(b, disk, WinningDirection::kHorizontal)) {
    return true;
  }
  if (SearchForWinner(b, disk, WinningDirection::kVertical)) {
    return true;
  }
  if (SearchForWinner(b, disk, WinningDirection::kRightDiag)) {
    return true;
  }
  if (SearchForWinner(b, disk, WinningDirection::kLeftDiag)) {
    return true;
  }
  return false;
}
bool Horizontal(Board& b, DiskType disk) {
  for (int i = 0; i < Board::kBoardHeight; i++) {
    int count = 0;
    for (int j = 0; j < Board::kBoardWidth; j++) {
      if (b.board[i][j] == disk) {
        count++;
        if (count == 4) {
          return true;
        }
      } else {
        count = 0;
      }
    }
  }
  return false;
}
bool Vertical(Board& b, DiskType disk) {
  for (int i = 0; i < Board::kBoardWidth; i++) {
    int count = 0;
    for (int j = 0; j < Board::kBoardHeight; j++) {
      if (b.board[j][i] == disk) {
        count++;
        if (count == 4) {
          return true;
        }
      } else {
        count = 0;
      }
    }
  }
  return false;
}
bool LeftDiag(Board& b, DiskType disk) {
  int count = 0;
  for (int j = Board::kBoardHeight - 1; j >= 0; j--) {
    count = 0;
    int row = j;
    int col = Board::kBoardWidth - 1;
    while (row < Board::kBoardHeight) {
      if (b.board[row][col] == disk) {
        count++;
        if (count == 4) {
          return true;
        }
      } else {
        count = 0;
      }
      col--;
      row++;
    }
  }
  for (int i = Board::kBoardWidth - 2; i >= 0; i--) {
    count = 0;
    int row = 0;
    int col = i;
    while (col >= 0) {
      if (b.board[row][col] == disk) {
        count++;
        if (count == 4) {
          return true;
        }
      } else {
        count = 0;
      }
      col--;
      row++;
    }
  }
  return false;
}

bool RightDiag(Board& b, DiskType disk) {
  int count = 0;
  for (int j = Board::kBoardHeight - 1; j >= 0; j--) {
    count = 0;
    int row = j;
    int col = 0;
    while (row < Board::kBoardHeight) {
      if (b.board[row][col] == disk) {
        count++;
        if (count == 4) {
          return true;
        }
      } else {
        count = 0;
      }
      col++;
      row++;
    }
  }
  for (int i = 1; i < Board::kBoardWidth; i++) {
    count = 0;
    int row = 0;
    int col = i;
    while (col < Board::kBoardWidth) {
      if (b.board[row][col] == disk) {
        count++;
        if (count == 4) {
          return true;
        }
      } else {
        count = 0;
      }
      col++;
      row++;
    }
  }
  return false;
}

bool SearchForWinner(Board& b, DiskType disk, WinningDirection to_check) {
  if (to_check == WinningDirection::kHorizontal) {
    return Horizontal(b, disk);
  }
  if (to_check == WinningDirection::kLeftDiag) {
    return LeftDiag(b, disk);
  }
  if (to_check == WinningDirection::kRightDiag) {
    return RightDiag(b, disk);
  }
  if (to_check == WinningDirection::kVertical) {
    return Vertical(b, disk);
  }
  return false;
}

bool BoardLocationInBounds(int row, int col) {
  if (row < Board::kBoardHeight && row >= 0) {
    if (col < Board::kBoardWidth && col >= 0) {
      return true;
    }
  }

  return false;
}
/**************************************************************************/
/* provided to you                                                        */
/**************************************************************************/
std::string BoardToStr(const Board& b) {
  constexpr int kTotalWidth = Board::kBoardWidth * 11 - Board::kBoardHeight - 1;
  std::stringstream ss;
  ss << std::endl;
  for (int row = Board::kBoardHeight; row > 0; --row) {
    ss << " |";
    for (int col = 0; col < Board::kBoardWidth; ++col) {
      std::string value_here;
      value_here.push_back(static_cast<char>(b.board[row - 1][col]));
      ss << ' ' << CenterStr(value_here, Board::kBoardWidth + 1) << '|';
    }
    ss << std::endl;
    ss << " |" << std::setw(kTotalWidth) << std::setfill('-') << '|'
       << std::endl;
  }
  ss << " |";
  for (int col = 0; col < Board::kBoardWidth; ++col) {
    ss << ' ' << CenterStr(std::to_string(col), Board::kBoardWidth + 1) << '|';
  }
  return ss.str();
}

std::string CenterStr(const std::string& str, int col_width) {
  // quick and easy (but error-prone) implementation
  auto padl = (col_width - str.length()) / 2;
  auto padr = (col_width - str.length()) - padl;
  std::string strf = std::string(padl, ' ') + str + std::string(padr, ' ');
  return strf;
}