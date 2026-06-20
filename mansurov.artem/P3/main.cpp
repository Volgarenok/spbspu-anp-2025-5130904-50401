#include <iostream>
#include <fstream>

namespace mansurov
{
  size_t min(size_t a, size_t b);
  void transformMatrix(int* mtx, size_t m, size_t n);
  std::istream& fillMtrx(std::istream& input, int* mtx, size_t rows, size_t cols);
  int minSum(const int* mtrx, size_t rows, size_t cols);
  void outputToFile(std::ofstream& output, const int* mtrx, size_t rows, size_t cols, int minsum);
}


int main(int argc, char** argv)
{
  using namespace mansurov;
  if (argc < 4) {
    std::cerr << "Not enough arguments\n";
    return 1;
  } else if (argc > 4) {
    std::cerr << "Too mush argument\n";
    return 1;
  } else if (!isdigit(*argv[1])) {
    std::cerr << "First parameter not number\n";
    return 1;
  } else if (!((argv[1][0] == '1' || argv[1][0] == '2') && argv[1][1] == '\0')) {
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
    output << rows << " " << cols << " 0" << "\n";
    return 0;
  }

  int tempMatrix1[rows * cols] = {};
  int* tempMatrix2 = nullptr;

  if (argv[1][0] == '2')
  {
      tempMatrix2 = new int [rows * cols];
  }

  int* matrix = argv[1][0] == '1' ? tempMatrix1 : tempMatrix2;
  fillMtrx(input, matrix, rows, cols);

  if (!input){
    std::cerr << "input error\n";
    delete[] tempMatrix2;
    return 2;
  }

  int minsum = minSum(matrix, rows, cols);
  transformMatrix(matrix, rows, cols);
  outputToFile(output, matrix, rows, cols, minsum);

  if (argv[1][0] == '2')
  {
    delete [] matrix;
  }
}


void mansurov::outputToFile(std::ofstream& output, const int* mtrx, size_t rows, size_t cols, int minsum)
{
  for (size_t i = 0; i < rows * cols; ++i){
    output << mtrx[i] << " ";
  }
  output << minsum << "\n";
}

std::istream&  mansurov::fillMtrx(std::istream& input, int* mtx, size_t rows, size_t cols)
{
  for (size_t i = 0; i < (rows * cols); ++i)
  {
    input >> mtx[i];
    if (!input){
      return input;
    }
  }
  return input;
}

void mansurov::transformMatrix(int* mtx, size_t n, size_t m)
{
  if (m == 0 || n == 0) {
    mtx = mtx;
  }
  else{
    for (size_t i = 0; i < m * n; i++) {
      size_t row = i / n;
      size_t col = i % n;
      size_t distTop = row;
      size_t distBottom = n - 1 - row;
      size_t distLeft = col;
      size_t distRight = m - 1 - col;
      size_t layer = std::min(std::min(distTop, distBottom), std::min(distLeft, distRight));
      mtx[i] += (layer + 1);
    }
  }
}


int mansurov::minSum(const int* mtrx, size_t rows, size_t cols)
{
  if (rows == 0 || cols == 0){
    return 0;
  }
  int minsum = mtrx[0];
  int tmpsum = 0;
  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 0; j < cols; ++j) {
      tmpsum = mtrx[i * rows + j];
      if (i > 0 && j < cols - 1) {
        tmpsum += mtrx[(i - 1) * rows + j + 1];
      }
      if (j > 0 && i < rows - 1) {
        tmpsum += mtrx[(i + 1) * rows + j - 1];
      }
      minsum = std::min(minsum, tmpsum);
    }
  }
  return minsum;
}
