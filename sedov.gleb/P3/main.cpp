#include <iostream>
#include <cstddef>
#include <limits>
#include <fstream>

namespace sedov
{
  std::istream & inputMatrix(std::istream & input, int * mtx, size_t rows, size_t cols);
  void convertIncMatrix(int * mtx, size_t rows, size_t cols);
  size_t getNumCol(const int * mtx, size_t rows, size_t cols);
  size_t completeMatrix(std::istream & input, int * mtx, size_t rows, size_t cols, const char * out);
}

int main(int argc, char ** argv)
{
  if (argc < 4)
  {
    std::cerr << "Not enough arguments\n";
    return 1;
  }
  else if (argc > 4)
  {
    std::cerr << "Too many arguments\n";
    return 1;
  }
  else if ((argv[1][0] != '1' && argv[1][0] != '2') || argv[1][1] != '\0')
  {
    std::cerr << "First parameter is out of range\n";
    return 1;
  }

  size_t r = 0, c = 0;
  std::ifstream input(argv[2]);
  input >> r >> c;
  if (!input)
  {
    std::cerr << "Bad reading\n";
    return 2;
  }

  if (argv[1][0] == '1')
  {
    int matrix[10000];
    size_t st = sedov::completeMatrix(input, matrix, r, c, argv[3]);
    return st;
  }

  try
  {
    int * matrix = new int[r * c];
    size_t st = sedov::completeMatrix(input, matrix, r, c, argv[3]);
    delete[] matrix;
    return st;
  }
  catch (const std::bad_alloc & e)
  {
    std::cerr << e.what() << "\n";
    return 3;
  }
}

std::istream & sedov::inputMatrix(std::istream & input, int * mtx, size_t rows, size_t cols)
{
  for (size_t i = 0; i < rows * cols; ++i)
  {
    input >> mtx[i];
  }
  return input;
}

void sedov::convertIncMatrix(int * mtx, size_t rows, size_t cols)
{
  size_t minrc = std::min(rows, cols);
  size_t layer = minrc / 2 + minrc % 2;
  const int MAX = std::numeric_limits< int >::max();
  for (size_t k = 0; k < layer; ++k)
  {
    for (size_t i = k; i < rows - k; ++i)
    {
      for (size_t j = k; j < cols - j; ++j)
      {
        if (mtx[i * cols + j] > MAX - 1)
        {
          throw std::overflow_error("Increment matrix overflow");
        }
        mtx[i * cols + j] += 1;
      }
    }
  }
}

size_t sedov::getNumCol(const int * mtx, size_t rows, size_t cols)
{
  size_t maxLength = 0, maxCol = 0;
  for (size_t j = 0; j < cols; ++j)
  {
    size_t length = 0;
    for (size_t i = 1; i < rows; ++i)
    {
      if (mtx[i * cols + j] == mtx[(i - 1) * cols + j])
      {
        length += 1;
        if (length > maxLength)
        {
          maxLength = length;
          maxCol = j + 1;
        }
      }
      else
      {
        length = 0;
      }
    }
  }
  return maxCol;
}

size_t sedov::completeMatrix(std::istream & input, int * mtx, size_t rows, size_t cols, const char * out)
{
  inputMatrix(input, mtx, rows, cols);
  if (!input)
  {
    if (input.eof())
    {
      std::cerr << "Not enough arguments for matrix\n";
    }
    else
    {
      std::cerr << "Bad reading\n";
    }
    return 2;
  }
  size_t res1 = getNumCol(mtx, rows, cols);
  try
  {
    convertIncMatrix(mtx, rows, cols);
    std::ofstream output(out);
    output << mtx << "\n";
    output << res1 << "\n";
    return 0;
  }
  catch (const std::overflow_error & e)
  {
    std::cerr << e.what() << "\n";
    return 3;
  }
}
