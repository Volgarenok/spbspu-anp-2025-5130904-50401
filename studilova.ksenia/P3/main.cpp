#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cctype>

namespace studilova
{
  int saddlePoints(const int* matrix, size_t rows, size_t cols);
  int maxDiagonalSum(const int* matrix, size_t rows, size_t cols);
  std::ifstream& readMatrix(std::ifstream& input, int* matrix, size_t rows, size_t cols);
}

int studilova::saddlePoints(const int* matrix, size_t rows, size_t cols)
{
  int count = 0;

  for (size_t i = 0; i < rows; i++)
  {
    for (size_t j = 0; j < cols; j++)
    {
      int current = matrix[i * cols + j];
      bool isMinInRow = true;
      bool isMaxInCol = true;

      for (size_t k = 0; k < cols; k++)
      {
        if (matrix[i * cols + k] < current)
        {
          isMinInRow = false;
          break;
        }
      }

      for (size_t k = 0; k < rows; k++)
      {
        if (matrix[k * cols + j] > current)
        {
          isMaxInCol = false;
          break;
        }
      }

      if (isMinInRow && isMaxInCol)
      {
        count++;
      }
    }
  }

  return count;
}

int studilova::maxDiagonalSum(const int* matrix, size_t rows, size_t cols)
{
  int maxSum = 0;

  for (size_t d = 0; d < cols; d++)
  {
    int sum = 0;
    size_t i = 0;
    size_t j = d;
    while (i < rows && j < cols)
    {
      sum += matrix[i * cols + j];
      i++;
      j++;
    }
    if (sum > maxSum)
    {
      maxSum = sum;
    }
  }

  for (size_t d = 1; d < rows; d++)
  {
    int sum = 0;
    size_t i = d;
    size_t j = 0;
    while (i < rows && j < cols)
    {
      sum += matrix[i * cols + j];
      i++;
      j++;
    }
    if (sum > maxSum)
    {
      maxSum = sum;
    }
  }

  return maxSum;
}

std::ifstream& studilova::readMatrix(std::ifstream& input, int* matrix, size_t rows, size_t cols)
{
  for (size_t i = 0; i < rows * cols; i++)
  {
    input >> matrix[i];
  }
  return input;
}

int main(int argc, char* argv[])
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

  const char* num = argv[1];
  const char* inputFilename = argv[2];
  const char* outputFilename = argv[3];

  int mode = num[0] - '0';

  std::ifstream inputFile(inputFilename);
  if (!inputFile.is_open())
  {
    std::cerr << "Cannot open input file\n";
    return 2;
  }

  size_t rows = 0;
  size_t cols = 0;
  inputFile >> rows >> cols;

  if (inputFile.fail())
  {
    std::cerr << "Can not read matrix dimensions\n";
    return 2;
  }

  if (rows == 0 || cols == 0)
  {
    std::ofstream outputFile(outputFilename);
    outputFile << "0 0\n";
    return 0;
  }

  if (rows * cols > 10000)
  {
    std::cerr << "Matrix is too big\n";
    return 2;
  }

  int* matrix = nullptr;
  int stackMemory[10000];

  if (mode == 1)
  {
    matrix = stackMemory;
  }
  else
  {
    matrix = static_cast< int* >(malloc(rows * cols * sizeof(int)));
    if (matrix == nullptr)
    {
      std::cerr << "Memory allocation failed\n";
      return 2;
    }
  }

  if (!studilova::readMatrix(inputFile, matrix, rows, cols))
  {
    std::cerr << "Invalid matrix data\n";
    if (mode == 2)
    {
      free(matrix);
    }
    return 2;
  }

  inputFile.close();

  int result1 = studilova::saddlePoints(matrix, rows, cols);
  int result2 = studilova::maxDiagonalSum(matrix, rows, cols);

  std::ofstream outputFile(outputFilename);
  outputFile << result1 << " " << result2 << "\n";
  if (mode == 2)
  {
    free(matrix);
  }

  return 0;
}
