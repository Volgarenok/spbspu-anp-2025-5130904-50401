#include <iostream>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <iomanip>
namespace ulanova
{
  char * extend(char * old_buffer, size_t old_size, size_t new_size)
  {
    char * new_buffer = static_cast <char *>(malloc(new_size * sizeof(char)));
    if (!new_buffer)
    {
      return nullptr;
    }
    for (size_t i = 0; i < old_size; ++i)
    {
     new_buffer[i] = old_buffer[i];
    }
    return new_buffer;
  }
  char * getline(std::istream & in, size_t & s, size_t & st)
  {
    s = 0;
    st = 0;
    char * buffer = static_cast<char *>(malloc(1 * sizeof(char)));
    if (!buffer)
    {
      return nullptr;
    }
    buffer[0] = '\0';
    bool is_skipws = in.flags() & std::ios_base::skipws;
    if (is_skipws)
    {
      in >> std::noskipws;
    }
    char ch;
    while (in >> ch)
    {
      if (ch == '\n')
      {
        break;
      }
      char * new_buffer = extend(buffer, s, s + 2);
      if (!new_buffer)
      {
        if (is_skipws)
        {
          in >> std::skipws;
        }
        free(buffer);
        return nullptr;
      }
      free(buffer);
      buffer = new_buffer;
      buffer[s++] = ch;
      buffer[s] = '\0';
    }
    if (in.eof())
    {
      st = 1;
      free(buffer);
      return nullptr;
    }
    if (is_skipws)
    {
      in >> std::skipws;
    }
    return buffer;
  }
  void excludeChars(const char* src, const char* exclude, char* result, size_t resultSize)
  {
    if (!src || !exclude || !result || resultSize == 0)
    {
      result[0] = '\0';
      return;
    }
    size_t idx = 0;
    for (const char* p = src; *p != '\0'; ++p)
    {
      int found = 0;
      for (const char * q = exclude; *q != '\0'; ++q)
      {
        if(*p == *q)
        {
          found = 1;
          break;
        }
      }
      if (!found)
      {
        if (idx >= resultSize - 1)
        {
          result[0] = '\0';
          return;
        }
        result[idx++] = *p;
      }
    }
    result[idx] = '\0';
  }
  void appendDigits(const char* src,const char* digitsSrc, char* result_2, size_t resultSize)
  {
    if (!src || !digitsSrc || !result_2 || resultSize == 0)
    {
      result_2[0] = '\0';
      return;
    }
    size_t idx = 0;
    for ( const char* p = src; *p != '\0'; ++p)
    {
      if (idx >= resultSize - 1)
      {
        result_2[0] = '\0';
        return;
      }
      result_2[idx++] = *p;
    }
    for (const char* q = digitsSrc; *q != '\0'; ++q)
    {
      if(std::isdigit(*q))
      {
        int exists = 0;
        for (size_t i = 0; i < idx; ++i)
        {
          if (result_2[i] == *q)
          {
            exists = 1;
            break;
          }
        }
        if (!exists)
        {
          if (idx >= resultSize - 1)
          {
            result_2[0] = '\0';
            return;
          }
          result_2[idx++] = *q;
        }
      }
    }
    result_2[idx] = '\0';
  }
}
int main()
{
  size_t s;
  size_t st;
  char * input = nullptr;
  input = ulanova::getline(std::cin, s, st);
  if (!input)
  {
    if (st == 1)
    {
      std::cerr << "Error EOF\n";
      return 2;
    } else {
      std::cerr << "Error memory\n";
      return 1;
    }
  }
  const size_t max_result_size = 2048;
  char result_2[max_result_size];
  char result[max_result_size];
  const char* excludeStr = "abc";
  const char* digitsStr = "g1h2k";

  ulanova::excludeChars(input, excludeStr, result , max_result_size);
  if (result[0] == '\0')
  {
    std::cerr << "Error: result bufer over\n";
    free(input);
    return 1;
  }
  std::cout << result << '\n';
  ulanova::appendDigits(input, digitsStr, result_2, max_result_size);
  if (result[0] == '\0')
  {
    std::cerr << "Error: result bufer over\n";
    free(input);
    return 1;
  }
  std::cout << result_2 << '\n';
  free(input);
  return 0;
}
