#include <iostream>
#include <iomanip>
#include <cctype>

namespace zubarev
{
  void pushOneElAmort(char** arr, size_t& size, size_t& capacity, char value);
  void pushOneWordAmort(char*** arr, size_t& size, size_t& capacity, char* word);

  bool isSpace(char letter);
  char** getWords(std::istream& in, size_t& size, size_t& capacity, bool (*isSpace)(char ch));

  std::ostream& outputMatrix(std::ostream& out, const char* const str, const size_t size);
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

void zubarev::pushOneElAmort(char** arr, size_t& size, size_t& capacity, char value)
{
  if (size + 1 >= capacity) {
    capacity = (capacity == 0) ? 2 : capacity * 2;
    char* newArr = new char[capacity];

    for (size_t i = 0; i < size; i++) {
      newArr[i] = (*arr)[i];
    }

    delete[] *arr;
    *arr = newArr;
  }
  (*arr)[size] = value;
  size++;
}
void zubarev::pushOneWordAmort(char*** arr, size_t& size, size_t& capacity, char* word)
{
  if (size + 1 >= capacity) {
    capacity = (capacity == 0) ? 2 : capacity * 2;
    char** newArr = new char*[capacity];

    for (size_t i = 0; i < size; i++) {
      newArr[i] = (*arr)[i];
    }

    delete[] *arr;
    *arr = newArr;
  }
  (*arr)[size] = word;
  size++;
}
char** zubarev::getWords(std::istream& in, size_t& size, size_t& capacity, bool (*isSpace)(char ch))
{
  char let = ' ';
  char** data = nullptr;

  bool is_skipws = in.flags() & std::ios_base::skipws;
  if (is_skipws) {
    in >> std::noskipws;
  }

  char* curData = nullptr;
  size_t curSize = 0;
  size_t curCapacity = 0;

  while (in >> let && let != '\n') {

    if (isSpace(let) && curSize > 0) {
      pushOneElAmort(&curData, curSize, curCapacity, '\0');
      pushOneWordAmort(&data, size, capacity, curData);
      curData = nullptr;
      curSize = 0;
      curCapacity = 0;
    } else if (!isSpace(let)) {
      pushOneElAmort(&curData, curSize, curCapacity, let);
    }
  }

  if (curSize > 0) {
    pushOneElAmort(&curData, curSize, curCapacity, '\0');
    pushOneWordAmort(&data, size, capacity, curData);
  }

  if (is_skipws) {
    in >> std::skipws;
  }

  return data;
}
bool zubarev::isSpace(char letter)
{
  return letter == ' ';
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
