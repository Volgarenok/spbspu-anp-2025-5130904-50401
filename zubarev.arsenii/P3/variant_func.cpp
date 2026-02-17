#include "variant_func.hpp"

int zubarev::getCouOfColNoIden(const int* matrix, size_t rows, size_t cols)
{
  size_t count = 0;
  bool equalFlag = false;

  for (size_t j = 0; j < cols; ++j) {
    for (size_t i = 0; i < rows - 1; ++i) {
      if (matrix[cols * i + j] == matrix[cols * (i + 1) + j]) {
        equalFlag = true;
        break;
      }
    }
    if (!equalFlag) {
      count++;
    } else {
      equalFlag = false;
    }
  }

  return count;
}

int zubarev::getMaxSumInDia(const int* matrix, size_t rows, size_t cols)
{
  int maxSum = getMinInt();
  int tempSum = 0;
  for (size_t s = 1; s <= (cols / 2); ++s) {
    for (size_t i = 0; i < rows - s; i++) {
      tempSum += matrix[i * cols + (i + s)];
    }
    if (tempSum > maxSum) {
      maxSum = tempSum;
    }
    tempSum = 0;
  }

  for (size_t s = 1; s <= (cols / 2); ++s) {
    for (size_t i = s; i < rows; i++) {
      tempSum += matrix[i * cols + (i - s)];
    }
    if (tempSum > maxSum) {
      maxSum = tempSum;
    }
    tempSum = 0;
  }

  return maxSum;
}
