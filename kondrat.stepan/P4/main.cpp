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
    }
    return str;
  }

  char * expand_str(char * small_str, size_t small_size)
  {
    size_t new_size = small_size + 5;
    char * new_str = nullptr;
    try
    {
      new_str = new char[new_size];
    }
    catch(const std::bad_alloc& e)
    {
      std::cerr << "Memory allocation failed!\n";
    }
    for (size_t i = 0; i < small_size; ++i)
    {
      new_str[i] = small_str[i];
    }
    delete[] small_str;
    return new_str;
  }

  char * getline(std::istream & in, size_t & size)
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

    size_t pos = 0;
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
}

int main()
{

}
