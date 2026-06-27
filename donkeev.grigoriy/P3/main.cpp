#include <iostream>
#include <fstream>

namespace donkeev
{
  std::istream& reading(std::istream& input, int& target);
  void outputToFile(std::ostream& output, const int* matrix, size_t rows, size_t cols, bool answer);
  size_t readingMatrix(std::istream& input, int* matrix, size_t rows, size_t cols);
  bool isFinish(size_t lim_u, size_t lim_r, size_t lim_d, size_t lim_l);
  void reducingMatrixSpirally(int* new_matrix, size_t rows, size_t cols);
  void copyMtx(const int* matrix, size_t rows, size_t cols, int* matrix2);
  int* cutMatrix(const int* matrix, size_t rows, size_t cols);
  bool isMatrixTriangular(int* matrix, size_t& rows, size_t& cols);
}

std::istream& donkeev::reading(std::istream& input, int& target)
{
  return input >> target;
}
void donkeev::outputToFile(std::ostream& output, const int* matrix, const size_t rows, const size_t cols, const bool answer)
{
  for (size_t i = 0; i < rows * cols; ++i)
  {
    output << matrix[i] << ' ';
  }
  output << std::boolalpha << answer;
}
size_t donkeev::readingMatrix(std::istream& input, int* matrix, const size_t rows, const size_t cols)
{
  for (size_t i = 0; i < rows * cols; ++i)
  {
    donkeev::reading(input, matrix[i]);
    if (!input)
    {
      return 1;
    }
  }
  int try_value = 0;
  donkeev::reading(input, try_value);
  if (input || !input.eof())
  {
    return 2;
  }
  return 0;
}
bool donkeev::isFinish(const size_t lim_u, const size_t lim_r, const size_t lim_d, const size_t lim_l)
{
  bool temp = lim_u == lim_r;
  temp = temp && lim_u == lim_d;
  temp = temp && lim_u == lim_l;
  return temp;
}
void donkeev::reducingMatrixSpirally(int* const new_matrix, const size_t rows, const size_t cols) //добавил const
{
  size_t lastVisitedUp = 0;
  size_t lastVisitedDown = rows + 1;
  size_t lastVisitedRight = cols + 1;
  size_t lastVisitedLeft = 0;
  size_t position = (rows - 1) * cols;
  int minus_counter = 1;
  new_matrix[position] -= minus_counter;
  ++minus_counter;
  for (size_t i = 0; i < rows - 1; ++i)
  {
    position -= cols;
    new_matrix[position] -= minus_counter;
    ++minus_counter;
  }
  ++lastVisitedLeft;
  while (true)
  {
    for (size_t i = 0; i < lastVisitedRight - lastVisitedLeft - 1; ++i)
    {
      position += 1;
      new_matrix[position] -= minus_counter;
      ++minus_counter;
    }
    ++lastVisitedUp;
    if (lastVisitedDown - lastVisitedUp == 1)
    {
      return;
    }
    for (size_t i = 0; i < lastVisitedDown - lastVisitedUp - 1; ++i)
    {
      position += cols;
      new_matrix[position] -= minus_counter;
      ++minus_counter;
    }
    --lastVisitedRight;
    if (lastVisitedRight - lastVisitedLeft == 1)
    {
      return;
    }
    for (size_t i = 0; i < lastVisitedRight - lastVisitedLeft - 1; ++i)
    {
      position -= 1;
      new_matrix[position] -= minus_counter;
      ++minus_counter;
    }
    --lastVisitedDown;
    if (lastVisitedRight - lastVisitedLeft == 1)
    {
      return;
    }
    for (size_t i = 0; i < lastVisitedDown - lastVisitedUp - 1; ++i)
    {
      position -= cols;
      new_matrix[position] -= minus_counter;
      ++minus_counter;
    }
    ++lastVisitedLeft;
    if (lastVisitedRight - lastVisitedLeft == 1)
    {
      return;
    }
  }
}
void donkeev::copyMtx(const int* matrix, const size_t rows, const size_t cols, int* const matrix2)
{
  for (size_t i = 0; i < rows * cols; ++i)
  {
    matrix2[i] = matrix [i];
  }
}
int* donkeev::cutMatrix(const int* matrix, size_t rows, size_t cols)
{
  size_t minimum = rows < cols ? rows : cols;
  rows = minimum;
  cols = minimum;
  int* cuttedMatrix = new int [minimum * minimum];
  for (size_t i = 0; i < minimum; ++i)
  {
    for (size_t j = 0; j < minimum; ++j)
    {
      cuttedMatrix[i * minimum + j] = matrix[i * cols + j];
    }
  }
  return cuttedMatrix;
}
bool donkeev::isMatrixTriangular(int* matrix, size_t& rows, size_t& cols)
{
  if (rows != cols)
  {
    int* temp = matrix;
    matrix = donkeev::cutMatrix(matrix, rows, cols);
    delete [] temp;
  }
  size_t skipping = 1;
  for (size_t i = 0; i < cols - 1; ++i)
  {
    size_t position = i + skipping * cols;
    while (position < rows * cols)
    {
      if (matrix[position] != 0)
      {
        return false;
      }
      position += cols;
    }
    ++skipping;
  }
  return true;
}
int main(int argc, char** argv)
{
  if (argc > 4)
  {
    std::cerr << "Too many arguments\n";
    return 1;
  }
  else if (argc < 4)
  {
    std::cerr << "Lack of arguments\n";
    return 1;
  }
  size_t i = 0;
  while (argv[1][i] != '\0')
  {
    if (argv[1][i] < '0' || argv[1][i] > '9')
    {
      std::cerr << "First argument is not a number\n";
      return 1;
    }
    ++i;
  }
  if (argv[1][1] != '\0')
  {
    std::cerr << "First argument is out of range\n";
    return 1;
  }
  if (argv[1][0] != '1' && argv[1][0] != '2')
  {
    std::cerr << "First argument is out of range\n";
    return 1;
  }
  std::ifstream input(argv[2]);
  if (!input)
  {
    std::cout << "File error\n";
    return 2;
  }
  size_t rows = 0;
  input >> rows;
  if (!input)
  {
    std::cerr << "Input error\n";
    return 2;
  }
  size_t cols = 0;
  input >> cols;
  if (!input)
  {
    std::cerr << "Input error\n";
    return 2;
  }
  std::ofstream output(argv[3]);
  if (rows == 0 && cols == 0)
  {
    output << rows << ' ' << cols << ' ' << "false";
    return 0;
  }
  int tempMatrix1[10000] = {};
  int* tempMatrix2 = nullptr;
  if (argv[1][0] == '2')
  {
    try
    {
      tempMatrix2 = new int [rows * cols];
    }
    catch (const std::bad_alloc& e)
    {
      std::cerr << e.what() << '\n';
      return 2;
    }
  }
  int* matrix = argv[1][0] == '1' ? tempMatrix1 : tempMatrix2;
  size_t checkingMatrixReading = donkeev::readingMatrix(input, matrix, rows, cols);
  if (checkingMatrixReading == 1)
  {
    std::cerr << "Input error\n";
    delete [] tempMatrix2;
    return 2;
  }
  else if (checkingMatrixReading == 2)
  {
    std::cerr << "Too much arguments\n";
    delete [] tempMatrix2;
    return 2;
  }
  bool lwrTriMtx = donkeev::isMatrixTriangular(matrix, rows, cols);
  donkeev::reducingMatrixSpirally(matrix, rows, cols);
  donkeev::outputToFile(output, matrix, rows, cols, lwrTriMtx);
  if (argv[1][0] == '2')
  {
    delete [] matrix;
  }
}
