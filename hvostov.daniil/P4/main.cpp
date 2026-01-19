#include <iostream>
#include <iomanip>
#include <cctype>
#include <cmath>

namespace hvostov {
  char * getLine(std::istream & in, size_t & size);
  void resizeStr(char ** str, size_t & size, size_t new_size);
  void extendStr(char ** str, size_t & size);
  size_t getNewSize(size_t size);
  void strConcatCharByChar(char * buffer, const char * str1, const char * str2);
  size_t countAlphaCharacters(const char * str);
}

int main()
{
  size_t size = 10;
  char * str = hvostov::getLine(std::cin, size);
  if (str == nullptr) {
    std::cerr << "Cant get string\n";
    return 1;
  }
  char str2[] = "qwerty12345";
  size_t size2 = 11;
  char * result = nullptr;
  try {
    result = new char[size + size2 + 1]();
  } catch (const std::bad_alloc & e) {
    std::cerr << e.what() << "\n";
    delete[] str;
    return 1;
  }
  hvostov::strConcatCharByChar(result, str, str2);
  size_t counter = hvostov::countAlphaCharacters(result);
  std::cout << result << "\n";
  std::cout << counter << "\n";
  delete[] str;
  delete[] result;
  return 0;
}

char * hvostov::getLine(std::istream & in, size_t & size)
{
  char * str = nullptr;
  try {
    str = new char[size + 1]();
  } catch (const std::bad_alloc &) {
    return nullptr;
  }
  bool is_skipws = in.flags() & std::ios_base::skipws;
  if (is_skipws) {
    in >> std::noskipws;
  }
  size_t i = 0;
  char a = 'a';
  while (in >> a && a != '\n') {
    if (i == size) {
      try {
        hvostov::extendStr(&str, size);
      } catch (const std::bad_alloc &) {
        delete[] str;
        return nullptr;
      }
    }
    str[i] = a;
    i++;
  }
  str[i] = '\0';
  size = i;
  try {
    hvostov::resizeStr(&str, size, size + 1);
  } catch (const std::bad_alloc &) {
    delete[] str;
    return nullptr;
  }
  if (is_skipws) {
    in >> std::skipws;
  }
  if (!in) {
    delete[] str;
    return nullptr;
  }
  return str;
}

void hvostov::resizeStr(char ** str, size_t & size, size_t new_size)
{
  char * new_str = new char[new_size]();
  for (size_t i = 0; i < std::min(size, new_size); i++) {
    new_str[i] = (*str)[i];
  }
  delete[] * str;
  size = new_size;
  *str = new_str;
}

size_t hvostov::getNewSize(size_t size)
{
  double new_size = size * std::sqrt(2);
  return std::ceil(new_size);
}

void hvostov::extendStr(char ** str, size_t & size)
{
  size_t new_size = hvostov::getNewSize(size);
  char * new_str = new char[new_size];
  for (size_t i = 0; i < size; i++) {
    new_str[i] = (*str)[i];
  }
  delete[] * str;
  size = new_size;
  *str = new_str;
}

void hvostov::strConcatCharByChar(char * buffer, const char * str1, const char * str2)
{
  size_t i = 0;
  size_t pos1 = 0;
  size_t pos2 = 0;
  while (str1[pos1] != '\0' && str2[pos2] != '\0') {
    if (i % 2 == 0) {
      buffer[i] = str1[pos1];
      pos1++;
    } else {
      buffer[i] = str2[pos2];
      pos2++;
    }
    i++;
  }
  if (str1[pos1] != '\0') {
    for (; str1[pos1] != '\0'; pos1++, i++) {
      buffer[i] = str1[pos1];
    }
  } else {
    for (; str2[pos2] != '\0'; pos2++, i++) {
      buffer[i] = str2[pos2];
    }
  }
  buffer[i] = '\0';
}

size_t hvostov::countAlphaCharacters(const char * str)
{
  size_t counter = 0;
  for (size_t i = 0; str[i] != '\0'; i++) {
    if (isalpha(str[i])) {
      counter++;
    }
  }
  return counter;
}
