#include <iostream>
#include <cstddef>
#include <fstream>
#include <istream>
#include <ostream>
#include <stdexcept>
#include <stdlib.h>

namespace mainfunction
{

  bool checkdynamickarr(const char* number);

  std::istream& readMatrix(std::istream& input, int* arr, size_t n, size_t m, size_t& elems_count);

  std::ostream& printMatrix(std::ostream& output, const int* a, size_t n, size_t m);

  size_t CntLocMax(int* arr, size_t n, size_t m);

  bool LwrRriMtx(int* arr, size_t n, size_t m);
}

int main(int argc, char** argv)
{
  if (argc != 4)
  {
    const char* error = argc > 4 ? "Too many arguments\n" : "Not enough arguments\n";
    std::cerr << error;
    return 1;
  }
  int* currArr = nullptr;
  try
  {
    bool mode = mainfunction::checkdynamickarr(argv[1]);
    std::ifstream input(argv[2]);
    size_t n = 1, m = 1;
    input >> n >> m; //m-строчки, n-столбцы
    
    int arr[10000] = {};

    currArr = mode == false ? arr : reinterpret_cast<int*>(malloc(sizeof(size_t) * n * m));
    if (!currArr)
    {
      std::cerr << "failed to allocate memory" << '\n';
      return 1;
    }

    size_t elems_count = 0;
    mainfunction::readMatrix(input, currArr, n, m, elems_count);

    if ((!input.eof() && input.fail()) || (elems_count != n * m))
    {
      if (mode == true)
      {
        free(currArr);
      }
      std::cerr << "Error while reading input file data, can't read as matrix\n";
      return 2;
    }
    input.close();

    std::cout << "CntLocMax= " << CntLocMax(currArr, n, m) << "\n";
    std::cout << std::boolalpha  << "LwrRriMtx= " << LwrRriMtx(currArr, n, m);

    if (mode == true)
    {
      free(arr);
    }
  }
  catch (...)
  {
    std::cerr << "Error during task execution, something went wrong\n";
    if (mode == true)
    {
      free(currArr);
    }
    return 2;
  }
  return 0;
}

bool mainfunction::checkdynarr(const char* number)
{
  size_t leng = 0;
  const char* ch = number;
  while (*ch)
  {
    leng++;
    ch++;
  }
  if (leng == 1)
  {
    if (number[0] == '1')
    {
      return false;
    }
    else if (number[0] == '2')
    {
      return true;
    }
}
throw std::runtime_error("Incorrect first parameter input\n");
}

std::istream& mainfunction::readMatrix(std::istream &input, int* arr, size_t n, size_t m, size_t& elems_count)
{
  elems_count = 0;
  while ((elems_count < n * m) && (input >> arr[elems_count]))
  {
    elems_count++;
  }

  return input;
}

std::ostream mainfunction::printMatrix(std::ostream& output, const int* a, size_t n, size_t m)
{
  if (n > 0 && m > 0)
  {
    for (size_t i = 0; i < n * m - 1; i++)
    {
      output << a[i] << " ";
    }
    output << a[m * n - 1] << "\n";
  }
  return output;
}

size_t mainfunction::CntLocMax(int* arr, size_t n, size_t m)
{
  size_t count = 0;
  
  if (n > 2 && m > 2)
  {
    for (size_t in = 1; i < n + 1; i++)
    {
      for (size_t im = 1; i < m + 1; i++)
      {
        if (im - 1 > 0 && im + 1 < m - 1 && in - 1 > 0 && in + 1 < n)
        {
          bool check = true;
          for (i1 = 1; (i1 < 3)&&(check==true); i1++)
          {
            for (i2 = 1; i1 < 3; i1++)
            {
              if (arr[i2 + i1 * n-1] > arr[in * n + im-1]) then check = false;
            }
            count += check == true ? 1 : 0;
          }
        }
      }
    }
  }
}

bool mainfunction::LwrRriMtx(int* arr, size_t n, size_t m)
{
  
  size_t minside = std::min(n, m);
  
  if (minside == 0)
  {
    minside=n;
  }

  bool checktri = true;

  for (size_t in = 1; i < n; i++)
  {
    for (size_t im = 1+in; i < n; i++)
      {
        if (arr[in * n + im - 1] != 0)
        {
          checktri = false
        }
      }
    } 
  return checktri;  
  }