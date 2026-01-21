#include <cmath>
#include <iostream>
#include <fstream>
#include <limits>

namespace kudaev
{
  std::ifstream& inputMtx(std::ifstream&, int*, size_t, size_t);
  void lftBotClk(int*, size_t, size_t);
  int bldSmtMtr(std::ostream&, int*, size_t, size_t);
  void outputMtx(std::ostream&, const int*, size_t, size_t);
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
  if (!std::isdigit(argv[1][0]) || argv[1][0] == '\0')
  {
    std::cerr << "First parameter is not a number\n";
    return 1;
  }
  int choice = std::atoi(argv[1]);
  std::ifstream input(argv[2]);
  std::ofstream output(argv[3]);
  if (!input.is_open())
  {
    std::cerr << "Cannot open input file\n";
    return 2;
  }
  if (!output.is_open())
  {
    std::cerr << "Cannot open output file\n";
    return 2;
  }
  int* target = nullptr;
  int a[10000] = {};
  size_t m, n;
  if (!(input >> m >> n))
  {
    std::cerr << "Error reading a file\n";
    return 2;
  }
  if (m == 0 || n == 0)
  {
    output << m << ' ' << n << '\n';
    return 0;
  }
  else
  {
    switch (choice)
    {
    case 1:
    {
      if (m * n <= 10000)
      {
        target = a;
      }
      else
      {
        std::cerr << "Too many elements for static array\n";
        return 2;
      }
      break;
    }
    case 2:
    {
      try
      {
        target = new int[m * n];
      }
      catch (const std::exception& ex)
      {
        std::cerr << ex.what() << '\n';
        return 2;
      }
      break;
    }
    default:
    {
      std::cerr << "First parameter is out of range\n";
      return 1;
    }
    }
  }
  try
  {
    if (!kudaev::inputMtx(input, target, m, n))
    {
      throw std::runtime_error("Can't read a file properly");
    }
    kudaev::lftBotClk(target, m, n);
    kudaev::outputMtx(output, target, m, n);
    int res = kudaev::bldSmtMtr(output, target, m, n);
    if (res == 1)
    {
      throw std::runtime_error("Memory allocation failed in bldSmtMtr");
    }
  }
  catch (const std::exception& ex)
  {
    if (choice == 2)
    {
      delete[] target;
    }
    std::cerr << ex.what() << '\n';
    return 2;
  }
  if (choice == 2 && target != nullptr)
  {
    delete[] target;
  }
}

std::ifstream& kudaev::inputMtx(std::ifstream& input, int* a, size_t m, size_t n)
{
  for (size_t i = 0; i < m * n; ++i)
  {
    input >> a[i];
  }
  return input;
}

void kudaev::lftBotClk(int* a, size_t m, size_t n)
{
  size_t pos = (m - 1) * n;
  size_t rows = m, cols = n;
  int k = 1;
  while (rows > 0 && cols > 0)
  {
    for (size_t i = 0; i < rows; i++)
    {
      a[pos] -= k++;
      if (i < rows - 1)
      {
        pos -= n;
      }
    }
    if (--cols == 0)
    {
      break;
    }
    pos++;
    for (size_t i = 0; i < cols; i++)
    {
      a[pos] -= k++;
      if (i < cols - 1)
      {
        pos++;
      }
    }
    if (--rows == 0)
    {
      break;
    }
    pos += n;
    for (size_t i = 0; i < rows; i++)
    {
      a[pos] -= k++;
      if (i < rows - 1)
      {
        pos += n;
      }
    }
    if (--cols == 0)
    {
      break;
    }
    pos--;
    for (size_t i = 0; i < cols; i++)
    {
      a[pos] -= k++;
      if (i < cols - 1)
      {
        pos--;
      }
    }
    if (--rows == 0)
    {
      break;
    }
    pos -= n;
  }
}

void kudaev::outputMtx(std::ostream& out, const int* a, size_t m, size_t n)
{
  out << m << ' ' << n << ' ';
  for (size_t i = 0; i < m * n; ++i)
  {
    if (i == m * n - 1)
    {
      out << a[i];
      break;
    }
    out << a[i] << ' ';
  }
  out << '\n';
}

int kudaev::bldSmtMtr(std::ostream& out, int* a, size_t m, size_t n)
{
  int* tmp = nullptr;
  float* res_mas = nullptr;
  try
  {
    tmp = new int[m * n];
    res_mas = new float[m * n];
    for (size_t i = 0; i < m * n; ++i)
    {
        tmp[i] = a[i];
    }
    for (size_t i = 0; i < m * n; ++i)
    {
      int sum = 0;
      int k = 0;
      int higherrow = i - n;
      size_t lowerrow = i + n;
      if (higherrow >= 0)
      {
        sum += tmp[higherrow];
        k++;
        if (higherrow % n != 0)
        {
          sum += tmp[higherrow - 1];
          k++;
        }
        if ((higherrow + 1) % n != 0)
        {
          sum += tmp[higherrow + 1];
          k++;
        }
      }
      if (lowerrow < m * n)
      {
        sum += tmp[lowerrow];
        k++;
        if (lowerrow % n != 0)
        {
          sum += tmp[lowerrow - 1];
          k++;
        }
        if ((lowerrow + 1) % n != 0)
        {
          sum += tmp[lowerrow + 1];
          k++;
        }
      }
      if (i % n != 0)
      {
        sum += tmp[i - 1];
        k++;
      }
      if ((i + 1) % n != 0)
      {
        sum += tmp[i + 1];
        k++;
      }
      if (k == 0)
      {
        res_mas[i] = 0.0f;
      }
      else
      {
        float res = sum * 1.0 / k;
        res_mas[i] = res;
      }
    }
    out << m << ' ' << n << ' ';
    for (size_t i = 0; i < m * n; ++i)
    {
      if (i == m * n - 1)
      {
        out << std::floor(10 * res_mas[i] + 0.5f) / 10;
        break;
      }
      out << std::floor(10 * res_mas[i] + 0.5f) / 10 << ' ';
    }
    delete[] tmp;
    delete[] res_mas;
  }
  catch (...)
  {
    delete[] tmp;
    delete[] res_mas;
    return 1;
  }
  return 0;
}
