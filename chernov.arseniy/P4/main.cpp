#include <iostream>
#include <iomanip>
#include <memory>
#include <cctype>

namespace chernov {
  void destroy(char ** strs, size_t k);
  const char * copy(const char * src, char * dest, size_t k);
  void resize(char ** str, size_t old_size, size_t new_size);
  void resize(size_t ** sizes, size_t old_size, size_t new_size);
  void resize(char *** strs, size_t old_size, size_t new_size);
  char * getline(std::istream & input, size_t & size, bool (*check_sym)(char), size_t start_size, double k_resize);
  char ** getlines(std::istream & input, size_t & size, size_t ** sizes, bool (*check_sym)(char), size_t start_size, double k_resize);
  int hasSam(const char * str1, const char * str2, size_t size1, size_t size2);
  void latRmv(char * new_str, const char * old_str, size_t old_size);
  bool isSpaceSym(char ch);
}

void chernov::destroy(char ** strs, size_t k)
{
  for (size_t i = 0; i < k; ++i) {
    free(strs[i]);
  }
  free(strs);
}

const char * chernov::copy(const char * src, char * dest, size_t k)
{
  for (size_t i = 0; i < k; ++i) {
    dest[i] = src[i];
  }
  return dest + k;
}

void chernov::resize(char ** str, size_t old_size, size_t new_size)
{
  char * new_str = reinterpret_cast< char * >(malloc(sizeof(char) * new_size));
  if (new_str == nullptr) {
    *str = nullptr;
    return;
  }
  size_t size = std::min(old_size, new_size);
  copy(*str, new_str, size);
  free(*str);
  *str = new_str;
}

void chernov::resize(size_t ** sizes, size_t old_size, size_t new_size)
{
  size_t * new_sizes = reinterpret_cast< size_t * >(malloc(sizeof(size_t) * new_size));
  if (new_sizes == nullptr) {
    *sizes = nullptr;
    return;
  }
  size_t size = std::min(old_size, new_size);
  for (size_t i = 0; i < size; ++i) {
    new_sizes[i] = (*sizes)[i];
  }
  free(*sizes);
  *sizes = new_sizes;
}

void chernov::resize(char *** strs, size_t old_size, size_t new_size)
{
  char ** new_strs = reinterpret_cast< char ** >(malloc(sizeof(char *) * new_size));
  if (new_strs == nullptr) {
    *strs = nullptr;
    return;
  }
  size_t size = std::min(old_size, new_size);
  for (size_t i = 0; i < size; ++i) {
    new_strs[i] = (*strs)[i];
  }
  free(*strs);
  *strs = new_strs;
}

char * chernov::getline(std::istream & input, size_t & size, bool (*check_sym)(char), \
  size_t start_size, double k_resize)
{
  bool is_skipws = input.flags() & std::ios_base::skipws;
  if (is_skipws) {
    input >> std::noskipws;
  }
  size_t str_size = start_size, i = 0;
  char * str = nullptr;
  chernov::resize(&str, 0, str_size);
  while (input) {
    if (i >= str_size - 1) {
      size_t new_str_size = str_size * k_resize;
      chernov::resize(&str, str_size, new_str_size);
      if (str == nullptr) {
        free(str);
        return nullptr;
      }
      str_size = new_str_size;
    }
    char ch = '\0';
    input >> ch;
    if (check_sym(ch) || ch == '\0') {
      break;
    }
    str[i] = ch;
    ++i;
  }
  str[i] = '\0';
  size = i;
  if (is_skipws) {
    input >> std::skipws;
  }
  return str;
}

char ** chernov::getlines(std::istream & input, size_t & size, size_t ** sizes, bool (*check_sym)(char), \
  size_t start_size, double k_resize)
{
  size_t strs_size = 0, i = 0;
  size_t * strs_sizes = nullptr;
  char ** strs = nullptr;
  while (input) {
    char * str = nullptr;
    size_t tmp_size = 0;
    str = chernov::getline(input, tmp_size, check_sym, start_size, k_resize);
    if (str == nullptr) {
      destroy(strs, i);
      return nullptr;
    }
    if (!tmp_size) {
      free(str);
      continue;
    }
    chernov::resize(&strs_sizes, strs_size, strs_size + 1);
    chernov::resize(&strs, strs_size, strs_size + 1);
    if (strs_sizes == nullptr || strs == nullptr) {
      free(str);
      free(strs_sizes);
      destroy(strs, i);
      return nullptr;
    }
    ++strs_size;
    strs_sizes[i] = tmp_size;
    strs[i] = str;
    ++i;
  }
  size = strs_size;
  *sizes = strs_sizes;
  return strs;
}

int chernov::hasSam(const char * str1, const char * str2, size_t size1, size_t size2)
{
  for (size_t i = 0; i < size1; ++i) {
    for (size_t j = 0; j < size2; ++j) {
      if (str1[i] == str2[j]) {
        return 1;
      }
    }
  }
  return 0;
}

void chernov::latRmv(char * new_str, const char * old_str, size_t old_size)
{
  size_t i = 0;
  for (size_t j = 0; j < old_size; ++j) {
    if (!std::isalpha(old_str[j])) {
      new_str[i] = old_str[j];
      ++i;
    }
  }
  new_str[i] = 0;
}

bool chernov::isSpaceSym(char ch)
{
  return isspace(ch);
}

int main()
{
  std::istream & input = std::cin;
  size_t size = 0, start_size = 10;
  double k_resize = 1.4;
  size_t * sizes = nullptr;
  char ** strs = nullptr;
  strs = chernov::getlines(input, size, &sizes, chernov::isSpaceSym, start_size, k_resize);
  if (strs == nullptr) {
    std::cerr << "badAllocError\n";
    return 1;
  }
  if (!input && !input.eof()) {
    chernov::destroy(strs, size);
    free(sizes);
    std::cerr << "badError\n";
    return 2;
  }
  if (size == 0) {
    std::cerr << "inputError\n";
    return 3;
  }

  size_t second_size = 3;
  char second_str[] = "abs";
  for (size_t i = 0; i < size; ++i) {
    int result_has_sam = chernov::hasSam(strs[i], second_str, sizes[i], second_size);
    std::cout << "HAS-SAM: " << result_has_sam << "\n";
  }

  for (size_t i = 0; i < size; ++i) {
    char * result_lat_rmv = reinterpret_cast< char * >(malloc(sizeof(char) * sizes[i]));
    chernov::latRmv(result_lat_rmv, strs[i], sizes[i]);
    std::cout << "LAT-RMV: " << result_lat_rmv << "\n";
    free(result_lat_rmv);
  }

  chernov::destroy(strs, size);
  free(sizes);
}
