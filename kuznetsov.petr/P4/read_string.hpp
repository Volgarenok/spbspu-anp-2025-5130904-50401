#ifndef READSTRING_H
#define READSTRING_H
#include <cstddef>
#include <iosfwd>

namespace kuznetsov {
  char* getLine(std::istream& in, size_t& size);
}

#endif

