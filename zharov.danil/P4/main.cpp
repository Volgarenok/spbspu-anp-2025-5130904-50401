#include <iostream>
#include <cctype>
#include <cstring>
#include "resize.hpp"
#include "input_string.hpp"

namespace zharov
{
  bool isSpace(char c);
  char * getLatRmv(const char * str, char * res);
  char * getShtSym(const char * str, char * res);
}

int main()
{
  size_t len = 0;
  char * str = nullptr;
  try {
    str = zharov::getLine(std::cin, len);
    if (std::cin.fail()) {
      std::cerr << "Bad enter\n";
      delete[] str;
      return 1;
    }
  } catch (const std::bad_alloc &) {
    std::cerr << "Bad alloc\n";
    return 1;
  }

  char ** arr_str = nullptr;
  size_t len_arr = 0;
  try {
    arr_str = zharov::splitLine(str, len_arr, zharov::isSpace);
  } catch (const std::bad_alloc &) {
    delete[] str;
    std::cerr << "Bad alloc\n";
    return 1;
  }

  for (size_t i = 0; i < len_arr; ++i) {
    char * line = arr_str[i];
    size_t c = 0;
    while (line[c] != '\0') {
      ++c;
    }
    char * res_1 = nullptr;
    try {
      res_1 = new char[c + 1];
    } catch (const std::bad_alloc &) {
      delete[] str;
      zharov::destroyArr(arr_str, len_arr);
      std::cerr << "Bad alloc\n";
      return 1;
    }
    res_1 = zharov::getLatRmv(line, res_1);
    std::cout << "LAT-RMV №" << i + 1 << ": " << res_1 << "\n";
    delete[] res_1;
  }
  for (size_t i = 0; i < len_arr; ++i) {
    char * line = arr_str[i];
    char * res_2 = nullptr;
    try {
      res_2 = new char[27];
    } catch(const std::bad_alloc &) {
      delete[] str;
      zharov::destroyArr(arr_str, len_arr);
      std::cerr << "Bad alloc\n";
      return 1;
    }
    res_2 = zharov::getShtSym(line, res_2);
    std::cout << "SHT_SYM №" << i + 1 << ": " << res_2 << "\n";
    delete[] res_2;
  }

  zharov::destroyArr(arr_str, len_arr);
  delete[] str;
}

bool zharov::isSpace(char c)
{
  return std::isspace(c);
}

char * zharov::getLatRmv(const char * str, char * res)
{
  size_t c = 0;
  for (size_t i = 0; str[i] != '\0'; ++i) {
    if (!isalpha(str[i])) {
      res[c] = str[i];
      ++c;
    }
  }
  res[c] = '\0';
  return res;
}

char * zharov::getShtSym(const char * str, char * res)
{
  bool found = false;
  size_t c = 0;
  for (char letter = 'a'; letter <= 'z'; letter++){
    for (size_t i = 0; str[i] != '\0'; ++i) {
      if (letter == tolower((str[i]))) {
        found = true;
        break;
      }
    }
    if (!found) {
      res[c] = letter;
      ++c;
    }
    found = false;
  }
  res[c] = '\0';
  return res;
}
