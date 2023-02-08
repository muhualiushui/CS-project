// clang-format off
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//  Written By : Student Name                    Environment : ubuntu:bionic               //
//  Date ......: 2021/02/10                      Compiler ...: clang-10                    //
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
// clang-format on
/////////////////////////////////////////////////////////////////////////////////////////////
//                             Framework Set-up //
/////////////////////////////////////////////////////////////////////////////////////////////
#include "catch.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                                 Includes //
/////////////////////////////////////////////////////////////////////////////////////////////
#include <stdexcept>
#include <iostream>
#include "CharPositions.hpp"
#include "WordLocation.hpp"
#include "WordSearchSolver.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                             Helpers/Constants //
/////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////
//                                Test Cases //
/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("pass") {
  std::vector<std::vector<char>> puzzle{{'d', 'e', 'a', 'o', 'u'},
                                        {'h', 'e', 'l', 'l', 'o'},
                                        {'c', 'a', 'l', 'o', 'm'},
                                        {'a', 'e', 't', 'a', 'u'},
                                        {'t', 'e', 't', 'o', 'u'}};
  WordSearchSolver wss(puzzle);
  SECTION("HORIZONTAL") {
    REQUIRE(wss.FindWord("hello").word == "hello");
    REQUIRE(wss.FindWord("hello", CheckDirection::kHorizontal).word == "hello");
    REQUIRE(wss.FindWord("hello").word ==
            wss.FindWord("hello", CheckDirection::kHorizontal).word);
    REQUIRE(wss.FindWord("hello").char_positions[3].character == 'l');
    REQUIRE(wss.FindWord("hello").char_positions[3].row == 1);
    REQUIRE(wss.FindWord("hello").char_positions[3].col == 3);
    REQUIRE(wss.FindWord("hello", CheckDirection::kHorizontal)
                .char_positions[3]
                .character == 'l');
    REQUIRE(wss.FindWord("hello", CheckDirection::kHorizontal)
                .char_positions[3]
                .row == 1);
    REQUIRE(wss.FindWord("hello", CheckDirection::kHorizontal)
                .char_positions[3]
                .col == 3);
    for (size_t i = 0; i < wss.FindWord("hello").char_positions.size(); i++) {
      REQUIRE(wss.FindWord("hello").word.at(i) ==
              wss.FindWord("hello").char_positions[i].character);
      REQUIRE(wss.FindWord("hello").char_positions[i].row ==
              wss.FindWord("hello").char_positions[i].row);
      REQUIRE(wss.FindWord("hello").char_positions[i].col ==
              wss.FindWord("hello").char_positions[i].col);
    }
  }
  SECTION("vertival") {
    REQUIRE(wss.FindWord("eeaee").word == "eeaee");
    REQUIRE(wss.FindWord("eeaee", CheckDirection::kVertical).word == "eeaee");
    REQUIRE(wss.FindWord("eeaee").word ==
            wss.FindWord("eeaee", CheckDirection::kVertical).word);
    for (size_t i = 0; i < wss.FindWord("eeaee").char_positions.size(); i++) {
      REQUIRE(wss.FindWord("eeaee").word.at(i) ==
              wss.FindWord("eeaee").char_positions[i].character);
    }
  }
  SECTION("leftdiagno") {
    REQUIRE(wss.FindWord("ullet").word == "ullet");
    REQUIRE(wss.FindWord("ullet", CheckDirection::kLeftDiag).word == "ullet");
    REQUIRE(wss.FindWord("ullet").word ==
            wss.FindWord("ullet", CheckDirection::kLeftDiag).word);
    for (size_t i = 0; i < wss.FindWord("ullet").char_positions.size(); i++) {
      REQUIRE(wss.FindWord("ullet").word.at(i) ==
              wss.FindWord("ullet").char_positions[i].character);
    }
  }
  SECTION("rightdiagno") {
    REQUIRE(wss.FindWord("delau").word == "delau");
    REQUIRE(wss.FindWord("delau", CheckDirection::kRightDiag).word == "delau");
    REQUIRE(wss.FindWord("delau").word ==
            wss.FindWord("delau", CheckDirection::kRightDiag).word);
    for (size_t i = 0; i < wss.FindWord("delau").char_positions.size(); i++) {
      REQUIRE(wss.FindWord("delau").word.at(i) ==
              wss.FindWord("delau").char_positions[i].character);
    }
  }
}

