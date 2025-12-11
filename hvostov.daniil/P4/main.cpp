#include <iostream>
#include <iomanip>
#include <cctype>
#include <cmath>

namespace hvostov {
  char ** getStr(std::istream & in, size_t & size, int (*divisor)(int));
  void resizeStr(char *** str, size_t & size, size_t new_size);
  void extendStr(char ** str, size_t & size);
  size_t getNewSize(size_t size);
  void strConcatCharByChar(char * buffer, char ** str1, char * str2, size_t size);
  size_t countAlphaCharacters(char ** str, size_t size);
  void deleteStr(char ** str, size_t size);
  char * copyStr(char * str);
  char * copyStr(char * str, size_t len);
  void extendStr(char *** str, size_t & size);
  void appendStr(char ** str, size_t & size, char * word, size_t len);
  size_t getStrLength(char ** str, size_t size);
}

int main()
{
  size_t size = 10;
  char ** str = hvostov::getStr(std::cin, size, isspace);
  if (str == nullptr) {
    std::cerr << "Cant get string\n";
    return 1;
  }
  char str2[] = "qwerty12345";
  size_t size2 = 11;
  char * result = nullptr;
  try {
    result = new char[hvostov::getStrLength(str, size) + size2 + 1]();
  } catch (const std::bad_alloc & e) {
    std::cerr << e.what() << "\n";
    hvostov::deleteStr(str, size);
    return 1;
  }
  hvostov::strConcatCharByChar(result, str, str2, size);
  size_t counter = hvostov::countAlphaCharacters(str, size);
  std::cout << result << "\n";
  std::cout << counter << "\n";
  delete[] result;
  hvostov::deleteStr(str, size);
  return 0;
}

size_t hvostov::getStrLength(char ** str, size_t size)
{
  size_t length = 0;
  for (size_t i = 0; i < size; i++) {
    for (size_t j = 0; str[i][j] != '\0'; j++) {
      length++;
    }
  }
  return length;
}

char * hvostov::copyStr(char * str, size_t len)
{
  char * copy = new char[len + 1];
  size_t i = 0;
  for (; i < len; i++) {
    copy[i] = str[i];
  }
  copy[i] = '\0';
  return copy;
}

char * hvostov::copyStr(char * str)
{
  size_t len = 0;
  for (; str[len] != '\0'; len++) {
    continue;
  }
  char * copy = new char[len + 1];
  size_t i = 0;
  for (; str[i] != '\0'; i++) {
    copy[i] = str[i];
  }
  copy[i] = '\0';
  return copy;
}

void hvostov::deleteStr(char ** str, size_t size)
{
  for (size_t i = 0; i < size; i++) {
    delete[] str[i];
  }
  delete[] str;
}

size_t hvostov::getNewSize(size_t size)
{
  double new_size = size * std::sqrt(2);
  return std::ceil(new_size);
}

void hvostov::extendStr(char *** str, size_t & size)
{
  size_t new_size = hvostov::getNewSize(size);
  char ** new_str = new char*[new_size];
  for (size_t i = 0; i < size; i++) {
    char * copy = nullptr;
    try {
      copy = copyStr((*str)[i]);
    } catch (const std::bad_alloc & e) {
      hvostov::deleteStr(new_str, i);
      throw;
    }
    new_str[i] = copy;
  }
  hvostov::deleteStr(*str, size);
  size = new_size;
  *str = new_str;
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

void hvostov::appendStr(char ** str, size_t & size, char * word, size_t len)
{
  char * word_copy = hvostov::copyStr(word, len);
  str[size] = word_copy;
  size++;
}

char ** hvostov::getStr(std::istream & in, size_t & size, int (*divider)(int))
{
  const size_t start_word_len = 10;
  size_t word_len = start_word_len;
  char ** str = nullptr;
  char * word = nullptr;
  try {
    str = new char*[size];
    word = new char[word_len]();
  } catch (const std::bad_alloc &) {
    delete[] str;
    return nullptr;
  }
  bool is_skipws = in.flags() & std::ios_base::skipws;
  if (is_skipws) {
    in >> std::noskipws;
  }
  char a = 'a';
  size_t str_index = 0, word_index = 0;
  bool is_previous_was_space = false;
  while (in >> a && a != '\n') {
    if (divider(a) && is_previous_was_space) {
      continue;
    } else {
      is_previous_was_space = false;
    }
    if (divider(a)) {
      try {
        hvostov::appendStr(str, str_index, word, word_index);
      } catch (const std::bad_alloc & e) {
        hvostov::deleteStr(str, str_index);
        return nullptr;
      }
      word_len = start_word_len;
      word_index = 0;
      try {
        word = new char[word_len]();
      } catch (const std::bad_alloc &) {
        hvostov::deleteStr(str, str_index);
        return nullptr;
      }
      is_previous_was_space = true;
    } else {
      word[word_index] = a;
      word_index++;
    }
    if (str_index == size) {
      try {
        hvostov::extendStr(&str, size);
      } catch (const std::bad_alloc &) {
        hvostov::deleteStr(str, str_index);
        return nullptr;
      }
    }
    if (word_index == word_len) {
      try {
        hvostov::extendStr(&word, word_len);
      } catch (const std::bad_alloc &) {
        hvostov::deleteStr(str, str_index);
        return nullptr;
      }
    }
  }
  if (word[0] != '\0') {
    hvostov::appendStr(str, str_index, word, word_index);
  }
  size = str_index;
  try {
    hvostov::resizeStr(&str, str_index, str_index + 1);
  } catch (const std::bad_alloc &) {
    hvostov::deleteStr(str, str_index);
    return nullptr;
  }
  if (is_skipws) {
    in >> std::skipws;
  }
  if (!in) {
    hvostov::deleteStr(str, str_index);
    return nullptr;
  }
  delete[] word;
  return str;
}

void hvostov::resizeStr(char *** str, size_t & size, size_t new_size)
{
  char ** new_str = new char*[new_size];
  for (size_t i = 0; i < std::min(size, new_size); i++) {
    char * copy = nullptr;
    try {
      copy = hvostov::copyStr((*str)[i]);
    } catch (const std::bad_alloc &) {
      hvostov::deleteStr(new_str, i);
      throw;
    }
    new_str[i] = copy;
  }
  hvostov::deleteStr(*str, size);
  size = new_size;
  *str = new_str;
}

void hvostov::strConcatCharByChar(char * buffer, char ** str1, char * str2, size_t size)
{
  size_t index = 0, pos = 0;
  size_t i = 0, j = 0;
  for (; i < size; i ++) {
    j = 0;
    while (str1[i][j] != '\0' && str2[pos] != '\0') {
      if (index % 2 == 0) {
        buffer[index++] = str1[i][j++];
      } else {
        buffer[index++] = str2[pos++];
      }
    }
    if (str2[pos] == '\0') {
      break;
    }
  }
  if (str2[pos] == '\0') {
    for (; i < size; i++) {
      for (; str1[i][j] != '\0'; j++) {
        buffer[index++] = str1[i][j];
      }
      j = 0;
    }
  } else {
    for (; str2[pos] != '\0'; pos++) {
      buffer[index++] = str2[pos];
    }
  }
  buffer[index] = '\0';
}

size_t hvostov::countAlphaCharacters(char ** str, size_t size)
{
  size_t counter = 0;
  for (size_t i = 0; i < size; i++) {
    for (size_t j = 0; str[i][j] != '\0'; j++) {
      if (isalpha(str[i][j])) {
        counter++;
      }
    }
  }
  return counter;
}
