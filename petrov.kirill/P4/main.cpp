#include <iostream>
#include <cctype>
#include <iomanip>

namespace petrov {
  void getline(std::istream& in, const size_t size, char* str, size_t& k);
};

void petrov::getline(std::istream& in, const size_t size, char* str, size_t& k) {
  std::cin >> std::noskipws;
  while (in.peek() != '\n' && k <= size) {
    if (in.bad() || in.fail() || in.eof()) {
      throw std::logic_error("err");
    }
    in >> str[k++];
  }
}

int main() {
  const size_t size = 10000;
  char* str = new char[size];
  size_t k = 0;
  try {
    petrov::getline(std::cin, size, str, k);
  } catch (...) {
    std::cerr << "err\n";
    delete[] str;
    return 1;
  }
  if (k == 0) {
    delete[] str;
    std::cerr << "err\n";
    return 1;
  }
  char* new_str = new char[k];
  for (size_t i = 0; i < k; ++i) {
    new_str[i] = str[i];
  }
  delete[] str;
  for (size_t i = 0; i < k; ++i) {
    std::cout << new_str[i];
  }
  delete[] new_str;
  return 0;
}
