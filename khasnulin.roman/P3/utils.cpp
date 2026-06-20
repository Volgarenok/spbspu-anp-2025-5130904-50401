#include "utils.hpp"
#include <iostream>
#include <stdexcept>

size_t khasnulin::getFirstParameter(const char *num)
{
  size_t len = 0;
  const char *ch = num;
  while (*ch)
  {
    len++;
    ch++;
  }
  if (len == 1)
  {
    if (num[0] == '1')
    {
      return 1;
    }
    else if (num[0] == '2')
    {
      return 2;
    }
  }
  throw std::runtime_error("Incorrect first parameter input\n");
}

using is_t = std::istream;
is_t &khasnulin::readMatrix(is_t &input, int *arr, size_t n, size_t m, size_t &elems_count)
{
  elems_count = 0;
  while ((elems_count < n * m) && (input >> arr[elems_count]))
  {
    elems_count++;
  }

  return input;
}

using os_t = std::ostream;
os_t &khasnulin::printMatrix(os_t &output, const int *a, size_t n, size_t m)
{
  output << n << " " << m << " ";
  if (n > 0 && n > 0)
  {
    for (size_t i = 0; i < n * m - 1; i++)
    {
      output << a[i] << " ";
    }
    output << a[m * n - 1];
  }
  output << "\n";
  return output;
}