TEST_CASE("NOT PASS") {
  std::vector<std::vector<char>> puzzle{{'d', 'e', 'a', 'o', 'u'},
                                        {'h', 'e', 'l', 'l', 'o'},
                                        {'c', 'a', 'l', 'o', 'm'},
                                        {'a', 'e', 't', 'a', 'u'},
                                        {'t', 'e', 't', 'o', 'u'}};
  WordSearchSolver wss(puzzle);
  REQUIRE_FALSE(wss.FindWord("hell").word == "hello");
  REQUIRE_FALSE(wss.FindWord("eeaee", CheckDirection::kHorizontal).word ==
                "eeaee");
  REQUIRE_FALSE(wss.FindWord("hello", CheckDirection::kVertical).word ==
                "hello");
  REQUIRE_FALSE(wss.FindWord("hello", CheckDirection::kLeftDiag).word ==
                "hello");
  REQUIRE_FALSE(wss.FindWord("hello", CheckDirection::kRightDiag).word ==
                "hello");

  REQUIRE_FALSE(wss.FindWord("hell", CheckDirection::kHorizontal).word ==
                "hello");
  REQUIRE_FALSE(wss.FindWord("eeae", CheckDirection::kVertical).word ==
                "eeaee");
  REQUIRE_FALSE(wss.FindWord("ulle", CheckDirection::kLeftDiag).word ==
                "ullet");
  REQUIRE_FALSE(wss.FindWord("dela", CheckDirection::kRightDiag).word ==
                "delau");
  REQUIRE_FALSE(wss.FindWord(" ").word == "hello");
  REQUIRE_FALSE(wss.FindWord(" ", CheckDirection::kHorizontal).word == "hello");
}

TEST_CASE("pass2") {
  std::vector<std::vector<char>> puzzle{{'d', 'e', 'a', 'o'},
                                        {'h', 'e', 'l', 'l'},
                                        {'c', 'a', 'l', 'o'},
                                        {'a', 'e', 't', 'a'},
                                        {'t', 'e', 't', 'o'}};
  WordSearchSolver wss(puzzle);
  SECTION("HORIZONTAL") {
    REQUIRE(wss.FindWord("del").word == "del");
    REQUIRE(wss.FindWord("hell", CheckDirection::kHorizontal).word == "hell");
    REQUIRE(wss.FindWord("hell").word ==
            wss.FindWord("hell", CheckDirection::kHorizontal).word);
    REQUIRE(wss.FindWord("hell").char_positions[3].character == 'l');
    REQUIRE(wss.FindWord("hell").char_positions[3].row == 1);
    REQUIRE(wss.FindWord("hell").char_positions[3].col == 3);
    REQUIRE_FALSE(wss.FindWord("hall").word == "hall");
    REQUIRE(wss.FindWord("del", CheckDirection::kRightDiag).word == "del");
    REQUIRE(wss.FindWord("ola", CheckDirection::kLeftDiag).word == "ola");
    REQUIRE(wss.FindWord("dhc", CheckDirection::kVertical).word == "dhc");
    REQUIRE_FALSE(wss.FindWord("hall", CheckDirection::kHorizontal).word ==
                  "hall");
  }
}

TEST_CASE("pass3") {
  std::vector<std::vector<char>> puzzle{{'d', 'e', 'a', 'o', 'u'},
                                        {'h', 'e', 'l', 'l', 'o'},
                                        {'c', 'a', 'l', 'o', 'm'}};
  WordSearchSolver wss(puzzle);

  REQUIRE(wss.FindWord("del").word == "del");
  REQUIRE(wss.FindWord("hell", CheckDirection::kHorizontal).word == "hell");
  REQUIRE(wss.FindWord("hell").word ==
          wss.FindWord("hell", CheckDirection::kHorizontal).word);
  REQUIRE(wss.FindWord("hell").char_positions[3].character == 'l');
  REQUIRE(wss.FindWord("hell").char_positions[3].row == 1);
  REQUIRE(wss.FindWord("hell").char_positions[3].col == 3);
  REQUIRE_FALSE(wss.FindWord("hall").word == "hall");
  REQUIRE(wss.FindWord("del", CheckDirection::kRightDiag).word == "del");
  REQUIRE(wss.FindWord("ola", CheckDirection::kLeftDiag).word == "ola");
  REQUIRE(wss.FindWord("dhc", CheckDirection::kVertical).word == "dhc");
  REQUIRE_FALSE(wss.FindWord("hall", CheckDirection::kHorizontal).word ==
                "hall");
}
/////////////////////////////////////////////////////////////////////////////////////////////