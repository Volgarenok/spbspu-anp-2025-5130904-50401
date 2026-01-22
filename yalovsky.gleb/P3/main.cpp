#include <iostream>
#include <fstream>
#include <cstdlib>

namespace yalovsky
{

  std::istream& read_matrix(std::istream& in, int* matrix, size_t rows, size_t cols)
  {
    for (size_t i = 0; i < rows * cols; i++)
    {
      in >> matrix[i];
    }
    return in;
  }

  void write_matrix(std::ostream& out, const int* matrix, size_t rows, size_t cols)
  {
    out << rows << " " << cols;
    for (size_t i = 0; i < rows * cols; i++)
    {
      out << " " << matrix[i];
    }
    out << "\n";
  }

  void copy_matrix(const int* source, int* dest, size_t rows, size_t cols)
  {
    for (size_t i = 0; i < rows * cols; i++)
    {
      dest[i] = source[i];
    }
  }

  void spiral_transform_lft_top_clk(int* matrix, size_t rows, size_t cols)
  {
    if (rows == 0 || cols == 0)
    {
      return;
    }

    int count = 1;
    int top = 0;
    int bottom = rows - 1;
    int left = 0;
    int right = cols - 1;

    while (top <= bottom && left <= right)
    {
      for (int i = left; i <= right; i++)
      {
        matrix[top * cols + i] -= count++;
      }
      top++;

      for (int j = top; j <= bottom; j++)
      {
        matrix[j * cols + right] -= count++;
      }
      right--;

      if (top <= bottom)
      {
        for (int i = right; i >= left; i--)
        {
          matrix[bottom * cols + i] -= count++;
        }
        bottom--;
      }

      if (left <= right)
      {
        for (int j = bottom; j >= top; j--)
        {
          matrix[j * cols + left] -= count++;
        }
        left++;
      }
    }
  }

  void spiral_transform_lft_bot_cnt(int* matrix, size_t rows, size_t cols)
  {
    if (rows == 0 || cols == 0)
    {
      return;
    }

    int count = 1;
    int top = 0;
    int bottom = rows - 1;
    int left = 0;
    int right = cols - 1;

    while (top <= bottom && left <= right)
    {
      for (int i = left; i <= right; i++)
      {
        matrix[bottom * cols + i] += count++;
      }
      bottom--;

      if (top <= bottom)
      {
        for (int j = bottom; j >= top; j--)
        {
          matrix[j * cols + right] += count++;
        }
      }
      right--;

      if (top <= bottom && left <= right)
      {
        for (int i = right; i >= left; i--)
        {
          matrix[top * cols + i] += count++;
        }
        top++;
      }

      if (left <= right)
      {
        for (int j = top; j <= bottom; j++)
        {
          matrix[j * cols + left] += count++;
        }
        left++;
      }
    }
  }

  void process_matrix(int* matrix, int* copy, size_t rows, size_t cols, std::ostream& output)
  {
    copy_matrix(matrix, copy, rows, cols);

    spiral_transform_lft_top_clk(matrix, rows, cols);
    output << "LFT-TOP-CLK result:\n";
    write_matrix(output, matrix, rows, cols);

    spiral_transform_lft_bot_cnt(copy, rows, cols);
    output << "LFT-BOT-CNT result:\n";
    write_matrix(output, copy, rows, cols);
  }

}

int main(int argc, char** argv)
{
  if (argc != 4)
  {
    std::cerr << (argc < 4 ? "Not enough arguments\n" : "Too many arguments\n");
    return 1;
  }

  if (!argv[1] || (argv[1][0] != '1' && argv[1][0] != '2') || argv[1][1] != '\0')
  {
    std::cerr << "First parameter is out of range\n";
    return 1;
  }

  int mode = argv[1][0] - '0';

  std::ifstream input(argv[2]);
  if (!input.is_open())
  {
    std::cerr << "Cannot open input file: " << argv[2] << "\n";
    return 2;
  }

  std::ofstream output(argv[3]);
  if (!output.is_open())
  {
    std::cerr << "Cannot open output file: " << argv[3] << "\n";
    return 2;
  }

  size_t rows = 0;
  size_t cols = 0;

  input >> rows >> cols;

  if (!input)
  {
    std::cerr << "Invalid input\n";
    return 2;
  }

  const size_t MAX_STATIC_SIZE = 10000;
  if (mode == 1 && rows * cols > MAX_STATIC_SIZE)
  {
    std::cerr << "Matrix too large for static alloc\n";
    return 2;
  }

  int* dynamic_matrix = nullptr;
  int* dynamic_copy = nullptr;

  if (mode == 1)
  {
    int fixed_matix[MAX_STATIC_SIZE];
    if (!yalovsky::read_matrix(input, fixed_matix, rows, cols))
    {
      std::cerr << "Invalid input - invalid matrix data\n";
      return 2;
    }

    int fixed_copy[MAX_STATIC_SIZE];
    yalovsky::process_matrix(fixed_matix, fixed_copy, rows, cols, output);
  }
  else
  {
    dynamic_matrix = static_cast< int* >(std::malloc(rows * cols * sizeof(int)));
    if (!dynamic_matrix)
    {
      std::cerr << "Memory alloc failed\n";
      return 2;
    }

    if (!yalovsky::read_matrix(input, dynamic_matrix, rows, cols))
    {
      std::cerr << "Invalid input - invalid matrix data\n";
      std::free(dynamic_matrix);
      return 2;
    }

    dynamic_copy = static_cast< int* >(std::malloc(rows * cols * sizeof(int)));
    if (!dynamic_copy)
    {
      std::cerr << "Memory alloc failed\n";
      std::free(dynamic_matrix);
      return 2;
    }

    yalovsky::process_matrix(dynamic_matrix, dynamic_copy, rows, cols, output);

    std::free(dynamic_copy);
    std::free(dynamic_matrix);
  }

  return 0;
}
