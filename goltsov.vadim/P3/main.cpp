#include <iostream>
#include <fstream>
#include <memory>

namespace goltsov
{
  long long * create(size_t rows, size_t cols);
  std::istream & getMtx(long long * mtx, size_t rows, size_t cols, std::istream & input);
  bool lwrTriMtx(const long long * mtx, size_t n, size_t shift, size_t cols, size_t flag1, size_t flag2);
  size_t cntLocMax(const long long * mtx, size_t rows, size_t cols);
}

int main(int argc, char ** argv)
{
  if (argc < 4)
  {
    std::cerr << "Not enough arguments\n";
    return 1;
  }

  if (argc > 4)
  {
    std::cerr << "Too many arguments\n";
    return 1;
  }

  int num = 0;
  if (!isdigit(argv[1][0]) || (!isdigit(argv[1][1]) && argv[1][1] != '\0'))
  {
    std::cout << "First parameter is not a number\n";
    return 1;
  }

  if (argv[1][1] != '\0')
  {
    std::cerr << "First parameter is out of range\n";
    return 1;
  }

  num = argv[1][0] - '0';

  if (num != 1 && num != 2)
  {
    std::cerr << "First parameter is out of range\n";
    return 1;
  }

  std::ifstream input(argv[2]);
  size_t rows = 0;
  size_t cols = 0;
  input >> rows >> cols;

  if (!input)
  {
    std::cerr << "Bad input\n";
    return 2;
  }

  long long * mtx = nullptr;

  if (num == 1)
  {
    long long autoMtx[10000];
    mtx = autoMtx;

    if (!goltsov::getMtx(mtx, rows, cols, input))
    {
      std::cerr << "Bad input\n";
      return 2;
    }
  }
  else
  {
    mtx = goltsov::create(rows, cols);
    if (mtx == nullptr)
    {
      std::cerr << "Bad alloc" << '\n';
      return 3;
    }

    if (!goltsov::getMtx(mtx, rows, cols, input))
    {
      std::cerr << "Bad input\n";
      free(mtx);
      return 2;
    }
  }

  bool answer1;

  if (rows < cols)
  {
    answer1 = goltsov::lwrTriMtx(mtx, rows, cols - rows, cols, 0, 1);
  }
  else
  {
    answer1 = goltsov::lwrTriMtx(mtx, cols, rows - cols, cols, 1, 0);
  }

  size_t answer2 = goltsov::cntLocMax(mtx, rows, cols);

  std::ofstream output(argv[3]);
  output << answer1 << '\n';
  output << answer2 << '\n';

  if (num == 2)
  {
    free(mtx);
  }
}

bool goltsov::lwrTriMtx(const long long * mtx, size_t n, size_t shift, size_t cols, size_t flag1, size_t flag2)
{
  if (n == 0)
  {
    return true;
  }

  for (size_t sh = 0; sh <= shift; ++sh)
  {
    bool flag = false;

    for (size_t i = 0; i < n - 1 && !flag; ++i)
    {
      for (size_t j = i + 1; j < n; ++j)
      {
        if (mtx[(i + sh * flag1) * cols + j + sh * flag2])
        {
          flag = true;
          break;
        }
      }
    }

    if (!flag)
    {
      return true;
    }
  }

  return false;
}

size_t goltsov::cntLocMax(const long long * mtx, size_t rows, size_t cols)
{
  size_t answer = 0;
  if (rows <= 2 || cols <= 2)
  {
    return 0;
  }

  for (size_t i = 1; i < rows - 1; ++i)
  {
    for (size_t j = 1; j < cols - 1; ++j)
    {
      if (mtx[i * cols + j] > mtx[(i - 1) * cols + j] && mtx[i * cols + j] > mtx[(i + 1) * cols + j])
      {
        if (mtx[i * cols + j] > mtx[i * cols + j - 1] && mtx[i * cols + j] > mtx[i * cols + j + 1])
        {
          ++answer;
        }
      }
    }
  }

  return answer;
}

long long * goltsov::create(size_t rows, size_t cols)
{
  long long * mtx = reinterpret_cast< long long * >(malloc(sizeof(long long) * rows * cols));

  return mtx;
}

std::istream & goltsov::getMtx(long long * mtx, size_t rows, size_t cols, std::istream & input)
{
  if (rows == 0 || cols == 0)
  {
    return input;
  }

  for (size_t i = 0; i < rows; ++i)
  {
    for (size_t j = 0; j < cols; ++j)
    {
      input >> mtx[i * cols + j];
    }
  }
  return input;
}
