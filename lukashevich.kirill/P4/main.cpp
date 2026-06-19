#include <iostream>
#include <cstddef>
#include <cctype>
#include <iomanip>
#include <cstring>
#include <exception>
#include <new>

namespace lukashevich {
  char* createStr(const size_t size)
  {
    return new char[size];
  }

  void copyChars(const char* source, char* destination, const size_t count) noexcept
  {
    for (size_t i = 0; i < count; ++i) {
      destination[i] = source[i];
    }
  }

  int getLatinIndex(const unsigned char c) noexcept
  {
    if (std::isalpha(c) == 0) {
      return -1;
    }

    const int lower = std::tolower(c);
    if (lower < 'a' || lower > 'z') {
      return -1;
    }

    return lower - 'a';
  }

  void fillLatinTable(const char* str, int* letters) noexcept
  {
    if (str == nullptr || letters == nullptr) {
      return;
    }

    for (size_t i = 0; str[i] != '\0'; ++i) {
      const int index = getLatinIndex(static_cast< unsigned char >(str[i]));
      if (index >= 0) {
        letters[index] = 1;
      }
    }
  }

  char* getLine(std::istream& in)
  {
    const std::ios_base::fmtflags flags = in.flags();
    in >> std::noskipws;

    size_t pos = 0;
    size_t size = 8;
    char* str = createStr(size);

    try {
      char sym = 0;
      while (in >> sym && sym != '\n') {
        if (pos + 1 == size) {
          if (size > static_cast< size_t >(-1) / 2) {
            throw std::bad_alloc();
          }

          const size_t newSize = size * 2;
          char* newStr = createStr(newSize);
          copyChars(str, newStr, pos);
          delete[] str;
          str = newStr;
          size = newSize;
        }

        str[pos] = sym;
        ++pos;
      }

      str[pos] = '\0';
      in.flags(flags);
      return str;
    } catch (...) {
      delete[] str;
      in.flags(flags);
      throw;
    }
  }

  size_t mergeLatinLetters(const char* str1, const char* str2, char* result, const size_t resultSize) noexcept
  {
    if (result == nullptr || resultSize == 0) {
      return 0;
    }

    int letters[26] = {0};
    fillLatinTable(str1, letters);
    fillLatinTable(str2, letters);

    size_t pos = 0;
    for (size_t i = 0; i < 26; ++i) {
      if (letters[i] != 0 && pos + 1 < resultSize) {
        result[pos] = static_cast< char >('a' + i);
        ++pos;
      }
    }

    result[pos] = '\0';
    return pos;
  }

  size_t removeLatinLetters(const char* str, char* result, const size_t resultSize) noexcept
  {
    if (str == nullptr || result == nullptr || resultSize == 0) {
      throw std::invalid_argument("argument are nullptr in func remove");
    }

    size_t pos = 0;
    for (size_t i = 0; str[i] != '\0'; ++i) {
      const int index = getLatinIndex(static_cast< unsigned char >(str[i]));
      if (index == -1 && pos + 1 < resultSize) {
        result[pos] = str[i];
        ++pos;
      }
    }

    result[pos] = '\0';
    return pos;
  }

  void freeMemory(char* str, char* result1, char* result2) noexcept
  {
    delete[] str;
    delete[] result1;
    delete[] result2;
  }
}

int main()
{
  namespace luk = lukashevich;

  char* str = nullptr;
  char* resLatTwo = nullptr;
  char* resLatRmv = nullptr;

  try {
    str = luk::getLine(std::cin);

    const char* secondWord = "def_ghk";
    const size_t latTwoSize = 27;
    const size_t latRmvSize = std::strlen(str) + 1;

    resLatTwo = luk::createStr(latTwoSize);
    resLatRmv = luk::createStr(latRmvSize);

    luk::mergeLatinLetters(str, secondWord, resLatTwo, latTwoSize);
    luk::removeLatinLetters(str, resLatRmv, latRmvSize);

    std::cout << resLatTwo << "\n";
    std::cout << resLatRmv << "\n";
  } catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << "\n";

    luk::freeMemory(str, resLatTwo, resLatRmv);
    return 1;
  }

  luk::freeMemory(str, resLatTwo, resLatRmv);
  return 0;
}
