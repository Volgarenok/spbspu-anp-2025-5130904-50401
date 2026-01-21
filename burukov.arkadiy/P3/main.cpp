#include <iostream>
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <limits>

namespace burukov
{
  int* allocateMatrix(size_t rows, size_t cols);
  void deallocateMatrix(int* matrix);
  int countLocalMinima(const int* matrix, size_t rows, size_t cols);
  int countLocalMaxima(const int* matrix, size_t rows, size_t cols);
  bool readMatrixElement(std::ifstream& input, int& value);
  bool readMatrix(std::ifstream& input, int* matrix, size_t rows, size_t cols);
}

int* burukov::allocateMatrix(size_t rows, size_t cols)
{
  return static_cast< int* >(std::malloc(rows * cols * sizeof(int)));
}

void burukov::deallocateMatrix(int* matrix)
{
  std::free(matrix);
}

int burukov::countLocalMinima(const int* matrix, size_t rows, size_t cols)
{
  int count = 0;
  for (size_t i = 1; i < rows - 1; ++i)
  {
    for (size_t j = 1; j < cols - 1; ++j)
    {
      const int current = matrix[i * cols + j];
      bool isMinimum = true;
      isMinimum = isMinimum && (current < matrix[(i - 1) * cols + j]);
      isMinimum = isMinimum && (current < matrix[(i + 1) * cols + j]);
      isMinimum = isMinimum && (current < matrix[i * cols + (j - 1)]);
      isMinimum = isMinimum && (current < matrix[i * cols + (j + 1)]);
      if (isMinimum)
      {
        ++count;
      }
    }
  }
  return count;
}

int burukov::countLocalMaxima(const int* matrix, size_t rows, size_t cols)
{
  int count = 0;
  for (size_t i = 1; i < rows - 1; ++i)
  {
    for (size_t j = 1; j < cols - 1; ++j)
    {
      const int current = matrix[i * cols + j];
      bool isMaximum = true;
      isMaximum = isMaximum && (current > matrix[(i - 1) * cols + j]);
      isMaximum = isMaximum && (current > matrix[(i + 1) * cols + j]);
      isMaximum = isMaximum && (current > matrix[i * cols + (j - 1)]);
      isMaximum = isMaximum && (current > matrix[i * cols + (j + 1)]);
      if (isMaximum)
      {
        ++count;
      }
    }
  }
  return count;
}

bool burukov::readMatrixElement(std::ifstream& input, int& value)
{
  size_t temp = 0;
  if (!(input >> temp))
  {
    return false;
  }

  const size_t maxInt = static_cast< size_t >(std::numeric_limits< int >::max());
  if (temp > maxInt)
  {
    std::cerr << "Number out of int range";
    return false;
  }

  value = static_cast< int >(temp);
  return true;
}

bool burukov::readMatrix(std::ifstream& input, int* matrix, size_t rows, size_t cols)
{
  for (size_t i = 0; i < rows; ++i)
  {
    for (size_t j = 0; j < cols; ++j)
    {
      int value = 0;
      if (!readMatrixElement(input, value))
      {
        if (input.eof())
        {
          std::cerr << "Not enough elements for matrix";
        }
        else if (input.fail())
        {
          input.clear();
          std::cerr << "Unexpected input format";
        }
        return false;
      }
      matrix[i * cols + j] = value;
    }
  }
  return true;
}

int main(int argc, char* argv[])
{
  if (argc != 4)
  {
    const char* errorMsg = (argc < 4) ? "Not enough arguments" : "Too many arguments";
    std::cerr << "Error: " << errorMsg;
    return 1;
  }

  const char* numStr = argv[1];
  if (numStr[0] != '1' && numStr[0] != '2')
  {
    std::cerr << "First parameter is out of range";
    return 1;
  }

  if (numStr[1] != '\0')
  {
    std::cerr << "First parameter is not number";
    return 1;
  }

  const int num = numStr[0] - '0';
  const char* inputFileName = argv[2];
  const char* outputFileName = argv[3];

  std::ifstream input(inputFileName);
  if (!input.is_open())
  {
    std::cerr << "Cannot open input file";
    return 1;
  }

  std::ofstream output(outputFileName);
  if (!output.is_open())
  {
    std::cerr << "Cannot create output file";
    return 1;
  }

  try
  {
    size_t rows = 0;
    size_t cols = 0;
    if (!(input >> rows >> cols))
    {
      std::cerr << "Cannot read matrix dimensions";
      return 2;
    }

    if (rows == 0 && cols == 0)
    {
      output << "0 0";
      return 0;
    }


    const size_t maxStaticSize = 10000;
    int* matrix = nullptr;

    if (num == 1)
    {
      if (rows * cols > maxStaticSize)
      {
        std::cerr << "Matrix is too large for static array";
        return 2;
      }

      matrix = burukov::allocateMatrix(rows, cols);
    }
    else
    {
      matrix = burukov::allocateMatrix(rows, cols);
    }

    if (matrix == nullptr)
    {
      std::cerr << "Memory allocation failed";
      return 2;
    }


    if (!burukov::readMatrix(input, matrix, rows, cols))
    {
      burukov::deallocateMatrix(matrix);
      return 2;
    }

    const int resultMin = burukov::countLocalMinima(matrix, rows, cols);
    const int resultMax = burukov::countLocalMaxima(matrix, rows, cols);
    output << resultMin << '\n';
    output << resultMax;

    burukov::deallocateMatrix(matrix);
  }
  catch (const std::exception& e)
  {
    std::cerr << "Exception: " << e.what();
    return 2;
  }

  return 0;
}
