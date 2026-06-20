#include <iostream>
#include <cstddef>
#include <cctype>
#include <iomanip>

namespace lukashevich {
  char* createStr(const size_t size)
  {
    char* str = nullptr;
    try {
      str = new char[size];
    } catch (const std::bad_alloc& e) {
      std::cerr << "bad alloc\n";
      return nullptr;
    }
    return str;
  }

  size_t strLen(const char* str)
  {
    size_t l = 0;
    while (str[l] != '\0') {
      l++;
    }
    return l;
  }

  char* updateStr(char* oldStr, const size_t oldSize)
  {
    char* newStr = createStr(oldSize * 2);
    if (!newStr) {
      delete[] oldStr;
      return nullptr;
    }
    for (size_t i = 0; i < oldSize; ++i) {
      newStr[i] = oldStr[i];
    }
    delete[] oldStr;
    return newStr;
  }

  char* getLine(std::istream& in)
  {
    const bool isSkipws = in.flags() & std::ios_base::skipws;
    if (isSkipws) {
      in >> std::noskipws;
    }

    size_t i = 0;
    size_t size = 8;
    char sym = 0;
    char* str = createStr(size);
    if (!str) {
      return nullptr;
    }

    while (in >> sym && sym != '\n') {
      if (i == size - 1) {
        str = updateStr(str, size);
        if (!str) {
          return nullptr;
        }
        size *= 2;
      }
      str[i++] = sym;
    }
    str[i++] = '\0';

    if (isSkipws) {
      in >> std::skipws;
    }

    return str;
  }

  int mergeLatinLetters(const char* str1, const char* str2, char* result, const int resultSize)
  {
    if (str1 == nullptr || str2 == nullptr || result == nullptr || resultSize <= 0) {
      return -1;
    }

    int letters[26] = {0};

    for (size_t i = 0; str1[i] != '\0'; ++i) {
      const unsigned char c = str1[i];
      if (std::isalpha(c)) {
        const int index = std::tolower(c) - 'a';
        if (index >= 0 && index < 26) {
          letters[index] = 1;
        }
      }
    }

    for (size_t i = 0; str2[i] != '\0'; ++i) {
      const unsigned char c = str2[i];
      if (std::isalpha(c)) {
        const int index = std::tolower(c) - 'a';
        if (index >= 0 && index < 26) {
          letters[index] = 1;
        }
      }
    }

    int pos = 0;
    for (int i = 0; i < 26; ++i) {
      if (letters[i] == 1) {
        if (pos + 1 >= resultSize) {
          return -1;
        }
        result[pos++] = static_cast<char>('a' + i);
      }
    }

    result[pos] = '\0';
    return pos;
  }

  int removeLatinLetters(const char* str, char* result, const int resultSize)
  {
    if (str == nullptr || result == nullptr || resultSize <= 0) {
      return -1;
    }

    int pos = 0;
    for (size_t i = 0; str[i] != '\0'; ++i) {
      const unsigned char c = str[i];
      if (!std::isalpha(c)) {
        if (pos + 1 >= resultSize) {
          return -1;
        }
        result[pos++] = str[i];
      }
    }

    result[pos] = '\0';
    return pos;
  }

  char* latinLettersInStock(const char* str1, const char* str2)
  {
    const int maxSize = 27;
    char* result = createStr(maxSize);
    if (!result) {
      return nullptr;
    }

    const int len = mergeLatinLetters(str1, str2, result, maxSize);
    if (len < 0) {
      delete[] result;
      return nullptr;
    }

    return result;
  }

  char* latinRemove(const char* str)
  {
    if (!str) {
      return nullptr;
    }

    const size_t size = strLen(str);
    char* result = createStr(size + 1);
    if (!result) {
      return nullptr;
    }

    const int len = removeLatinLetters(str, result, static_cast<int>(size + 1));
    if (len < 0) {
      delete[] result;
      return nullptr;
    }

    return result;
  }
}

int main()
{
  namespace luk = lukashevich;
  char* str = luk::getLine(std::cin);
  if (!str) {
    std::cerr << "problem with input\n";
    return 1;
  }

  const char* secondWord = "def_ghk";
  char* resLatTwo = luk::latinLettersInStock(str, secondWord);
  char* resLatRmv = luk::latinRemove(str);

  std::cout << resLatTwo << "\n";
  std::cout << resLatRmv << "\n";

  delete[] str;
  delete[] resLatTwo;
  delete[] resLatRmv;

  return 0;
}
