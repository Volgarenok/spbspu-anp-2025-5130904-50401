#include <iostream>
#include <cstddef>
#include <cctype>
#include <iomanip>

namespace lukashevich {
  char* createStr(const size_t size)
  {
    return new char[size];
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

    while (in >> sym && sym != '\n') {
      if (i == size - 1) {
        str = updateStr(str, size);
        size *= 2;
      }
      str[i++] = sym;
    }

    if (in.eof() && i == 0) {
      delete[] str;
      if (isSkipws) {
        in >> std::skipws;
      }
      throw std::runtime_error("empty input");
    }

    char* result = createStr(size + 1);
    for (size_t j = 0; j < i; ++j) {
      result[j] = str[j];
    }
    result[i] = '\0';

    delete [] str;

    if (isSkipws) {
      in >> std::skipws;
    }

    return result;
  }

  int mergeLatinLetters(const char* str1, const char* str2, char* result, const int resultSize)
  {
    if (str1 == nullptr || str2 == nullptr || result == nullptr || resultSize <= 0) {
      throw std::invalid_argument("Argument are nullptr in func merge");
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
          throw std::runtime_error("small buffer for func merge");
        }
        result[pos++] = static_cast< char >('a' + i);
      }
    }
    result[pos] = '\0';
    return pos;
  }

  int removeLatinLetters(const char* str, char* result, const int resultSize)
  {
    if (str == nullptr || result == nullptr || resultSize <= 0) {
      throw std::invalid_argument("argument are nullptr in func remove");
    }

    int pos = 0;
    for (size_t i = 0; str[i] != '\0'; ++i) {
      const unsigned char c = str[i];
      if (!std::isalpha(c)) {
        if (pos + 1 >= resultSize) {
          throw std::runtime_error("small buffer for func merge");
        }
        result[pos++] = str[i];
      }
    }
    result[pos] = '\0';
    return pos;
  }

  char* latinLettersInStock(const char* str1, const char* str2)
  {
    if (str1 == nullptr || str2 == nullptr) {
      throw std::invalid_argument("argument are nullptr in func latin");
    }

    const int maxSize = 27;
    char* result = createStr(maxSize);

    mergeLatinLetters(str1, str2, result, maxSize);
    return result;
  }

  char* latinRemove(const char* str)
  {
    if (str == nullptr) {
      throw std::invalid_argument("Null pointer in latinRemove");
    }

    const size_t size = strLen(str);
    char* result = createStr(size + 1);

    removeLatinLetters(str, result, static_cast< int >(size + 1));
    return result;
  }
}

int main()
{
  namespace luk = lukashevich;

  char* str = nullptr;
  char* resLatTwo = nullptr;
  char* resLatRmv = nullptr;

  try {
  char* str = luk::getLine(std::cin);
  const char* secondWord = "def_ghk";

  resLatTwo = luk::latinLettersInStock(str, secondWord);
  resLatRmv = luk::latinRemove(str);

  std::cout << resLatTwo << "\n";
  std::cout << resLatRmv << "\n";
  } catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << "\n";

    delete[] str;
    delete[] resLatTwo;
    delete[] resLatRmv;

    return 1;
  }

  delete[] str;
  delete[] resLatTwo;
  delete[] resLatRmv;
}
