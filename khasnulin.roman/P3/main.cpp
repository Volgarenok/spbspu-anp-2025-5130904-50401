#include <fstream>
#include <iostream>

#include "matrix_actions.hpp"
#include "utils.hpp"

int main(int argc, char **argv)
{
  size_t mode = 0;
  int *currArr = nullptr;
  if (argc != 4)
  {
    const char *message = argc > 4 ? "Too many arguments\n" : "Not enough arguments\n";
    std::cerr << message;
    return 1;
  }
  try
  {
    mode = khasnulin::getFirstParameter(argv[1]);

    std::ifstream input(argv[2]);
    size_t n = 1, m = 1;

    int arr[10000] = {};

    input >> n >> m;
    currArr = mode == 1 ? arr : new int[n * m];

    size_t elems_count = 0;
    khasnulin::readMatrix(input, currArr, n, m, elems_count);

    if ((!input.eof() && input.fail()) || (elems_count != n * m))
    {
      if (mode == 2)
      {
        delete[] currArr;
      }
      std::cerr << "Error while reading input file data, can't read as matrix\n";
      return 2;
    }
    input.close();

    bool isLWR_TRI_MTX = khasnulin::lwrTriMtx(currArr, n, m);
    khasnulin::lftBotClk(currArr, n, m);

    std::ofstream output(argv[3]);

    khasnulin::printMatrix(output, currArr, n, m);
    output << std::boolalpha << isLWR_TRI_MTX;

    if (mode == 2)
    {
      delete[] currArr;
    }
  }
  catch (const std::bad_alloc &e)
  {
    std::cerr << "Error memory allocation\n";
    return 2;
  }
  catch (const std::runtime_error &e)
  {
    if (mode == 2)
    {
      delete[] currArr;
    }
    std::cerr << e.what() << "\n";
    return 1;
  }
  catch (...)
  {
    std::cerr << "Error during task execution, something went wrong\n";
    if (mode == 2)
    {
      delete[] currArr;
    }
    return 2;
  }
}
