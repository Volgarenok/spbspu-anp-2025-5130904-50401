#include "resize.hpp"

void kuznetsov::extend(char** str, size_t oldSize, size_t newSize)
{
  char* extendedStr = new char[newSize];
  for (size_t i = 0; i < oldSize; ++i) {
    extendedStr[i] = (*str)[i];
  }
  for (size_t i = oldSize; i < newSize; ++i) {
    extendedStr[i] = 0;
  }
  delete[] *str;
  *str = extendedStr;
}

void kuznetsov::extend(char*** arr, size_t old)
{
  char** newArray = new char*[old + 1];
  for (size_t i = 0; i < old; ++i) {
    newArray[i] = (*arr)[i];
  }
  newArray[old] = nullptr;
  delete[] *arr;
  *arr = newArray;
}

void kuznetsov::extend(size_t** arr, size_t old)
{
  size_t* newArray = new size_t[old + 1];
  for (size_t i = 0; i < old; ++i) {
    newArray[i] = (*arr)[i];
  }
  delete[] *arr;
  *arr = newArray;
}

void kuznetsov::cut(char** str, size_t k)
{
  char* arr = new char[k];
  for (size_t i = 0; i < k; ++i) {
    arr[i] = (*str)[i];
  }
  delete[] *str;
  *str = arr;
}

