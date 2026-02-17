#include <iomanip>
#include <iostream>
#include "input.hpp"
#include "resize.hpp"

namespace chernov {
  int hasSam(const char * str1, const char * str2, size_t size1, size_t size2);
  void latRmv(char * new_str, const char * old_str, size_t old_size);
  bool isSpaceSym(char ch);
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
