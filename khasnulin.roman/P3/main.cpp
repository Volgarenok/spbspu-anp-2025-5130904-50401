#include <cstddef>
#include <fstream>
#include <iostream>
#include <istream>
#include <ostream>
#include <stdexcept>

namespace khasnulin
{

  size_t getFirstParameter(const char *num);

  std::istream &readMatrix(std::istream &input, int *arr, size_t n, size_t m, size_t &elems_count);

  void lftBotClk(int *arr, size_t n, size_t m);

  bool lwrTriMtx(const int *arr, size_t n, size_t m);

  std::ostream &printMatrix(std::ostream &output, const int *a, size_t n, size_t m);
}

int main(int argc, char **argv)
{
  size_t mode = 0;
  int *currArr = nullptr;
  if (argc != 4)
  {
    const char *message = argc > 4 ? "Too many arguments\n" : "Not enough arguments\n";
    std::cerr << message;
    return 1;
  }
  try
  {
    mode = khasnulin::getFirstParameter(argv[1]);

    std::ifstream input(argv[2]);
    size_t n = 1, m = 1;

    int arr[10000] = {};

    input >> n >> m;
    currArr = mode == 1 ? arr : new int[n * m];

    size_t elems_count = 0;
    khasnulin::readMatrix(input, currArr, n, m, elems_count);

    if ((!input.eof() && input.fail()) || (elems_count != n * m))
    {
      if (mode == 2)
      {
        delete[] currArr;
      }
      std::cerr << "Error while reading input file data, can't read as matrix\n";
      return 2;
    }
    input.close();

    bool isLWR_TRI_MTX = khasnulin::lwrTriMtx(currArr, n, m);
    khasnulin::lftBotClk(currArr, n, m);

    std::ofstream output(argv[3]);

    khasnulin::printMatrix(output, currArr, n, m);
    output << std::boolalpha << isLWR_TRI_MTX;

    if (mode == 2)
    {
      delete[] currArr;
    }
  }
  catch (const std::bad_alloc &e)
  {
    std::cerr << "Error memory allocation\n";
    return 2;
  }
  catch (const std::runtime_error &e)
  {
    if (mode == 2)
    {
      delete[] currArr;
    }
    std::cerr << e.what() << "\n";
    return 1;
  }
  catch (...)
  {
    std::cerr << "Error during task execution, something went wrong\n";
    if (mode == 2)
    {
      delete[] currArr;
    }
    return 2;
  }
}

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

void khasnulin::lftBotClk(int *arr, size_t n, size_t m)
{
  if (n > 0 && m > 0)
  {
    size_t currI = (n - 1) * m;

    int directionI = -1;
    int directionJ = 0;
    int factor = 1;
    size_t spiral_circle = 0;
    size_t elem_counter = 0;
    for (size_t i = 0; i < n * m; i++)
    {
      arr[currI] -= factor;
      factor++;
      elem_counter++;
      if (directionI && elem_counter == (n - spiral_circle))
      {
        if (directionI == -1)
        {
          directionJ = 1;
        }
        else
        {
          directionJ = -1;
        }
        spiral_circle++;
        elem_counter = 0;
        directionI = 0;
      }
      else if (directionJ && elem_counter == (m - spiral_circle))
      {
        if (directionJ == -1)
        {
          directionI = -1;
        }
        else
        {
          directionI = 1;
        }
        elem_counter = 0;
        directionJ = 0;
      }
      currI += directionI * m + directionJ;
    }
  }
}

bool khasnulin::lwrTriMtx(const int *arr, size_t n, size_t m)
{
  size_t minSide = std::min(n, m);
  if (minSide == 0)
  {
    return false;
  }
  for (size_t i = 0; i < minSide; i++)
  {
    for (size_t j = i + 1; j < m; j++)
    {
      if (arr[i * m + j] != 0)
      {
        return false;
      }
    }
  }

  return true;
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
