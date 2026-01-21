#include <iostream>
#include <fstream>
#include <cstddef>
#include <cctype>

namespace petrov
{
  std::istream& fill(std::istream& input, int* mtx, size_t rows, size_t cols);
  int* copy(int* mtx, size_t rows, size_t cols);
  void lft_bot_cnt(std::ostream& output, int* mtx, size_t rows, size_t cols);
  void vert_step_for_task1(int* mtx, size_t top, size_t bottom, size_t right, size_t left, size_t& plus_step, bool move_down, size_t cols);
  void hor_step_for_task1(int* mtx, size_t top, size_t bottom, size_t right, size_t left, size_t& plus_step, bool move_right, size_t cols);
  void fll_inc_wav(std::ostream& output, int* mtx, size_t rows, size_t cols);
  void vert_step_for_task2(int* mtx, size_t col, size_t row_start, size_t row_end, size_t cols, size_t plus_step);
  void hor_step_for_task2(int* mtx, size_t row, size_t col_start, size_t col_end, size_t cols, size_t plus_step);
  void fill_output(std::ostream& output, int* mtx, size_t rows, size_t cols);
  int* create_matrix(std::istream& in, size_t rows, size_t cols);
}

int* petrov::create_matrix(std::istream& in, size_t rows, size_t cols)
{
  int* mtx = nullptr;
  try
  {
    mtx = new int[rows * cols]();
  }
  catch (const std::bad_alloc&)
  {
    return nullptr;
  }

  petrov::fill(in, mtx, rows, cols);
  if (!in)
  {
    std::cerr << "BAD input\n";
    delete[] mtx;
    return nullptr;
  }
  return mtx;
}

void petrov::fill_output(std::ostream& output, int* mtx, size_t rows, size_t cols)
{
  output << rows << " " << cols;
  for (size_t i = 0; i < rows * cols; ++i)
  {
    output << " " << mtx[i];
  }
  output << "\n";
}

int* petrov::copy(int* mtx, size_t rows, size_t cols)
{
  int* copy = new int[rows * cols]();
  for (size_t i = 0; i < (rows * cols); ++i)
  {
    copy[i] = mtx[i];
  }
  return copy;
}

std::istream& petrov::fill(std::istream& input, int* mtx, size_t rows, size_t cols)
{
  for(size_t i = 0; i < (rows * cols); ++i)
  {
    input >> mtx[i];
  }
  return input;
}

void petrov::vert_step_for_task1(int* mtx, size_t top, size_t bottom, size_t right, size_t left, size_t& plus_step, bool move_down, size_t cols)
{
  if (move_down)
  {
    for (size_t i = top; i <= bottom; ++i)
    {
      mtx[i * cols + left] += plus_step++;
    }
  }
  else
  {
    for (size_t i = bottom + 1; i-- > top;)
    {
      mtx[i * cols + right] += plus_step++;
    }
  }
}

void petrov::hor_step_for_task1(int* mtx, size_t top, size_t bottom, size_t right, size_t left, size_t& plus_step, bool move_right, size_t cols)
{
  if (move_right)
  {
    for (size_t i = left; i <= right; ++i)
    {
      mtx[bottom * cols + i] += plus_step++;
    }
  }
  else
  {
    for (size_t i = right + 1; i-- > left;)
    {
      mtx[top * cols + i] += plus_step++;
    }
  }
}

void petrov::lft_bot_cnt(std::ostream& output, int* mtx, size_t rows, size_t cols)
{
  size_t step = 1;
  size_t top = 0, bottom = rows - 1, left = 0, right = cols - 1;

  while (top <= bottom && left <= right)
  {
    hor_step_for_task1(mtx, top, bottom, right, left, step, true, cols);
    if (bottom-- == 0) break;

    vert_step_for_task1(mtx, top, bottom, right, left, step, false, cols);
    if (right-- == 0) break;

    if (top <= bottom)
      hor_step_for_task1(mtx, top++, bottom, right, left, step, false, cols);

    if (left <= right)
      vert_step_for_task1(mtx, top, bottom, right, left++, step, true, cols);
  }

  fill_output(output, mtx, rows, cols);
}

void petrov::vert_step_for_task2(int* mtx, size_t col, size_t row_start, size_t row_end, size_t cols, size_t plus_step)
{
  for (size_t r = row_start; r <= row_end; ++r)
  {
    mtx[r * cols + col] += static_cast<int>(plus_step);
  }
}

void petrov::hor_step_for_task2(int* mtx, size_t row, size_t col_start, size_t col_end, size_t cols, size_t plus_step)
{
  for (size_t i = col_start; i <= col_end; ++i)
  {
    mtx[row * cols + i] += static_cast<int>(plus_step);
  }
}

void petrov::fll_inc_wav(std::ostream& output, int* mtx, size_t rows, size_t cols)
{
  size_t step = 1;
  size_t top = 0, bottom = rows - 1, left = 0, right = cols - 1;

  while (top <= bottom && left <= right)
  {
    hor_step_for_task2(mtx, bottom--, left, right, cols, step);

    if (top <= bottom)
      vert_step_for_task2(mtx, right--, top, bottom, cols, step);

    if (top <= bottom)
      hor_step_for_task2(mtx, top++, left, right, cols, step);

    if (left <= right)
      vert_step_for_task2(mtx, left++, top, bottom, cols, step);

    ++step;
  }

  fill_output(output, mtx, rows, cols);
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
    std::cerr << "Too mush argument\n";
    return 1;
  }
  else if (!isdigit(*argv[1]))
  {
    std::cerr << "First parameter not number\n";
    return 1;
  }
  else if (!((argv[1][0] == '1' || argv[1][0] == '2') && argv[1][1] == '\0'))
  {
    std::cerr << "First parameter is out of range\n";
    return 1;
  }
  std::ifstream input(argv[2]);
  std::ofstream output(argv[3]);
  size_t rows = 0, cols = 0;
  input >> rows >> cols;
  if (!input)
  {
    std::cerr << "BAD input\n";
    return 2;
  }

  if (rows == 0 || cols == 0)
  {
    output << rows << " " << cols;
    return 0;
  }

  const size_t MAX_SIZE = 10000;
  int static_buf[MAX_SIZE];
  int* matrix1 = nullptr;

  bool allocated = (argv[1][0] == '1');

  if (allocated)
  {
    if (rows * cols > MAX_SIZE)
    {
      std::cerr << "matrix invalid\n";
      return 2;
    }

    matrix1 = static_buf;
    petrov::fill(input, matrix1, rows, cols);
  }
  else
  {
    matrix1 = petrov::create_matrix(input, rows, cols);
  }

  if (!matrix1)
  {
    std::cerr << "matrix invalid\n";
    return 2;
  }

  int* matrix2 = petrov::copy(matrix1, rows, cols);
  if (!matrix2)
  {
    if (!allocated) delete[] matrix1;
    std::cerr << "memory allocation failed\n";
    return 2;
  }

  try
  {
    petrov::lft_bot_cnt(output, matrix1, rows, cols);
    petrov::fll_inc_wav(output, matrix2, rows, cols);
  }
  catch (const std::exception& e)
  {
    if (!allocated) delete[] matrix1;
    delete[] matrix2;
    return 2;
  }

  if (!allocated) delete[] matrix1;
  delete[] matrix2;

  return 0;
}
