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
}

int main()
{

}
