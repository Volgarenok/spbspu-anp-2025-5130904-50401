#include <iostream>
#include <fstream>

namespace stupir
{
  bool checkAddSnail(size_t up, size_t down, size_t left, size_t right)
  {
    return (up <= down && left <= right);
  }

  void addSnail(const int * arr1, size_t rows, size_t cols, int * arr2)
  {
    size_t sum = 1;
    size_t left = 0;
    size_t right = cols - 1;
    size_t up = 0;
    size_t down = rows - 1;
    while (checkAddSnail(up, down, left, right))
    {
      for (size_t i = left; i < right + 1; ++i)
      {
        arr2[cols * down + i] += sum + arr1[cols * down + i];
        sum++;
      }
      down--;

      if (!checkAddSnail(up, down, left, right))
      {
        break;
      }

      for (size_t i = down; i > up ; --i)
      {
        arr2[cols * i + right] += sum + arr1[cols * i + right];
        sum++;
      }
      arr2[cols * up + right] += sum + arr1[cols * up + right];
      sum++;
      right--;

      if (!checkAddSnail(up, down, left, right))
      {
        break;
      }

      for (size_t i = right; i > left; --i)
      {
        arr2[up * cols + i] += sum + arr1[up * cols + i];
        sum++;
      }
      arr2[up * cols + left] += sum + arr1[up * cols + left];
      sum++;
      up++;

      if (!checkAddSnail(up, down, left, right))
      {
        break;
      }

      for (size_t i = up; i < down + 1; ++i)
      {
        arr2[cols * i + left] += sum + arr1[cols * i + left];
        sum++;
      }
      left++;
    }
  }

  std::ifstream & readArr(std::ifstream & input, size_t rows, size_t cols, int * arr)
  {
    for (size_t i = 0; i < rows * cols; ++i)
    {
      input >> arr[i];
    }
    return input;
  }

  void writeArr(std::ofstream & output, size_t rows, size_t cols, const int * arr)
  {
    if (!output.fail())
    {
      output << arr[0];
      for (size_t i = 1; i < rows * cols; ++i)
      {
        output << " " << arr[i];
      }
    }
    else
    {
      std::cerr << "Сouldn't open the file for writing\n";
    }
  }

  size_t countNotZeroD(const int * arr, size_t rows, size_t cols)
  {
    size_t result = 0;
    if (rows == 0 && cols == 0)
    {
      return 0;
    }
    for (size_t k = 0; k < rows; ++k)
    {
      size_t num = 0;
      for (size_t i = 0; i < rows; ++i)
      {
        if (i - k < cols)
        {
          if (arr[cols * i + i - k] == 0)
          {
            num++;
          }
        }
      }
      if (num == 0)
      {
        result++;
      }
    }

    for (size_t k = 1; k < cols; ++k)
    {
      size_t num = 0;
      for (size_t i = 0; i < rows; ++i)
      {
        if (i + k < cols)
        {
          if (arr[cols * i + i + k] == 0)
          {
            num++;
          }
        }
      }
      if (num == 0)
      {
        result++;
      }
    }
    return result;
  }
}
int main(int argc, char ** argv)
{
  const char * firstArg = argv[1];
  const char * secondArg = argv[2];
  const char * thirdArg = argv[3];

  if (argc < 4)
  {
    std::cerr << "Not enough argument\n";
    return 1;
  }
  else if (argc > 4)
  {
    std::cerr << "Too many arguments\n";
    return 1;
  }
  else if ((firstArg[0] != '1' && firstArg[0] != '2') || firstArg[1] != '\0')
  {
    std::cerr << "First parametr out of range\n";
    return 1;
  }

  std::ifstream input(secondArg);
  if (!input.is_open())
  {
    std::cerr << "Error when opening a file\n";
    return 2;
  }

  size_t rows = 0;
  size_t cols = 0;
  input >> rows;
  input >> cols;
  if (input.fail() || (rows == 0 && cols) || (rows && cols == 0))
  {
    std::cerr << "Irregular matrix sizes\n";
    return 2;
  }

  const size_t maxStat = 10000;
  int * matrixFile = nullptr;
  int * matrixChange = nullptr;
  size_t numDigNotNull = 0;
  namespace stu = stupir;
  try
  {
    if (firstArg[0] == '1')
    {
      if (rows * cols <= maxStat)
      {
        int buffer[maxStat] = {};
        matrixFile = buffer;
      }
      else
      {
        throw std::bad_alloc();
      }
    }
    else
    {
      matrixFile = new int[rows * cols]();
    }

    if (!stu::readArr(input, rows, cols, matrixFile))
    {
      std::cerr << "Non-correct values of matrix elements\n";
      if (firstArg[0] == '2')
      {
        delete [] matrixFile;
      }
      return 2;
    }
    input.close();
    matrixChange = new int[rows * cols]();
    if (rows != 0 && cols != 0)
    {
      stu::addSnail(matrixFile, rows, cols, matrixChange);
    }
    numDigNotNull = stu::countNotZeroD(matrixFile, rows, cols);
  }
  catch (const std::bad_alloc & e)
  {
    delete [] matrixFile;
    delete [] matrixChange;
    std::cerr << "Not enough memory\n";
    return 2;
  }
  std::ofstream output(thirdArg);
  if (rows != 0 && cols != 0)
  {
    output << rows << " " << cols << " ";
    stu::writeArr(output, rows, cols, matrixChange);
  }
  else
  {
    output << rows << " " << cols;
  }
  output << "\n" << numDigNotNull;

  if (firstArg[0] == '2')
  {
    delete [] matrixFile;
  }
  delete [] matrixChange;
}
