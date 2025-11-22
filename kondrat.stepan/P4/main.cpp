#include <iostream>
#include <cstddef>
#include <cctype>
#include <iomanip>

namespace kondrat
{
  char * create_str(size_t size)
  {
    char * str = nullptr;
    try
    {
      str = new char[size];
    }
    catch(const std::bad_alloc& e)
    {
      std::cerr << "Memory allocation failed!\n";
      return nullptr;
    }
    return str;
  }

  char * expand_str(char * small_str, size_t small_size, size_t & size)
  {
    size_t new_size = size + 5;
    char* new_str = create_str(new_size);
    if (!new_str)
    {
      return nullptr;
    }
    
    for (size_t i = 0; i < small_size; ++i)
    {
      new_str[i] = small_str[i];
    }
    
    delete[] small_str;
    size = new_size;
    return new_str;
  }

  char * getline(std::istream & in, size_t & size, size_t & pos)
  {
    bool is_skipws = in.flags() & std::ios_base::skipws;
    if (is_skipws)
    {
      in >> std::noskipws;
    }

    size = 5;
    char * buffer = create_str(size);

    if (!buffer)
    {
      return nullptr;
    }

    int ch = 0;

    while (true)
    {
      ch = in.get();
      if (ch == '\n' || ch == EOF)
      {
        break;
      }
      if (pos + 1 >= size)
      {
        char * bigger = expand_str(buffer, size);
        if (!bigger)
        {
          return nullptr;
        }
        buffer = bigger;
        size += 5;
      }
      buffer[pos++] = static_cast< char >(ch);
    }
    buffer[pos] = '\0';

    if(is_skipws)
    {
      in >> std::skipws;
    }
    return buffer;
  }

  size_t len_str(char * str)
  {
    if (!str) return 0;
    size_t len = 0;
    while (str[len] != '\0')
    {
      ++len;
    }
    return len;
  }

  char * uni_two(char * first_str, char * second_str, char * out)
  {
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
    return out;
  }

  size_t dif_lat(char * str, int * used_abc)
  {
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
          int id = ch + 25;
          if (!used_abc[id])
          {
            used_abc[id] = 1;
            ++count;
          }
        }
      }
    }
  }
}

int main()
{
  size_t size = 0;
  size_t pos = 0;
  char * second_str = "def_";
  size_t second_len = kondrat::len_str(second_str);

  char * str = kondrat::getline(std::cin, size, pos);
  if (!str)
  {
    std::cerr << "Failed to read input string\n";
    return 1;
  }

  size_t size_str_uni_two = pos + second_len + 1;

  char * str_uni_two = nullptr;
  char* result_uni_two = kondrat::create_str(size_str_uni_two);
  if (!result_uni_two)
  {
    delete[] str;
    return 1;
  }

  int used_abc[52] = {};
  kondrat::uni_two(str, second_str, str_uni_two);
  size_t ans_dif_lat = kondrat::dif_lat(str, used_abc);

  std::cout << str_uni_two << "\n";
  std::cout << ans_dif_lat << "\n";

  delete[] str;
  delete[] str_uni_two;
}
