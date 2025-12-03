#include <iostream>
#include <cstddef>
#include <limits>

namespace burukov
{
  size_t stringLength(const char* str);
  const size_t MAX = std::numeric_limits< size_t >::max();
}

size_t burukov::stringLength(const char* str)
{
  size_t count = 0;
  while (str[count] != '\0')
  {
    ++count;
  }
  return count;
}

int main()
{
  return 0;
}