#include "resize.hpp"

void zharov::destroyArr(char ** arr, size_t len)
{
  for (size_t i = 0; i < len; ++i) {
    delete[] arr[i];
  }
  delete[] arr;
}

void zharov::extendStr(char ** str, size_t old_size, size_t new_size)
{
  char * new_str = new char[new_size];
  for (size_t i = 0; i < old_size; ++i) {
    new_str[i] = (*str)[i];
  }
  delete[] *str;
  *str = new_str;
}

void zharov::extendArr(char *** arr_str, size_t old_size, size_t new_size)
{
  char ** new_arr = new char * [new_size];
  for (size_t i = 0; i < old_size; ++i) {
    new_arr[i] = (*arr_str)[i];
  }
  delete[] *arr_str;
  *arr_str = new_arr;
}
