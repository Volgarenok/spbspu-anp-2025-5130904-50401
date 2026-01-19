#ifndef READWORDS_H
#define READWORDS_H
#include <iosfwd>
#include <cstddef>

namespace kuznetsov {
  char** getWords(std::istream& in, size_t& words, size_t** sizes, bool(*c)(char));
}

#endif

