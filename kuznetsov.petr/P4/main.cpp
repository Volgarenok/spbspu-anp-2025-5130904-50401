#include <iostream>
#include <cctype>
#include "read_string.hpp"
#include "read_words.hpp"

namespace kuznetsov {
  void removeVow(char* buff, const char* str);
  int checkSeqSym(const char* str);
  bool isSpace(char t);
  void deleting(char** arr, size_t k);
}

int main()
{
  namespace kuz = kuznetsov;
  size_t size = 0;
  char** str = nullptr;
  size_t* sizes = nullptr;

  str = kuz::getWords(std::cin, size, &sizes, kuz::isSpace);

  if (!std::cin) {
    kuz::deleting(str, size);
    delete[] sizes;
    return 1;
  }
  for (size_t i = 0; i < size; ++i) {
    char* buffer = nullptr;
    try {
      buffer = new char[sizes[i] + 1] {};
    } catch (const std::bad_alloc&) {
      delete[] sizes;
      kuz::deleting(str, size);
      std::cerr << "Bad alloc buffer\n";
      return 2;
    }

    kuz::removeVow(buffer, str[i]);
    std::cout << buffer << '\n';
    std::cout << kuz::checkSeqSym(str[i]) << '\n';

    delete[] buffer;
  }

  delete[] sizes;
  kuz::deleting(str, size);
}

bool kuznetsov::isSpace(char t)
{
  return std::isspace(t);
}

void kuznetsov::deleting(char** arr, size_t k)
{
  for (size_t i = 0; i < k; ++i) {
    delete[] arr[i];
  }
  delete[] arr;
}

void kuznetsov::removeVow(char* buff, const char* str)
{
  char vow[] = "aeiou";
  size_t nextPast = 0;
  for (size_t i = 0; str[i] != '\0'; ++i ) {
    size_t j = 0;
    for (; j < 5; ++j) {
      if (tolower(str[i]) == vow[j]) {
        break;
      }
    }
    if (j == 5) {
      buff[nextPast] = str[i];
      nextPast++;
    }
  }
  buff[nextPast] = '\0';
}

int kuznetsov::checkSeqSym(const char* str)
{
  if (str[0] == '\0') {
    return 0;
  }
  for (size_t i = 1; str[i] != '\0'; ++i) {
    if (str[i - 1] == str[i]) {
      return 1;
    }
  }
  return 0;
}
