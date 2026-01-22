#include <iostream>
#include <cstddef>
#include <iomanip>
#include <cctype>

namespace malashenko {
  char * createStr(size_t size)
  {
    char * str = nullptr;
    try {
      str = new char[size];
    } catch (const std::bad_alloc & e) {
      std::cerr << "bad alloc\n";
      return nullptr;
    }
    return str;
  }

  size_t strLen(const char * str) {
    size_t l = 0;
    while (str[l] != '\0') {
      l++;
    }
    return l;
  }

  char * updateStr(char * oldStr, size_t oldSize)
  {
    char * newStr = createStr(oldSize * 2);
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

  char * getLine(std::istream & in)
  {
    bool is_skipws = in.flags() & std::ios_base::skipws;
    if (is_skipws) {
      in >> std::noskipws;
    }

    size_t i = 0;
    size_t size = 8;
    char sym = 0;
    char * str = createStr(size);
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
    if (is_skipws) {
      in >> std::skipws;
    }
    return str;
  }

  size_t repDgt(char * str, size_t size)
  {
    int nums[10] = {};
    size_t numSize = 0;

    for (size_t i = 0; i < size; ++i) {
      if (isdigit(str[i])) {
        size_t j = 0;
        for (; j < numSize; ++j) {
          if (nums[j] == str[i]) {
            return 1;
          }
        }
        nums[j] = str[i];
        numSize++;
      }
    }
    return 0;
  }

  char * rmvVol(char * str, size_t size)
  {
    char vols[] = "aeiouAEIOU";
    char * newStr = createStr(size);
    size_t strLen = 0;
    for (size_t i = 0; i < size; ++i) {
      bool isVol = 0;
      if (std::isalpha(str[i])) {
        for (size_t j = 0; j < 10; ++j) {
          isVol = isVol || (str[i] == vols[j]);
        }
      }
      if (isVol == 0) {
        newStr[strLen] = str[i];
        strLen++;
      }
    }
    newStr[strLen] = '\0';
    return newStr;
  }
}

int main()
{
  namespace mal = malashenko;
  char * str = mal::getLine(std::cin);
  if (!str || std::cin.fail()) {
    std::cerr << "problem with input\n";
    delete[] str;
    return 1;
  }
  size_t size = mal::strLen(str);
  if (!size) {
    std::cerr << "The input must not be empty\n";
    delete[] str;
    return 1;
  }
  size_t isRepDgt = mal::repDgt(str, size);
  char * noVolStr = mal::rmvVol(str, size);

  std::cout << isRepDgt << "\n";
  std::cout << noVolStr << "\n";

  delete[] str;
  delete[] noVolStr;
  return 0;
}
