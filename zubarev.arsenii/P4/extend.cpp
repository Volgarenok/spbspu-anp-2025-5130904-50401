#include "extend.hpp"
#include <iostream>

void zubarev::pushOneElAmort(char** arr, size_t& size, size_t& capacity, char value)
{
  if (size + 1 >= capacity) {
    capacity = (capacity == 0) ? 2 : capacity * 2;
    char* newArr = nullptr;
    try {
      newArr = new char[capacity];
    } catch (const std::bad_alloc&) {
      std::cerr << "Memory allocation failed for square matrix\n";
      throw;
    }
    for (size_t i = 0; i < size; i++) {
      newArr[i] = (*arr)[i];
    }

    delete[] *arr;
    *arr = newArr;
  }
  (*arr)[size] = value;
  size++;
}
void zubarev::pushOneWordAmort(char*** arr, size_t& size, size_t& capacity, char* word)
{
  if (size + 1 >= capacity) {
    capacity = (capacity == 0) ? 2 : capacity * 2;
    char** newArr = nullptr;
    try {
      newArr = new char*[capacity];
    } catch (const std::bad_alloc&) {
      std::cerr << "Memory allocation failed for square matrix\n";
      throw;
    }
    for (size_t i = 0; i < size; i++) {
      newArr[i] = (*arr)[i];
    }

    delete[] *arr;
    *arr = newArr;
  }
  (*arr)[size] = word;
  size++;
}
