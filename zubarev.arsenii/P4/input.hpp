#ifndef INPUT_H
#define INPUT_H

#include <iostream>
namespace zubarev
{
  bool isSpace(char letter);
  char** getWords(std::istream& in, size_t& size, size_t& capacity, bool (*isSpace)(char ch));
}
#endif
