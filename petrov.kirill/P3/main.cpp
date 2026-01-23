#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstdlib>

namespace petrov
{
  bool fill_massive(size_t r, size_t c, std::ifstream& in, int* mtx)
  {
    int q = 0;
    size_t n = (r < c) ? r : c;
    for (size_t i = 0; i < r; ++i)
    {
      for (size_t j = 0; j < c; ++j)
      {
        if (!(in >> q))
        {
          return false;
        }
        if (i < n && j < n)
        {
          mtx[i * n + j] = q;
        }
      }
    }
    return true;
  }

  void count_diagonal(size_t n, size_t& s, const int* mtx)
  {
    for (int k = 1 - (int)n; k <= (int)n - 1; ++k)
    {
      bool iszero = false;
      size_t count = 0;
      for (size_t i = 0; i < n; ++i)
      {
        int j = (int)i - k;
        if (j >= 0 && j < (int)n)
        {
          count++;
          if (mtx[i * n + j] == 0)
          {
            iszero = true;
          }
        }
      }
      if (count > 0 && !iszero)
      {
        s++;
      }
    }
  }

  void fll_inc_way(std::ofstream& ou, const int* mtx, size_t n)
  {
    size_t s = 0;
    petrov::count_diagonal(n, s, mtx);
    ou << s << "\n";
  }

  void write_output(std::ofstream& ou, size_t n, const int* mtx)
  {
    ou << n << " " << n << " " << "\n";
    for (size_t i = 0; i < n; ++i)
    {
      for (size_t j = 0; j < n; ++j)
      {
        ou << mtx[i * n + j] << (j == n - 1 ? "" : " ");
      }
      ou << "\n";
    }
  }

  void reform(size_t n, int* mtx)
  {
    size_t layers = (n + 1) / 2;
    for (size_t d = 1; d <= layers; ++d)
    {
      for (size_t i = d - 1; i < n - d + 1; ++i)
      {
        for (size_t j = d - 1; j < n - d + 1; ++j)
        {
          mtx[i * n + j] += (int)d;
        }
      }
    }
  }

  void cnt_nzr_dig(std::ofstream& ou, int* mtx, size_t n)
  {
    petrov::reform(n, mtx);
    petrov::write_output(ou, n, mtx);
  }
}

int main(int argc, char** argv)
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

  char type = argv[1][0];
  if ((type != '1' && type != '2') || argv[1][1] != '\0')
  {
    std::cerr << "First parameter is out of range\n";
    return 1;
  }

  std::ifstream in(argv[2]);
  if (!in.is_open())
  {
    std::cerr << "Cannot open input file\n";
    return 2;
  }

  size_t rows = 0, cols = 0;
  if (!(in >> rows >> cols))
  {
    std::cerr << "err\n";
    return 2;
  }

  if (rows == 0 || cols == 0)
  {
    return 0;
  }

  size_t n = (rows < cols) ? rows : cols;
  int statmtx[10000] = {0};
  int* mtx = nullptr;

  if (type == '1')
  {
    if (n * n > 10000)
    {
      std::cerr << "Static array overflow\n";
      return 2;
    }
    mtx = statmtx;
  }
  else
  {
    mtx = reinterpret_cast<int*>(std::malloc(sizeof(int) * n * n));
    if (mtx == nullptr)
    {
      std::cerr << "Memory allocation failed\n";
      return 2;
    }
  }

  if (!petrov::fill_massive(rows, cols, in, mtx))
  {
    std::cerr << "err\n";
    if (type == '2')
    {
      std::free(mtx);
    }
    return 2;
  }
  in.close();

  std::ofstream ou(argv[3]);
  if (!ou.is_open())
  {
    std::cerr << "Cannot open output file\n";
    if (type == '2')
    {
      std::free(mtx);
    }
    return 2;
  }

  petrov::fll_inc_way(ou, mtx, n);
  petrov::cnt_nzr_dig(ou, mtx, n);

  if (type == '2')
  {
    std::free(mtx);
  }

  return 0;
}
