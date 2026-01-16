#include <iostream>
#include <cctype>
#include <iomanip>
#include <cstring>
#include <limits>

namespace petrov {
  void getline(std::istream& in, const size_t size, char* str, size_t& k);
  void rpl_sym(size_t& k, char* new_str, char* rpl_sym_str, char a, char b);
  void lat_two(size_t& s, size_t& k, size_t& r, char* lat_two_str, char* new_str, char* alph);
  bool is_el_in_mass(size_t& k, char* mass, char a);
  char to_lower(char c);
};

char petrov::to_lower(char c) {
  if (c >= 'A' && c <= 'Z') {
    return c + ('a' - 'A');
  }
  return c;
}

bool petrov::is_el_in_mass(size_t& k, char* mass, char a) {
  for (size_t i = 0; i < k; ++i) {
    if (mass[i] == a) {
      return 1;
    }
  }
  return 0;
}

void petrov::lat_two(size_t& s, size_t& k, size_t& r, char* lat_two_str, char* new_str, char* alph) {
  for (size_t i = 0; i < s; ++i) {
    char c = petrov::to_lower(lat_two_str[i]);
    if (c >= 'a' && c <= 'z' && !petrov::is_el_in_mass(r, alph, c)) {
      alph[r++] = c;
    }
  }
  for (size_t i = 0; i < k; ++i) {
    char c = petrov::to_lower(new_str[i]);
    if (c >= 'a' && c <= 'z' && !petrov::is_el_in_mass(r, alph, c)) {
      alph[r++] = c;
    }
  }
  for (size_t i = 0; i < r - 1; ++i) {
    for (size_t j = 0; j < r - i - 1; ++j) {
      if (alph[j] > alph[j + 1]) {
        char temp = alph[j];
        alph[j] = alph[j + 1];
        alph[j + 1] = temp;
      }
    }
  }
}

void petrov::getline(std::istream& in, const size_t size, char* str, size_t& k) {
  in >> std::noskipws;
  while (!in.eof() && in.peek() != '\n' && k < size - 1) {
    if (in.bad() || in.fail()) {
      throw std::logic_error("err");
    }
    in >> str[k++];
  }
  str[k] = '\0';
  in >> std::skipws;
}

void petrov::rpl_sym(size_t& k, char* new_str, char* rpl_sym_str, char a, char b) {
  for (size_t i = 0; i < k; ++i) {
    if (new_str[i] == a) {
      rpl_sym_str[i] = b;
    } else {
      rpl_sym_str[i] = new_str[i];
    }
  }
  rpl_sym_str[k] = '\0';
}

int main() {
  const size_t size = 10000;
  char* str = new char[size];
  memset(str, 0, size);
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
  char* new_str = new char[k + 1];
  memset(new_str, 0, k + 1);
  for (size_t i = 0; i < k; ++i) {
    new_str[i] = str[i];
  }
  new_str[k] = '\0';
  delete[] str;
  char a, b;
  std::cin >> a >> b;
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  char* rpl_sym_str = new char[k + 1];
  memset(rpl_sym_str, 0, k + 1);
  petrov::rpl_sym(k, new_str, rpl_sym_str, a, b);
  char* new_str_2 = new char[size];
  memset(new_str_2, 0, size);
  size_t s = 0;
  try {
    petrov::getline(std::cin, size, new_str_2, s);
  } catch (...) {
    std::cerr << "err\n";
    delete[] rpl_sym_str;
    delete[] new_str;
    delete[] new_str_2;
    return 1;
  }
  char* lat_two_str = new char[s + 1];
  memset(lat_two_str, 0, s + 1);
  for (size_t i = 0; i < s; ++i) {
    lat_two_str[i] = new_str_2[i];
  }
  lat_two_str[s] = '\0';
  delete[] new_str_2;
  size_t r = 0, ch = 26;
  char* alph = new char[ch + 1];
  memset(alph, 0, ch + 1);
  petrov::lat_two(s, k, r, lat_two_str, new_str, alph);
  std::cout << new_str << "\n";
  std::cout << rpl_sym_str << "\n";
  std::cout << alph << "\n";
  delete[] lat_two_str;
  delete[] alph;
  delete[] rpl_sym_str;
  delete[] new_str;
  return 0;
}
