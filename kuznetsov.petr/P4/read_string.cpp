#include "read_string.hpp"
#include <iostream>
#include <iomanip>
#include "resize.hpp"

char* kuznetsov::getLine(std::istream& in, size_t& size)
{
  char* buff = new char[2] {};
  size_t blockSize = 1;
  size_t strLen = 0;
  bool isSkipws = in.flags() & std::ios::skipws;
  in >> std::noskipws;
  while (in >> buff[strLen++] && buff[strLen - 1] != '\n') {
    if (strLen == blockSize) {
      try {
        size_t newSize = blockSize +  blockSize / 2 + 1;
        extend(&buff, strLen, newSize + 1);
        blockSize = newSize;
      } catch (const std::bad_alloc&) {
        delete[] buff;
        throw;
      }
    }
  }
  strLen--;
  cut(&buff, strLen);
  size = strLen;
  buff[strLen] = '\0';
  if (isSkipws) {
    in >> std::skipws;
  }
  return buff;
}

