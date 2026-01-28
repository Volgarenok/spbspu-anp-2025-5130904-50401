#include <iostream>
#include <iomanip>
#include <cctype>

namespace tarasenko
{
  bool is_vowel(char c)
  {
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y');
  }

  void remove_vowels(const char * string, char * output, size_t len)
  {
    size_t k = 0;
    for (size_t i = 0; i < len; ++i)
    {
      char current = string[i];
      char lower_c = std::tolower(current);
      if (is_vowel(lower_c))
      {
        continue;
      }
      output[k] = current;
      k++;
    }
    output[k] = '\0';
  }

  void upp_to_low(const char * string, char * output, size_t len)
  {
    for (size_t i = 0; i < len; ++i)
    {
      output[i] = std::tolower(string[i]);
    }
    output[len] = '\0';
  }

  char * getline(std::istream & in, size_t & len)
  {
    bool is_skipws = in.flags() & std::ios_base::skipws;
    if (is_skipws)
    {
      in >> std::noskipws;
    }
    const size_t step = 10;
    char * string = nullptr;
    char * temp_mem = nullptr;
    char last_symbol = '\0';
    size_t k = 0;
    while (in)
    {
      in >> last_symbol;
      if (!in || (last_symbol == '\n' && !k))
      {
        delete[] string;
        throw std::runtime_error("input error");
      }
      if (last_symbol == '\n')
      {
        break;
      }
      if (k % step == 0)
      {
        temp_mem = new char[k + step];
        for (size_t i = 0; i < k; ++i)
        {
          temp_mem[i] = string[i];
        }
        delete[] string;
        string = temp_mem;
      }
      string[k] = last_symbol;
      k++;
    }
    string[k] = '\0';
    len = k;
    if (is_skipws)
    {
      in >> std::skipws;
    }
    return string;
  }
}

int main()
{
  size_t len = 0;
  char * output = nullptr;
  char * string = nullptr;
  try
  {
    string = tarasenko::getline(std::cin, len);
    output = new char[len + 1]{};
  }
  catch (const std::runtime_error &e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
  catch (const std::bad_alloc &)
  {
    std::cerr << "failed to allocate memory\n";
    return 1;
  }
  tarasenko::upp_to_low(string, output, len);
  std::cout << output << '\n';
  tarasenko::remove_vowels(string, output, len);
  std::cout << output << '\n';
  delete[] output;
  delete[] string;
}
