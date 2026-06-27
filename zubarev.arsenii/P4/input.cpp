#include "input.hpp"
#include "extend.hpp"
bool zubarev::isSpace(char letter)
{
  return letter == ' ';
}
char** zubarev::getWords(std::istream& in, size_t& size, size_t& capacity, bool (*isSpace)(char ch))
{
  char let = ' ';
  char** data = nullptr;

  bool is_skipws = in.flags() & std::ios_base::skipws;
  if (is_skipws) {
    in >> std::noskipws;
  }

  char* curData = nullptr;
  size_t curSize = 0;
  size_t curCapacity = 0;

  while (in >> let && let != '\n') {

    if (isSpace(let) && curSize > 0) {
      pushOneElAmort(&curData, curSize, curCapacity, '\0');
      pushOneWordAmort(&data, size, capacity, curData);
      curData = nullptr;
      curSize = 0;
      curCapacity = 0;
    } else if (!isSpace(let)) {
      pushOneElAmort(&curData, curSize, curCapacity, let);
    }
  }

  if (curSize > 0) {
    pushOneElAmort(&curData, curSize, curCapacity, '\0');
    pushOneWordAmort(&data, size, capacity, curData);
  }

  if (is_skipws) {
    in >> std::skipws;
  }

  return data;
}
