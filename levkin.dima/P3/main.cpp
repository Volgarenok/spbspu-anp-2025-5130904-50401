#include <cstddef>
#include <fstream>
#include <iostream>
#include <istream>
#include <ostream>
#include <stdexcept>

namespace levkin
{
  int * copy(const int *, size_t);
  std::istream &read_matrix(std::istream &, int *, size_t, size_t, size_t &);
  std::ostream &print_matrix(std::ostream &output, const int *, size_t , size_t );
  int *lft_bot_ctn(int const *, size_t, size_t);
  size_t num_col_lsr(int const *, size_t, size_t);
}

int main(int argc, char **argv)
{
  size_t mode = 0;
  int *deletion_pointer = nullptr;
  int *arr = nullptr;
  if (argc != 4)
  {
    const char *err = argc > 4 ? "Too many arguments" : "Not enough arguments";
    std::cerr << err << "\n";
    return 1;
  }
  try
  {
    char * mode_str = argv[1];
    if (mode_str[0] == '1') {
        mode = 1;
    } else if (mode_str[0] == '2') {
        mode = 2;
    } else {
        throw std::runtime_error("Wierd mode");
    }

    std::ifstream input(argv[2]);
    size_t cols = 1, rows = 1;

    int static_arr[10000] = {};

    input >> cols >> rows;
    if (mode == 1) {
      arr = static_arr;
    } else {
      arr = new int[cols * rows];
      deletion_pointer = arr;
    }

    size_t elems_count = 0;
    levkin::read_matrix(input, arr, cols, rows, elems_count);

    if ((!input.eof() && input.fail()) || (elems_count != cols * rows))
    {
      delete[] deletion_pointer;
      std::cerr << "Wierd matrix file\n";
      return 2;
    }
    input.close();

    int *result = levkin::lft_bot_ctn(arr, rows, cols);
    size_t best_col = levkin::num_col_lsr(arr, rows, cols);

    std::ofstream output(argv[3]);

    levkin::print_matrix(output, result, cols, rows);
    output << best_col;
    delete[] deletion_pointer;
    delete[] result;
  }
  catch (const std::bad_alloc &e)
  {
    delete[] deletion_pointer;
    std::cerr << "Error memory allocation\n";
    return 2;
  }
  catch (const std::runtime_error &e)
  {
    delete[] deletion_pointer;
    std::cerr << e.what() << "\n";
    return 1;
  }
  catch (...)
  {
    delete[] deletion_pointer;
    std::cerr << "Error during task execution, something went wrong\n";
    return 2;
  }
}

int * levkin::copy(const int * arr, size_t sz)
{
    int * nw = new int [sz];
    for (size_t i = 0; i < sz; ++i)
    {
        nw[i] = arr[i];
    }
    return nw;
}


using is_t = std::istream;
is_t &levkin::read_matrix(is_t &input, int *arr, size_t cols, size_t rows, size_t &elems_count)
{
  elems_count = 0;
  while ((elems_count < cols * rows) && (input >> arr[elems_count]))
  {
    elems_count++;
  }

  return input;
}

using os_t = std::ostream;
os_t &levkin::print_matrix(os_t &output, const int *a, size_t cols, size_t rows)
{
  output << cols << " " << rows << " ";
  if (cols > 0 && cols > 0)
  {
    for (size_t i = 0; i < cols * rows - 1; i++)
    {
      output << a[i] << " ";
    }
    output << a[rows * cols - 1];
  }
  output << "\n";
  return output;
}


int *levkin::lft_bot_ctn(int const *buffer, size_t rows, size_t cols)
{
  int *arr = levkin::copy(buffer, rows*cols);
  size_t border_padding[4] = {0, 0, 0, 1};
  size_t x = 0;
  size_t y = rows - 1;
  size_t going_mode = 0;
  size_t i = 1;
  while (i <= rows * cols) {
    if (i == rows * cols) {
      arr[cols * y + x] += i;
      break;
    }
    bool can_we_go_this_way = true;
    switch (going_mode) {
    case 0:
      can_we_go_this_way = x + 1 < (cols - border_padding[0]);
      break;
    case 1:
      can_we_go_this_way = y > border_padding[1];
      break;
    case 2:
      can_we_go_this_way = x > border_padding[2];
      break;
    case 3:
      can_we_go_this_way = y + 1 < rows - border_padding[3];
      break;
    }
    if (!can_we_go_this_way) {
      switch (going_mode) {
      case 0:
        going_mode = 1;
        border_padding[0]++;
        break;
      case 1:
        going_mode = 2;
        border_padding[1]++;
        break;
      case 2:
        going_mode = 3;
        border_padding[2]++;
        break;
      case 3:
        going_mode = 0;
        border_padding[3]++;
        break;
      }
      continue;
    }
    arr[cols * y + x] += i;
    i++;
    switch (going_mode) {
    case 0:
      x += 1;
      break;
    case 1:
      y -= 1;
      break;
    case 2:
      x -= 1;
      break;
    case 3:
      y += 1;
      break;
    }
  }
  return arr;
}

size_t levkin::num_col_lsr(int const *buffer, size_t rows, size_t cols)
{
  if (!buffer || rows == 0 || cols == 0) {
    return 0;
  }
  size_t best_col = 0;
  size_t best_len = 0;
  for (size_t col = 0; col < cols; ++col) {
    size_t max_len = 1;
    size_t cur_len = 1;
    for (size_t row = 1; row < rows; ++row) {
      int prev = buffer[(row - 1) * cols + col];
      int curr = buffer[row * cols + col];
      if (curr == prev) {
        ++cur_len;
      } else {
        cur_len = 1;
      }
      max_len = std::max(max_len, cur_len);
    }
    if (max_len > best_len) {
      best_len = max_len;
      best_col = col;
    }
  }
  return best_col;
}
