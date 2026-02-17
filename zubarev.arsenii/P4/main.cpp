#include "input.hpp"

namespace zubarev
{
  size_t strlen(const char* s);
  bool inStr(const char* const str, const char let);
  int solveSpliceStr(const char* mainStr, const char* secondStr, char* finalStr);
  int solveUniInAlp(const char* const mainStr, char* buf);
}

int main()
{
  namespace zub = zubarev;
  size_t mainSize = 0;
  size_t capacity = 0;
  char** myWords = nullptr;

  std::cout << "Enter words: ";

  try {
    myWords = zub::getWords(std::cin, mainSize, capacity, &zub::isSpace);
  } catch (const std::bad_alloc&) {
    std::cerr << "Memory allocation failed\n";
    return 1;
  }
  if (mainSize == 0) {
    std::cerr << "Input wrong\n";
    return 1;
  }
  std::cout << '\n';

  for (size_t i = 0; i < mainSize; ++i) {
    std::cout << "Word [" << i << "]: " << myWords[i] << '\n';
    const char* secondStr = "def_";
    size_t secondSize = zub::strlen(secondStr);

    size_t currentWordLen = zub::strlen(myWords[i]);
    size_t finalSize = secondSize + currentWordLen;
    char* finalStr = nullptr;

    try {
      finalStr = new char[finalSize + 1];
    } catch (const std::bad_alloc&) {
      std::cerr << "Memory allocation failed\n";
      for (size_t i = 0; i < mainSize; ++i) {
        delete[] myWords[i];
      }
      delete[] myWords;
      return 1;
    }
    zub::solveSpliceStr(myWords[i], secondStr, finalStr);
    std::cout << finalStr << '\n';
    delete[] finalStr;

    size_t endSize = 0;
    char* endStr = nullptr;
    try {
      endSize = 26;
      endStr = new char[endSize + 1];
    } catch (const std::bad_alloc&) {
      std::cerr << "Memory allocation failed\n";
      for (size_t i = 0; i < mainSize; ++i) {
        delete[] myWords[i];
      }
      delete[] myWords;
      return 1;
    }

    zub::solveUniInAlp(myWords[i], endStr);
    std::cout << endStr << '\n';
    delete[] endStr;

    delete[] myWords[i];
  }

  delete[] myWords;
}

size_t zubarev::strlen(const char* s)
{
  size_t len = 0;
  while (s[len] != '\0') {
    len++;
  }
  return len;
}

int zubarev::solveSpliceStr(const char* mainStr, const char* secondStr, char* finalStr)
{
  while (*mainStr != '\0' || *secondStr != '\0') {
    if (*mainStr != '\0') {
      *(finalStr++) = *(mainStr++);
    }

    if (*secondStr != '\0') {
      *(finalStr++) = *(secondStr++);
    }
  }
  *finalStr = '\0';
  return 0;
}

bool zubarev::inStr(const char* const str, const char let)
{
  for (const char* i = str; *i != '\0'; ++i) {
    if (std::tolower(*i) == std::tolower(let)) {
      return true;
    }
  }
  return false;
}

int zubarev::solveUniInAlp(const char* const mainStr, char* buf)
{
  const char* alphabet = "abcdefghijklmnopqrstuvwxyz";

  for (const char* i = alphabet; *i != '\0'; ++i) {
    if (!(inStr(mainStr, *i))) {
      *(buf++) = *i;
    }
  }
  *buf = '\0';
  return 0;
}
