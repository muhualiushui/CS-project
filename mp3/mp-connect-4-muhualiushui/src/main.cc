#include <iostream>

#include "board.hpp"

int main() {
  Board b;
  InitBoard(b);
  // DropDiskToBoard(b, DiskType::kPlayer1, 3);
  // DropDiskToBoard(b, DiskType::kPlayer2, 4);
  // DropDiskToBoard(b, DiskType::kPlayer1, 4);
  // DropDiskToBoard(b, DiskType::kPlayer2, 5);
  // DropDiskToBoard(b, DiskType::kPlayer2, 5);
  // DropDiskToBoard(b, DiskType::kPlayer1, 5);
  // DropDiskToBoard(b, DiskType::kPlayer2, 6);
  // DropDiskToBoard(b, DiskType::kPlayer2, 6);
  // DropDiskToBoard(b, DiskType::kPlayer2, 6);
  // DropDiskToBoard(b, DiskType::kPlayer1, 6);

  DropDiskToBoard(b, DiskType::kPlayer1, 6);
  DropDiskToBoard(b, DiskType::kPlayer2, 5);
  DropDiskToBoard(b, DiskType::kPlayer1, 5);
  DropDiskToBoard(b, DiskType::kPlayer2, 4);
  DropDiskToBoard(b, DiskType::kPlayer2, 4);
  DropDiskToBoard(b, DiskType::kPlayer1, 4);
  DropDiskToBoard(b, DiskType::kPlayer2, 3);
  DropDiskToBoard(b, DiskType::kPlayer2, 3);
  DropDiskToBoard(b, DiskType::kPlayer2, 3);
  DropDiskToBoard(b, DiskType::kPlayer1, 3);
  std::cout << BoardToStr(b) << std::endl;
  if (CheckForWinner(b, DiskType::kPlayer1)) {
    std::cout << "win" << std::endl;
  }
}