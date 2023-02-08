// clang-format off
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//  Written By : Michael R. Nowak                Environment : ubuntu:latest               //
//  Date ......: 2022/02/07                      Compiler ...: clang-10                    //
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
// clang-format on
/////////////////////////////////////////////////////////////////////////////////////////////
//                             Framework Set-up //
/////////////////////////////////////////////////////////////////////////////////////////////
#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif

#include "catch.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                                 Includes //
/////////////////////////////////////////////////////////////////////////////////////////////
#include <stdexcept>

#include "board.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                             Helpers/Constants //
/////////////////////////////////////////////////////////////////////////////////////////////
constexpr int kBoardWidth = 7;
constexpr int kBoardHeight = 6;

bool AreEqual(DiskType solution[][kBoardWidth],
              DiskType student[][kBoardWidth]) {
  for (int i = 0; i < kBoardHeight; ++i) {
    for (int j = 0; j < kBoardWidth; ++j) {
      if (solution[i][j] != student[i][j]) return false;
    }
  }
  return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//                                Test Cases //
/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("Board initialization", "[board_init]") {
  // SECTION("Can use sections") {}
  // clang-format off
  DiskType solution[kBoardHeight][kBoardWidth] = { 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty} 
  };
  // clang-format on
  Board student;  // NOLINT
  InitBoard(student);
  REQUIRE(AreEqual(solution, student.board));
}

TEST_CASE("right diagno Test") {
  Board b;
  REQUIRE_FALSE(CheckForWinner(b, DiskType::kEmpty));
  InitBoard(b);
  REQUIRE(CheckForWinner(b, DiskType::kEmpty));
  DropDiskToBoard(b, DiskType::kPlayer1, 3);
  DropDiskToBoard(b, DiskType::kPlayer2, 4);
  DropDiskToBoard(b, DiskType::kPlayer1, 4);
  DropDiskToBoard(b, DiskType::kPlayer2, 5);
  DropDiskToBoard(b, DiskType::kPlayer2, 5);
  DropDiskToBoard(b, DiskType::kPlayer1, 5);
  DropDiskToBoard(b, DiskType::kPlayer2, 6);
  DropDiskToBoard(b, DiskType::kPlayer2, 6);
  DropDiskToBoard(b, DiskType::kPlayer2, 6);
  DropDiskToBoard(b, DiskType::kPlayer1, 6);

  SECTION("ALREADY PASSED") {
    REQUIRE(CheckForWinner(b, DiskType::kPlayer1));
    REQUIRE(
        SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kRightDiag));
    REQUIRE_FALSE(CheckForWinner(b, DiskType::kPlayer2));
  }
}

