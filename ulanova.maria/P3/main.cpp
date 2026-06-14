#include <iostream>
#include <fstream>

namespace ulanova {
  int*  readMatrix(std::ifstream& input, size_t& rows, size_t& cols, bool isFixedSize, bool& hadReadError)
  {
    if (!(input >> rows >> cols))
    {
      std::cerr << "Error: Invalid matrix\n";
      hadReadError = true;
      return nullptr;
    }

    if (rows == 0 || cols == 0)
    {
      return nullptr;
    }

    if (isFixedSize && rows * cols > 10000)
    {
      std::cerr << "Error: Matrix maximum size (10000)\n";
      hadReadError = true;
      return nullptr;
    }
    int* matrix = new int[rows * cols];
    for (size_t i = 0; i < rows; ++i)
    {
      for (size_t j = 0; j < cols; ++j)
      {
        if (!(input >> matrix[i * cols + j]))
        {
          delete[] matrix;
          std::cerr << "Error: Failed to read matrix \n";
          hadReadError = true;
          return nullptr;
        }
      }
    }
    return matrix;
  }
  size_t countSaddlePoints(const int* matrix, size_t rows, size_t cols)
  {
    if (!matrix || rows == 0 || cols == 0)
    {
      return 0;
    }

    size_t saddleCount = 0;

    for (size_t i = 0; i < rows; ++i)
    {
      int minVal = matrix[i * cols];
      size_t minCol = 0;
      for (size_t j = 1; j < cols; ++j)
      {
        if (matrix[i * cols + j] < minVal)
        {
          minVal = matrix[i * cols + j];
          minCol = j;
        }
      }
      bool isMax = true;
      for (size_t k = 0; k < rows; ++k)
      {
        if (matrix[k * cols + minCol] > minVal)
        {
          isMax = false;
          break;
        }
      }

      if (isMax)
      {
        saddleCount++;
      }
    }
    return saddleCount;
  }
  void spiralTransform(int* matrix, size_t rows, size_t cols)
  {
    if (!matrix || rows == 0 || cols == 0)
    {
      return;
    }

    int top = 0, bottom = rows - 1;
    int left = 0, right = cols - 1;
    int counter = 1;

    while (top <= bottom && left <= right)
    {
      for (int j = left; j <= right; ++j)
      {
        matrix[top * cols + j] -= counter++;
      }
      top++;
      for (int i = top; i <= bottom; ++i)
      {
        matrix[i * cols + right] -= counter++;
      }
      right--;
      if (top <= bottom)
      {
        for (int j = right; j >= left; --j)
        {
          matrix[bottom * cols + j] -= counter++;
        }
        bottom--;
      }
      if (left <= right)
      {
        for (int i = bottom; i >= top; --i)
        {
          matrix[i * cols + left] -= counter++;
        }
        left++;
      }
    }

  }

}

int main(int argc, char* argv[])
{
  if (argc != 4)
  {
    std::cerr << "Error: Need 3 arguments\n";
    return 1;
  }
  const char* mode = argv[1];
  if (mode[0] != '1' && mode[0] != '2')
  {
    std::cerr << "Error: Mode must be 1 or 2\n";
    return 1;
  }
  bool isFixedSize = (mode[0] == '1');
  std::ifstream input(argv[2]);
  if (!input)
  {
    std::cerr << "Error: Cannot open input file \n";
    return 2;
  }
  std::ofstream output(argv[3]);
  if (!output)
  {
    std::cerr << "Error: Cannot open output file\n";
    return 3;
  }
  size_t rows = 0, cols = 0;
  bool hadReadError = false;
  int* matrix = ulanova::readMatrix(input, rows, cols, isFixedSize, hadReadError);
  if (!matrix)
  {
    if (hadReadError)
    {
      return 4;
    }
    output << "0\n";
    return 0;
  }
  size_t saddleCount = ulanova::countSaddlePoints(matrix, rows, cols);
  ulanova::spiralTransform(matrix, rows, cols);
  output << saddleCount << "\n";
  for (size_t i = 0; i < rows; ++i)
  {
    for (size_t j = 0; j < cols; ++j)
    {
      output << matrix[i * cols + j] << " ";
    }
    output << "\n";
  }
  delete[] matrix;
  return 0;
}
