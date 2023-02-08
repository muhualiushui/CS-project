#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP
#include <iostream>
#include <vector>

// Your function declarations should go in this header file.
bool IsUpperCase(char temp_letter);
char UpcaseToLowercase(char word);
std::vector<std::string> AddWords(std::string ArrangedWords);
std::string EnglishToHawa(std::string english);

bool IsVowel(char i);
bool IsVowelGroup(char i, char j);

std::string ArrangementFor3(std::string english, size_t i);
std::string ArrangementFor2(std::string english, size_t i);
std::string ArrangementFor1(std::string english, size_t i);
std::string ArrangementFor0(std::string english, size_t i);

std::string AddLetterFor2(std::string english, size_t i, char add1, char add2);
std::string AddLetterFor3(
    std::string english, size_t i, char add1, char add2, char add3);
std::string AddLetterFor4(
    std::string english, size_t i, char add1, char add2, char add3, char add4);
std::string AddLetterFor5(std::string english,
                          size_t i,
                          char add1,
                          char add2,
                          char add3,
                          char add4,
                          char add5);

std::string Vowel(std::string english, size_t i);
std::string VowelGroupAI(std::string english, size_t i);
std::string VowelGroupAO(std::string english, size_t i);
std::string VowelGroupEI(std::string english, size_t i);
std::string VowelGroupEU(std::string english, size_t i);
std::string VowelGroupOI(std::string english, size_t i);
std::string VowelGroupOU(std::string english, size_t i);
std::string VowelGroupIU(std::string english, size_t i);
std::string VowelGroupUI(std::string english, size_t i);
#endif