TEST_CASE("OUT OF BOUND") {
  SECTION("IN THE BOUND") {
    REQUIRE(BoardLocationInBounds(5, 0));
    REQUIRE(BoardLocationInBounds(0, 5));
    REQUIRE(BoardLocationInBounds(5, 5));
  }
  SECTION("OUT OF BOUND") {
    REQUIRE_FALSE(BoardLocationInBounds(0, -1));
    REQUIRE_FALSE(BoardLocationInBounds(-1, 2));
    REQUIRE_FALSE(BoardLocationInBounds(-1, -1));
  }
  SECTION("OUT OF BOUND 2") {
    REQUIRE_FALSE(BoardLocationInBounds(100, 0));
    REQUIRE_FALSE(BoardLocationInBounds(0, 100));
    REQUIRE_FALSE(BoardLocationInBounds(100, 100));
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("DROP") {
  Board b;
  InitBoard(b);
  SECTION("INVALID INPUT") {
    REQUIRE_THROWS_AS(DropDiskToBoard(b, DiskType::kPlayer1, -1),
                      std::runtime_error);
    REQUIRE_THROWS_AS(DropDiskToBoard(b, DiskType::kPlayer1, 100),
                      std::runtime_error);
  }
  SECTION("out of a coloum") {
    DropDiskToBoard(b, DiskType::kPlayer1, 6);
    DropDiskToBoard(b, DiskType::kPlayer1, 6);
    DropDiskToBoard(b, DiskType::kPlayer1, 6);
    DropDiskToBoard(b, DiskType::kPlayer1, 6);
    DropDiskToBoard(b, DiskType::kPlayer1, 6);
    DropDiskToBoard(b, DiskType::kPlayer1, 6);
    REQUIRE_THROWS_AS(DropDiskToBoard(b, DiskType::kPlayer1, 6),
                      std::runtime_error);
  }
}

TEST_CASE("NO WINNER") {
  Board b;
  InitBoard(b);
  DropDiskToBoard(b, DiskType::kPlayer2, 6);
  DropDiskToBoard(b, DiskType::kPlayer1, 6);
  DropDiskToBoard(b, DiskType::kPlayer1, 6);
  DropDiskToBoard(b, DiskType::kPlayer2, 6);
  DropDiskToBoard(b, DiskType::kPlayer1, 6);
  DropDiskToBoard(b, DiskType::kPlayer1, 6);

  DropDiskToBoard(b, DiskType::kPlayer1, 5);
  DropDiskToBoard(b, DiskType::kPlayer1, 5);
  DropDiskToBoard(b, DiskType::kPlayer1, 5);
  DropDiskToBoard(b, DiskType::kPlayer2, 5);
  DropDiskToBoard(b, DiskType::kPlayer1, 5);
  DropDiskToBoard(b, DiskType::kPlayer1, 5);

  DropDiskToBoard(b, DiskType::kPlayer2, 0);
  DropDiskToBoard(b, DiskType::kPlayer1, 0);
  DropDiskToBoard(b, DiskType::kPlayer1, 0);
  DropDiskToBoard(b, DiskType::kPlayer2, 0);
  DropDiskToBoard(b, DiskType::kPlayer1, 0);
  DropDiskToBoard(b, DiskType::kPlayer1, 0);

  DropDiskToBoard(b, DiskType::kPlayer1, 1);
  DropDiskToBoard(b, DiskType::kPlayer1, 1);
  DropDiskToBoard(b, DiskType::kPlayer1, 1);
  DropDiskToBoard(b, DiskType::kPlayer2, 1);
  DropDiskToBoard(b, DiskType::kPlayer1, 1);
  DropDiskToBoard(b, DiskType::kPlayer1, 1);

  DropDiskToBoard(b, DiskType::kPlayer1, 2);
  DropDiskToBoard(b, DiskType::kPlayer1, 2);
  DropDiskToBoard(b, DiskType::kPlayer1, 2);
  DropDiskToBoard(b, DiskType::kPlayer2, 2);
  DropDiskToBoard(b, DiskType::kPlayer2, 2);
  DropDiskToBoard(b, DiskType::kPlayer2, 2);

  DropDiskToBoard(b, DiskType::kPlayer2, 3);
  DropDiskToBoard(b, DiskType::kPlayer2, 3);
  DropDiskToBoard(b, DiskType::kPlayer2, 3);
  DropDiskToBoard(b, DiskType::kPlayer1, 3);
  DropDiskToBoard(b, DiskType::kPlayer2, 3);
  DropDiskToBoard(b, DiskType::kPlayer2, 3);

  DropDiskToBoard(b, DiskType::kPlayer1, 4);
  DropDiskToBoard(b, DiskType::kPlayer1, 4);
  DropDiskToBoard(b, DiskType::kPlayer1, 4);
  DropDiskToBoard(b, DiskType::kPlayer2, 4);
  DropDiskToBoard(b, DiskType::kPlayer2, 4);
  DropDiskToBoard(b, DiskType::kPlayer2, 4);

  REQUIRE_FALSE(CheckForWinner(b, DiskType::kPlayer1));
  REQUIRE_FALSE(CheckForWinner(b, DiskType::kPlayer2));
}