#include <iostream>
#include <iomanip>
#include <cctype>
#include <cstring>

namespace zharov
{
  bool isSpace(char c);
  char ** splitLine(char * str, size_t & len, bool(*sep)(char));
  void extendArr(char *** str, size_t old_size, size_t new_size);
  char * getLine(std::istream & in, size_t & len);
  void extendStr(char ** str, size_t old_size, size_t new_size);
  char * getLatRmv(const char * str, char * res);
  char * getShtSym(const char * str, char * res);
  void destroyArr(char ** arr, size_t len);
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

void zharov::destroyArr(char ** arr, size_t len)
{
  for (size_t i = 0; i < len; ++i) {
    delete[] arr[i];
  }
  delete[] arr;
}

void zharov::extendStr(char ** str, size_t old_size, size_t new_size)
{
  char * new_str = new char[new_size];
  for (size_t i = 0; i < old_size; ++i) {
    new_str[i] = (*str)[i];
  }
  delete[] *str;
  *str = new_str;
}

void zharov::extendArr(char *** arr_str, size_t old_size, size_t new_size)
{
  char ** new_arr = new char * [new_size];
  for (size_t i = 0; i < old_size; ++i) {
    new_arr[i] = (*arr_str)[i];
  }
  delete[] *arr_str;
  *arr_str = new_arr;
}

bool zharov::isSpace(char c)
{
  return std::isspace(c);
}

char ** zharov::splitLine(char * str, size_t & len, bool(*sep)(char))
{
  size_t size = 10;
  size_t step = 2;
  char ** arr_str = new char * [size];
  bool is_last_sep = true;
  size_t i = 0;
  size_t start_i = 0;
  for (; str[i] != '\0'; ++i) {
    if (len == size) {
      try {
        zharov::extendArr(&arr_str, size, size * step);
      } catch (const std::bad_alloc &) {
        zharov::destroyArr(arr_str, len);
        throw;
      }
      size *= step;
    }
    if (sep(str[i])) {
      if (!is_last_sep) {
        char * new_str = nullptr;
        try {
          new_str = new char[i - start_i + 1];
        } catch (const std::bad_alloc &) {
          zharov::destroyArr(arr_str, len);
          throw;
        }
        for (size_t j = 0; j < i - start_i; ++j) {
          new_str[j] = str[start_i + j];
        }
        new_str[i - start_i] = '\0';
        arr_str[len] = new_str;
        ++len;
        is_last_sep = true;
      }
      start_i = i + 1;
    } else {
      is_last_sep = false;
    }
  }
  if (!is_last_sep || i == 0) {
    char * new_str = nullptr;
    try {
      new_str = new char[i - start_i + 1];
    } catch (const std::bad_alloc &) {
      zharov::destroyArr(arr_str, len);
      throw;
    }
    for (size_t j = 0; j < i - start_i; ++j) {
      new_str[j] = str[start_i + j];
    }
    new_str[i - start_i] = '\0';
    arr_str[len] = new_str;
    ++len;
  }
  return arr_str;
}

char * zharov::getLine(std::istream & in, size_t & len)
{
  size_t size = 10;
  size_t step = 2;
  char end = '\n';
  bool is_skipws = in.flags() & std::ios_base::skipws;
  if (is_skipws) {
    in >> std::noskipws;
  }

  char * str = new char[size + 1];
  char sym = ' ';
  while (in >> sym && sym != end) {
    if (size == len) {
      try {
        zharov::extendStr(&str, size, size * step);
      } catch (const std::bad_alloc &) {
        delete[] str;
        throw;
      }
      size *= step;
    }
    str[len] = sym;
    ++len;
  }
  str[len] = '\0';

  if (is_skipws) {
    in >> std::skipws;
  }
  return str;
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
