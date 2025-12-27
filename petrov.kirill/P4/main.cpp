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
      break;
    }
    in >> str[k++];
  }
}

int main() {
  const size_t size = 10000;
  char* str = new char[size];
  size_t k = 0;
  petrov::getline(std::cin, size, str, k);
  char* new_str = new char[k];
  for (size_t i = 0; i < k; ++i) {
    new_str[i] = str[i];
  }
  delete[] str;
  if (k != 0) {
    for (size_t i = 0; i < k; ++i) {
      std::cout << new_str[i];
    }
    return 0;
    delete[] new_str;
  } else {
    std::cerr << "err\n";
    delete[] new_str;
    return 1;
  }
}
