#include "read_words.hpp"
#include <iomanip>
#include "resize.hpp"

void deleting(char** arr, size_t k)
{
  for (size_t i = 0; i < k; ++i) {
    delete[] arr[i];
  }
  delete[] arr;
}

char** kuznetsov::getWords(std::istream& in, size_t& words, size_t** sizes, bool(*spliter)(char))
{
  size_t strCount = 0;
  char** strArray = nullptr;
  size_t* strLens = nullptr;
  bool isSkipws = in.flags() & std::ios::skipws;
  in >> std::noskipws;

  char* buff = nullptr;
  char t = '\0';
  try {
    while (t != '\n' && in ) {
      t = '\0';
      extend(&strArray, strCount);
      extend(&strLens, strCount);
      buff = new char[2];
      size_t strLen = 0;
      size_t blockSize = 1;
      while (!spliter(t) && in) {
        in >> t;
        buff[strLen++] = t;
        if (strLen == blockSize) {
          size_t newSize = blockSize +  blockSize / 2 + 1;
          extend(&buff, strLen, newSize + 1);
          blockSize = newSize;
        }
      }
      buff[strLen - 1] = '\0';
      cut(&buff, strLen);
      strArray[strCount] = buff;
      strLens[strCount] = strLen - 1;
      strCount++;
    }
  } catch (const std::bad_alloc&) {
    delete[] buff;
    delete[] strLens;
    deleting(strArray, strCount);
    throw;
  }

  if (isSkipws) {
    in >> std::skipws;
  }
  words = strCount;
  *sizes = strLens;
  return strArray;
}

