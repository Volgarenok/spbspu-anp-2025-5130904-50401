#include <iostream>
#include <memory>
#include <cstddef>
#include <fstream>
#include <locale>

namespace petrov
{
  int* make_mtx(std::ifstream& in, size_t r, size_t c, char t, int* statmtx);
  void fll_inc_way(std::ofstream& ou, const int* mtx, size_t r, size_t c);
  void cnt_nzr_dig(std::ofstream& ou, int* mtx, size_t r, size_t c);
  void write_output(std::ofstream& ou, size_t r, const int* mtx);
  void reform(size_t d, size_t r, int* mtx);
  void count_diagonal(size_t r, size_t& s, size_t c, const int* mtx);
  size_t fill_massive(size_t r, std::ifstream& in, int* mtx, size_t s);
}

size_t petrov::fill_massive(size_t r, std::ifstream& in, int* mtx, size_t s)
{
  for (size_t i = 0; i < r; ++i)
  {
    for (size_t j = 0; j < r; ++j)
    {
      if (in.eof())
      {
        return s;
      }
      in >> mtx[i * r + j];
      s++;
    }
  }
  return s;
}

int* petrov::make_mtx(std::ifstream& in, size_t r, size_t c, char t, int* statmtx)
{
  size_t w = r * c;
  r = std::min(r, c);
  if (t == '2')
  {
    int* mtx = reinterpret_cast<int*>(malloc(sizeof(int) * r * r));
    int q;
    if (r == 0)
    {
      free(mtx);
      throw std::runtime_error("err");
    }
    if (mtx == nullptr)
    {
      throw std::logic_error("err\n");
    }
    size_t s = 0;
    s = petrov::fill_massive(r, in, mtx, s);
    for (size_t i = r * r; i < w; ++i)
    {
      if (in.eof())
      {
        free(mtx);
        throw std::logic_error("err");
      }
      in >> q;
    }
    return mtx;
  } else {
    int q;
    if (r == 0)
    {
      throw std::runtime_error("err");
    }
    if (statmtx == nullptr)
    {
      throw std::logic_error("err\n");
    }
    size_t s = 0;
    s = petrov::fill_massive(r, in, statmtx, s);
    for (size_t i = r * r; i < w; ++i)
    {
      if (in.eof())
      {
        throw std::logic_error("err");
      }
      in >> q;
    }
    return &statmtx[0];
  }
}

void petrov::count_diagonal(size_t r, size_t& s, size_t c, const int* mtx)
{
  size_t n = std::min(r, c), q = 0, i = 0, j = n - 1;
  bool iszero = 1;
  while (q < n - 1)
  {
    while (i < n - 1)
    {
      if (mtx[i * n + j] == 0)
      {
        iszero = 0;
      }
      i++;
      j--;
    }
    q++, s += iszero, i = q, j = n - q - 1, iszero = 1;
  }
  i = n - 1, q = 0, j = 0, iszero = 1;
  while (q < n - 1)
  {
    while (j < n - 1)
    {
      if (mtx[i * n + j] == 0)
      {
        iszero = 0;
      }
      j++, i--;
    }
    q++, s += iszero, i = n - 1 - q, j = q, iszero = 1;
  }
}

void petrov::fll_inc_way(std::ofstream& ou, const int* mtx, size_t r, size_t c)
{
  size_t s = 0;
  petrov::count_diagonal(r, s, c, mtx);
  ou << s << "\n";
}

void petrov::write_output(std::ofstream& ou, size_t r, const int* mtx)
{
  ou << r << " " << r << " ";
  for (size_t i = 0; i < r; ++i)
  {
    for (size_t j = 0; j < r; ++j)
    {
      ou << mtx[i * r + j] << " ";
    }
  }
}

void petrov::reform(size_t d, size_t r, int* mtx)
{
  while (d < r + 1)
  {
    for (size_t i = 0; i < r; ++i)
    {
      for (size_t j = 0; j < r; ++j)
      {
        if (i >= d - 1 && i < r - d + 1 && j >= d - 1 && j < r - d + 1)
        {
          mtx[i * r + j]++;
        }
      }
    }
    d++;
  }
}

void petrov::cnt_nzr_dig(std::ofstream& ou, int* mtx, size_t r, size_t c)
{
  r = std::min(r, c);
  size_t d = 1;
  reform(d, r, mtx);
  write_output(ou, r, mtx);
}

int main(int argc, char** argv)
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
  if (!((argv[1][0] == '1' && argv[1][1] == '\0') || (argv[1][0] == '2' && argv[1][1] == '\0')))
  {
    std::cerr << "First parameter is out of range\n";
    return 1;
  }
  size_t rows = 0, cols = 0;
  std::ifstream in(argv[2]);
  in >> rows >> cols;
  if (in.fail())
  {
    std::cerr << "err\n";
    return 2;
  }
  int statmtx[10000];
  int* mtx = nullptr;
  try
  {
    mtx = petrov::make_mtx(in, rows, cols, argv[1][0], &statmtx[0]);
  }
  catch (const std::runtime_error&)
  {
    if (argv[1][0] == '2')
    {
      free(mtx);
    }
    return 0;
  }
  catch (...)
  {
    std::cerr << "err\n";
    return 2;
  }
  if (in.fail())
  {
    std::cerr << "err\n";
    return 2;
  }
  in.close();
  std::ofstream ou(argv[3]);
  petrov::fll_inc_way(ou, (argv[1][0] == '1' ? statmtx : mtx), rows, cols);
  petrov::cnt_nzr_dig(ou, (argv[1][0] == '1' ? statmtx : mtx), rows, cols);
  if (argv[1][0] == '2')
  {
    free(mtx);
  }
  return 0;
}
