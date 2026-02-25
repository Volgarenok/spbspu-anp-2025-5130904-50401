#include <iostream>
#include <cstddef>
#include <cctype>
#include <iomanip>

namespace kondrat
{
  char * create_str(size_t size)
  {
    return new char[size];
  }

  char * expand_str(char * small_str, size_t small_size, size_t & size)
  {
    size_t new_size = size + 5;
    char * new_str = create_str(new_size);

    for (size_t i = 0; i < small_size; ++i)
    {
      new_str[i] = small_str[i];
    }

    delete[] small_str;
    size = new_size;
    return new_str;
  }

  char * getline(std::istream & in, size_t & size)
  {
    bool is_skipws = in.flags() & std::ios_base::skipws;
    if (is_skipws)
    {
      in >> std::noskipws;
    }

    size_t cap = 5;
    char * buffer = create_str(cap);

    size = 0;
    char ch = 0;

    if (!in.get(ch))
    {
      delete[] buffer;
      if (is_skipws)
      {
        in >> std::skipws;
      }
      return nullptr;
    }
    if (ch == '\n')
    {
      delete[] buffer;
      if (is_skipws)
      {
        in >> std::skipws;
      }
      return nullptr;
    }

    buffer[size++] = ch;

    while (true)
    {
      if (!in.get(ch) || ch == '\n')
      {
        break;
      }

      if (size >= cap - 1)
      {
        char * bigger = expand_str(buffer, size, cap);
        buffer = bigger;
      }

      buffer[size++] = ch;
    }

    buffer[size] = '\0';

    if (is_skipws)
    {
      in >> std::skipws;
    }
    return buffer;
  }

  size_t len_str(const char * str)
  {
    if (!str)
    {
      return 0;
    }
    size_t len = 0;
    while (str[len] != '\0')
    {
      ++len;
    }
    return len;
  }

  void uni_two(const char * first_str, const char * second_str, char * out)
  {
    if (!first_str || !second_str || !out)
    {
      return;
    }
    size_t i = 0;
    size_t j = 0;
    size_t k = 0;

    while (first_str[i] != '\0' || second_str[j] != '\0')
    {
      if (first_str[i] != '\0')
      {
        out[k++] = first_str[i++];
      }
      if (second_str[j] != '\0')
      {
        out[k++] = second_str[j++];
      }
    }
    out[k] = '\0';
  }

  size_t dif_lat(const char * str, int * used_abc)
  {
    if (!str || !used_abc)
    {
      return 0;
    }
    size_t count = 0;
    for (size_t i = 0; str[i] != '\0'; ++i)
    {
      char ch = str[i];

      if (std::isalpha(ch))
      {
        if (std::isupper(ch))
        {
          int id = ch - 'A';
          if (!used_abc[id])
          {
            used_abc[id] = 1;
            ++count;
          }
        }
        else if (std::islower(ch))
        {
          int id = (ch - 'a') + 26;
          if (!used_abc[id])
          {
            used_abc[id] = 1;
            ++count;
          }
        }
      }
    }
    return count;
  }
}

int main()
{
  char * str = nullptr;
  char * result_uni_two = nullptr;

  try
  {
    size_t size = 0;
    const char * second_str = "def_";
    size_t second_len = kondrat::len_str(second_str);

    str = kondrat::getline(std::cin, size);
    if (!str)
    {
      std::cerr << "Failed to read input string\n";
      return 1;
    }

    size_t size_str_uni_two = size + second_len + 1;

    result_uni_two = kondrat::create_str(size_str_uni_two);

    int used_abc[52] = {};
    kondrat::uni_two(str, second_str, result_uni_two);
    size_t ans_dif_lat = kondrat::dif_lat(str, used_abc);

    std::cout << result_uni_two << "\n";
    std::cout << ans_dif_lat << "\n";

    delete[] str;
    delete[] result_uni_two;
  }

  catch (const std::bad_alloc &)
  {
    delete[] str;
    delete[] result_uni_two;
    return 1;
  }
}
