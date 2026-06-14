#include <iostream>
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <limits>

namespace burukov
{
int* createMatrix(size_t rows, size_t cols);
int countLocalMinima(const int* matrix, size_t rows, size_t cols);
int countLocalMaxima(const int* matrix, size_t rows, size_t cols);
bool readMatrixElement(std::ifstream& input, int& value, int* dynamicMatrix = nullptr);
}

int* burukov::createMatrix(size_t rows, size_t cols)
{
  int* matrix = nullptr;
  matrix = static_cast<int*>(malloc(rows * cols * sizeof(int)));
  return matrix;
}

int burukov::countLocalMinima(const int* matrix, size_t rows, size_t cols)
{
  int count = 0;
  for (size_t i = 1; i < rows - 1; ++i)
  {
    for (size_t j = 1; j < cols - 1; ++j)
    {
      const int current = matrix[i * cols + j];
      bool isMinimum = current < matrix[(i - 1) * cols + j];
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
      bool isMaximum = current > matrix[(i - 1) * cols + j];
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

bool burukov::readMatrixElement(std::ifstream& input, int& value, int* dynamicMatrix)
{
  size_t temp = 0;
  if (!(input >> temp))
  {
    if (input.eof())
    {
      std::cerr << "Not enough elements for matrix" << "\n";
      if (dynamicMatrix != nullptr)
      {
        free(dynamicMatrix);
      }
      return false;
    }
    else if (input.fail())
    {
      input.clear();
      std::cerr << "Unexpected input" << "\n";
      if (dynamicMatrix != nullptr)
      {
        free(dynamicMatrix);
      }
      return false;
    }
  }

  const size_t maxInt = static_cast<size_t>(std::numeric_limits<int>::max());
  if (temp > maxInt)
  {
    std::cerr << "Number out of int range" << "\n";
    if (dynamicMatrix != nullptr)
    {
      free(dynamicMatrix);
    }
    return false;
  }

  value = static_cast<int>(temp);
  return true;
}

int main(int argc, char* argv[])
{
  if (argc != 4)
  {
    std::cerr << "Error: " << (argc < 4 ? "Not enough arguments" : "Too many arguments") << "\n";
    return 1;
  }

  const char* numStr = argv[1];
  if (numStr[0] != '1' && numStr[0] != '2')
  {
    std::cerr << "First parameter is out of range" << "\n";
    return 1;
  }

  if (numStr[1] != '\0')
  {
    std::cerr << "First parameter is not number" << "\n";
    return 1;
  }

  const int num = numStr[0] - '0';
  const char* inputFileName = argv[2];
  const char* outputFileName = argv[3];

  std::ifstream input(inputFileName);
  if (!input.is_open())
  {
    std::cerr << "Cannot open input file" << "\n";
    return 1;
  }

  std::ofstream output(outputFileName);
  if (!output.is_open())
  {
    std::cerr << "Cannot create output file" << "\n";
    return 1;
  }

  try
  {
    size_t rows = 0;
    size_t cols = 0;
    if (!(input >> rows >> cols))
    {
      std::cerr << "Cannot read matrix dimensions" << "\n";
      return 2;
    }

    if (rows == 0 && cols == 0)
    {
      output << "0 0" << "\n";
      return 0;
    }

    const size_t maxStaticSize = 10000;
    if (num == 1)
    {
      if (rows * cols > maxStaticSize)
      {
        std::cerr << "Matrix is too large for static array" << "\n";
        return 2;
      }

      int matrix[maxStaticSize];
      for (size_t i = 0; i < rows; ++i)
      {
        for (size_t j = 0; j < cols; ++j)
        {
          int value = 0;
          if (!burukov::readMatrixElement(input, value))
          {
            return 2;
          }
          matrix[i * cols + j] = value;
        }
      }

      const int resultMin = burukov::countLocalMinima(matrix, rows, cols);
      const int resultMax = burukov::countLocalMaxima(matrix, rows, cols);
      output << resultMin << '\n';
      output << resultMax << '\n';
    }
    else
    {
      int* matrix = burukov::createMatrix(rows, cols);
      if (matrix == nullptr)
      {
        std::cerr << "Memory allocation failed" << "\n";
        return 2;
      }

      for (size_t i = 0; i < rows; ++i)
      {
        for (size_t j = 0; j < cols; ++j)
        {
          int value = 0;
          if (!burukov::readMatrixElement(input, value, matrix))
          {
            return 2;
          }
          matrix[i * cols + j] = value;
        }
      }
      const int resultMin = burukov::countLocalMinima(matrix, rows, cols);
      const int resultMax = burukov::countLocalMaxima(matrix, rows, cols);
      output << resultMin << "\n";
      output << resultMax << "\n";
      free(matrix);
    }
  }
  catch (const std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
    return 2;
  }
  return 0;
}
