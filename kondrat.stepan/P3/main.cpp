#include <cctype>
#include <cstdlib>
#include <cstddef>
#include <iostream>
#include <fstream>

namespace kondrat
{
  bool check_args(int argc, char ** argv, int & mode)
  {
    if (argc < 4)
    {
      std::cerr << "Not enough arguments\n";
      return false;
    }
    else if (argc > 4)
    {
      std::cerr << "Too many arguments\n";
      return false;
    }

    char * s = argv[1];
    if (!s || s[0] == '\0')
    {
      std::cerr << "First parameter is not a number\n";
      return false;
    }

    if (s[1] != '\0')
    {
      std::cerr << "First parameter is not a number\n";
      return false;
    }

    if (!std::isdigit(s[0]))
    {
      std::cerr << "First parameter is not a number\n";
      return false;
    }

    int val = s[0] - '0';

    if (val != 1 && val != 2)
    {
      std::cerr << "First parameter is out of range\n";
      return false;
    }

    mode = val;
    return true;
  }

  bool read_matrix_dimensions(std::ifstream & fin, size_t & rows, size_t & cols)
  {
    if (!(fin >> rows >> cols))
    {
      std::cerr << "Invalid matrix\n";
      return false;
    }

    return true;
  }

  std::ifstream & fill_matrix(std::ifstream & fin, int * m, size_t rows, size_t cols)
  {
    size_t total = rows * cols;
    for (size_t i = 0; i < total; i++)
    {
      fin >> m[i];
    }
    return fin;
  }

  size_t num_col_lsr(const int * m, size_t rows, size_t cols)
  {
    if (rows == 0 || cols == 0)
    {
      return 0;
    }

    size_t best_col = 0;
    size_t max_len = 0;

    for (size_t j = 0; j < cols; j++)
    {
      size_t curr_len = 1;
      size_t col_max = 1;

      for (size_t i = 1; i < rows; i++)
      {
        if (m[i * cols + j] == m[(i - 1) * cols + j])
        {
          curr_len++;
          if (curr_len > col_max)
          {
            col_max = curr_len;
          }
        }
        else
        {
          curr_len = 1;
        }
      }

      if (col_max > max_len)
      {
        max_len = col_max;
        best_col = j;
      }
    }

    return best_col + 1;
  }

  size_t cnt_loc_min(const int * m, size_t rows, size_t cols)
  {
    if (rows < 3 || cols < 3)
    {
      return 0;
    }

    size_t count = 0;

    for (size_t i = 1; i + 1 < rows; ++i)
    {
      for (size_t j = 1; j + 1 < cols; ++j)
      {
        int num = m[i * cols + j];
        bool isLocMin = true;

        for (size_t i_i = 0; i_i < 3; ++i_i)
        {
          for (size_t j_j = 0; j_j < 3; ++j_j)
          {
            if (i_i == 1 && j_j == 1)
            {
              continue;
            }

            size_t ni = i + i_i - 1;
            size_t nj = j + j_j - 1;

            if (!(num < m[ni * cols + nj]))
            {
              isLocMin = false;
            }
          }
        }

        if (isLocMin)
        {
          count++;
        }
      }
    }

    return count;
  }

  int process_matrix(std::ifstream & fin, std::ofstream & fout, int * m, size_t rows, size_t cols)
  {
    kondrat::fill_matrix(fin, m, rows, cols);
    if (!fin)
    {
      std::cerr << "Invalid matrix\n";
      return 2;
    }

    fin.close();

    size_t local_min_count = kondrat::cnt_loc_min(m, rows, cols);
    size_t best_col = kondrat::num_col_lsr(m, rows, cols);

    fout << local_min_count << ' ' << best_col << "\n";

    return 0;
  }
}

int main(int argc, char ** argv)
{
  int mode = 0;
  int result = 0;

  if (!kondrat::check_args(argc, argv, mode))
  {
    return 1;
  }

  std::ifstream fin(argv[2]);
  if (!fin)
  {
    std::cerr << "Cannot open input file\n";
    return 2;
  }

  size_t rows = 0, cols = 0;
  if (!kondrat::read_matrix_dimensions(fin, rows, cols))
  {
    return 2;
  }

  std::ofstream fout(argv[3]);
  if (!fout)
  {
    std::cerr << "Cannot open output file\n";
    return 2;
  }

  if (mode == 1)
  {
    int m_stack[10000];
    result = kondrat::process_matrix(fin, fout, m_stack, rows, cols);
  }
  else
  {
    int * m = reinterpret_cast< int * >(malloc(rows * cols * sizeof(int)));
    if (!m)
    {
      std::cerr << "Bad allocation memory\n";
      return 3;
    }

    result = kondrat::process_matrix(fin, fout, m, rows, cols);

    free(m);
  }

  return result;
}
