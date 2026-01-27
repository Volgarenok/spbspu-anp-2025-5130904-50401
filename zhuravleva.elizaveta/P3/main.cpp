#include <iostream>
#include <fstream>

namespace zhuravleva {
  const size_t maxSize = 10000;

  bool readMatrixElements(std::ifstream& file, int* matrix, size_t rows, size_t cols)
  {
    for (size_t i = 0; i < rows; i++)
    {
      for (size_t j = 0; j < cols; j++)
      {
        if (!(file >> matrix[i * cols + j]))
        {
          return false;
        }
      }
    }
    return true;
  }

  std::ifstream& readMatrix(std::ifstream& file, int** matrix, size_t& rows, size_t& cols)
  {
    *matrix = nullptr;
    if (!(file >> rows >> cols))
    {
      return file;
    }

    if (rows == 0 || cols == 0)
    {
      return file;
    }
    return file;
  }

  size_t colsNoDublicats(const int* matrix, size_t rows, size_t cols)
  {
    if (rows == 0 || cols == 0 || matrix == nullptr)
    {
      return 0;
    }
    size_t count = 0;
    for (size_t j = 0; j < cols; j++)
    {
      bool isDublics = false;
      for (size_t i = 0; i < rows - 1; i++)
      {
        if (matrix[i * cols + j] == matrix[(i + 1) * cols + j])
        {
          isDublics = true;
        }
      }
      if (!isDublics)
      {
        count++;
      }
    }
    return count;
  }

  size_t diagonalsNoZero(const int* matrix, size_t rows, size_t cols)
  {
    if (rows == 0 || cols == 0 || matrix == nullptr)
    {
      return 0;
    }
    size_t count = 0;
    for (size_t shift = 1; shift < cols; shift++)
    {
      bool hasZero = false;
      for (size_t i = 0; i < rows && i + shift < cols; i++)
      {
        if (matrix[i * cols + (i + shift)] == 0)
        {
          hasZero = true;
        }
      }
      if (!hasZero)
      {
        count++;
      }
    }

    for (size_t shift = 1; shift < rows; shift++)
    {
      bool hasZero = false;
      for (size_t i = 0; i < cols && i + shift < rows; i++)
      {
        if (matrix[(i + shift) * cols + i] == 0)
        {
          hasZero = true;
        }
      }
      if (!hasZero)
      {
        count++;
      }
    }
    return count;
  }
}

int main(int argc, char* argv[])
{
  if (argc != 4)
  {
    std::cerr << "Need 3 arguments: 1) mode 2) input 3) output\n";
    return 1;
  }
  const char* mode = argv[1];
  if (mode[0] != '1' && mode[0] != '2')
  {
    std::cerr << "Mode must be 1 or 2\n";
    return 1;
  }
  bool isFixedSize = (mode[0] == '1');

  int* matrix = nullptr;
  const int* matrixForRead = nullptr;

  size_t rows = 0, cols = 0;
  int fixedBuffer[zhuravleva::maxSize];
  std::ifstream file_input(argv[2]);
  if (!file_input) {
    std::cerr << "Error: Cannot open input file.\n";
    return 1;
  }
  zhuravleva::readMatrix(file_input, &matrix, rows, cols);
  if (!file_input) {
    std::cerr << "Error: Invalid matrix data or read error.\n";
    return 2;
  }

  if (isFixedSize)
  {
    if (cols > 0 && rows > (zhuravleva::maxSize / cols))
    {
      std::cerr << "Error: Matrix too large for fixed buffer.\n";
      return 2;
    }
    matrix = fixedBuffer;
  }
  else
  {
    matrix = new int[rows * cols];
  }

  if (!zhuravleva::readMatrixElements(file_input, matrix, rows, cols)) {
    std::cerr << "Error: Failed to read matrix elements.\n";
    if (!isFixedSize) {
      delete[] matrix;
    }
    return 2;
  }
  matrixForRead = matrix;
  size_t resultForColsNoDublicats = zhuravleva::colsNoDublicats(matrixForRead, rows, cols);
  size_t resultForDiagonalsNoZero = zhuravleva::diagonalsNoZero(matrixForRead, rows, cols);

  std::ofstream file_output(argv[3]);
  if (!file_output) {
    std::cerr << "Error: Cannot open output file.\n";
    if (!isFixedSize) {
      delete[] matrix;
    }
    return 1;
  }
  file_output << resultForColsNoDublicats << " ";
  file_output << resultForDiagonalsNoZero << "\n";
  if (!isFixedSize) {
    delete[] matrix;
    matrix = nullptr;
  }
  return 0;
}
