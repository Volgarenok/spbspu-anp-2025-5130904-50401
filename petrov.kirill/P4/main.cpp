#include <iostream>
#include <cctype>
#include <iomanip>

namespace petrov {
  void getline(std::istream& in, const size_t size, char* str, size_t& k);
  void rpl_sym(size_t& k, char* new_str, char* rpl_sym_str, char a, char b);
  void lat_two(size_t& s, size_t& k, size_t& r, size_t& ch, char* lat_two_str, char* new_str, char* alph);
  bool is_el_in_mass(size_t& k, char* mass, char a);
};

bool petrov::is_el_in_mass(size_t& k, char* mass, char a) {
  for (size_t i = 0; i < k; ++i) {
    if (mass[i] == a) {
      return 1;
    }
  }
  return 0;
}

void petrov::lat_two(size_t& s, size_t& k, size_t& r, size_t& ch, char* lat_two_str, char* new_str, char* alph) {
  for (size_t i = 0; i < s && r < ch; ++i) {
    if (!petrov::is_el_in_mass(ch, alph, lat_two_str[i])) {
      alph[r++] = lat_two_str[i];
    }
  }
  for (size_t i = 0; i < k && r < ch; ++i) {
    if (!petrov::is_el_in_mass(ch, alph, new_str[i])) {
      alph[r++] = new_str[i];
    }
  }
}

void petrov::getline(std::istream& in, const size_t size, char* str, size_t& k) {
  std::cin >> std::noskipws;
  while (in.peek() != '\n' && k <= size && !in.eof()) {
    if (in.bad() || in.fail()) {
      throw std::logic_error("err");
    }
    in >> str[k++];
  }
  std::cin >> std::skipws;
}

void petrov::rpl_sym(size_t& k, char* new_str, char* rpl_sym_str, char a, char b) {
  if (k != 0) {
    for (size_t i = 0; i < 1; ++i) {
      if (new_str[i] == a) {
        rpl_sym_str[i] = b;
      } else {
        rpl_sym_str[i] = new_str[i];
      }
    }
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
  char* new_str = new char[k + 1];
  if (k > 0) {
    for (size_t i = 0; i < k; ++i) {
      new_str[i] = str[i];
    }
    new_str[k] = '\0';
  }
  delete[] str;
  char a, b;
  std::cin >> a >> b;
  char* rpl_sym_str = new char[k + 1];
  if (k > 0) {
    petrov::rpl_sym(k, new_str, rpl_sym_str, a, b);
  }
  char* new_str_2 = new char[size];
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
  char* lat_two_str = new char[s];
  for (size_t i = 0; i < s; ++i) {
    lat_two_str[i] = new_str_2[i];
  }
  delete[] new_str_2;
  size_t r = 0, ch = 52;
  char* alph = new char[ch];
  for (size_t i = 0; i < ch; ++i) {
    alph[i] = ' ';
  }
  petrov::lat_two(s, k, r, ch, lat_two_str, new_str, alph);
  for (size_t i = 0; i < k; ++i) {
    std::cout << new_str[i];
  }
  std::cout << "\n";
  for (size_t i = 0; i < k; ++i) {
    std::cout << rpl_sym_str[i];
  }
  std::cout << "\n";
  for (size_t i = 0; i < r; ++i) {
    std::cout << alph[i];
  }
  delete[] lat_two_str;
  delete[] alph;
  delete[] rpl_sym_str;
  delete[] new_str;
  return 0;
}
