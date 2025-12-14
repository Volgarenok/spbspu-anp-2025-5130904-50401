#include <iostream>
#include <fstream>

namespace tarasenko
{
  std::istream & input(std::istream & in, int * arr, size_t n, size_t m, size_t & k)
  {
    for (size_t i = 0; i < n * m; ++i)
    {
      in >> arr[i];
      if (!in)
      {
        return in;
      }
      k += 1;
    }
    return in;
  }

  size_t cnt_loc_extremum(int const * arr, int type, size_t n, size_t m)
  {
    if (n * m == 0)
    {
      return 0;
    }
    size_t count = 0;
    for (size_t i = 1; i < n - 1; ++i)
    {
      for (size_t k = 1; k < m - 1; ++k)
      {
        bool is_extremum = true;
        const int num = arr[i * m + k];
        for (int near_i = -1; near_i < 2; ++near_i)
        {
          for (int near_k = -1; near_k < 2; ++near_k)
          {
            if (!(near_i == 0 && near_k == 0))
            {
              const int near_num = arr[(i + near_i) * m + (k + near_k)];
              if ((type && num <= near_num) || (!type && num >= near_num))
              {
                is_extremum = false;
              }
            }
          }
        }
        count += (is_extremum ? 1 : 0);
      }
    }
    return count;
  }

  size_t cnt_loc_max(int const * arr, size_t n, size_t m)
  {
    return cnt_loc_extremum(arr, 1, n, m);
  }

  size_t cnt_loc_min(int const * arr, size_t n, size_t m)
  {
    return cnt_loc_extremum(arr, 0, n, m);
  }
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
  const char * first_arg = argv[1];
  if ((first_arg[0] != '1' && first_arg[0] != '2') || first_arg[1] != '\0')
  {
    std::cerr << "First parameter is out of range\n";
    return 1;
  }

  std::ifstream input(argv[2]);
  size_t rows = 0, cols = 0;
  input >> rows >> cols;
  if (!input)
  {
    std::cerr << "Incorrect file" << '\n';
    return 2;
  }
  if (rows == 0 || cols == 0)
  {
    std::ofstream output(argv[3]);
    output << 0 << '\n';
    output << 0 << '\n';
    return 0;
  }

  int fixed_arr[10000] = {};
  int * arr = nullptr;
  bool is_dynamic = (*argv[1] == '2') ? 1 : 0;
  if (!is_dynamic)
  {
    arr = fixed_arr;
  }
  else
  {
    arr = reinterpret_cast< int * >(malloc(sizeof(int) * rows * cols));
    if (!arr)
    {
      std::cerr << "failed to allocate memory" << '\n';
      return 1;
    }
  }
  size_t k = 0;
  tarasenko::input(input, arr, rows, cols, k);
  if (!input)
  {
    std::cerr << "Managed to read " << k << " numbers from file" << '\n';
    if (is_dynamic)
    {
      free(arr);
    }
    return 2;
  }
  input.close();
  size_t max = tarasenko::cnt_loc_max(arr, rows, cols);
  size_t min = tarasenko::cnt_loc_min(arr, rows, cols);
  std::ofstream output(argv[3]);
  output << max << '\n';
  output << min << '\n';
  if (is_dynamic)
  {
    free(arr);
  }
}
