#include <iostream>
#include <iomanip>
#include <cctype>

namespace petrov
{
  size_t getline(std::istream& in, char* s, size_t q);
  char* rpl_sym(std::istream& in, char* s, size_t q);
  char* lat_two(std::istream& in, char* s, char* new_s, size_t q, size_t size);
  bool find_char(char* a, char b, size_t q);
  char* sortin(char* a, size_t q);
}

char* petrov::sortin(char* a, size_t q)
{
  for (size_t i = 0; i < q; ++i)
  {
    for (size_t j = 0; j < q - 1; ++j)
    {
      if (a[j] > a[j + 1])
      {
        size_t d = a[j];
        a[j] = a[j + 1];
        a[j + 1] = d;
      }
    }
  }
  return a;
}

size_t petrov::getline(std::istream& in, char* s, size_t q)
{
  size_t i = 0;
  for (; i < q; ++i)
  {
    in >> s[i];
    if (in.peek() == '\n')
    {
      return i + 2;
    }
  }
  if (!in.eof())
  {
    delete[] s;
    throw std::logic_error("err");
  }
  return q;
}

bool petrov::find_char(char* a, char b, size_t q)
{
  for (size_t i = 0; i < q; ++i)
  {
    if (a[i] == b)
    {
      return 1;
    }
  }
  return 0;
}

char* petrov::lat_two(std::istream& in, char* s, char* new_s, size_t q, size_t size)
{
  char* alph = new char[53];
  size_t j = 0;
  for (size_t i = 0; i < q; ++i)
  {
    if (isalpha(s[i]) && !petrov::find_char(alph, s[i], 53))
    {
      alph[j] = s[i];
      j++;
    }
  }
  for (size_t i = 0; i < size; ++i)
  {
    if (isalpha(new_s[i]) && !petrov::find_char(alph, new_s[i], 53))
    {
      alph[j] = new_s[i];
      j++;
    }
  }
  char* new_alph = sortin(alph, j);
  delete[] new_s;
  return new_alph;
}

char* petrov::rpl_sym(std::istream& in, char* s, size_t q)
{
  char a, b;
  in >> a >> b;
  char* new_a = new char[q];
  for (size_t i = 0; i < q - 1; ++i)
  {
    if (s[i] == a)
    {
      new_a[i] = b;
    }
    else
    {
      new_a[i] = s[i];
    }
  }
  return new_a;
}

int main()
{
  const size_t size = 10000;
  char* s = new char[size];
  size_t d = size;
  try
  {
    std::cin >> std::noskipws;
    d = petrov::getline(std::cin, s, d);
  }
  catch (...)
  {
    std::cerr << "err\n";
    return 1;
  }
  std::cin >> std::skipws;
  char* rpl_sym_char = new char[d];
  rpl_sym_char = petrov::rpl_sym(std::cin, s, d);
  char* lat_two_char = new char[53];
  char* new_s = new char[size];
  std::cin >> std::skipws;
  size_t w;
  try
  {
    w = petrov::getline(std::cin, new_s, size);
  }
  catch (...)
  {
    std::cerr << "err\n";
    return 1;
  }
  lat_two_char = petrov::lat_two(std::cin, s, new_s, d, w);
  std::cout << rpl_sym_char << "\n" << lat_two_char << "\n";
  delete[] lat_two_char;
  delete[] rpl_sym_char;
  delete[] s;
  delete[] new_s;
  return 0;
}
