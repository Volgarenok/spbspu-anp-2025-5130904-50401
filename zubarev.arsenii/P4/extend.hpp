#ifndef EXTEND_H
#define EXTEND_H

#include <cstddef>
namespace zubarev
{

  void pushOneElAmort(char** arr, size_t& size, size_t& capacity, char value);
  void pushOneWordAmort(char*** arr, size_t& size, size_t& capacity, char* word);
}
#endif
