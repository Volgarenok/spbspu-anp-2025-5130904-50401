#include "read_line.hpp"
#include "arrays_operations.hpp"

#include <istream>

namespace
{
  bool getSkipWsState(std::istream &in)
  {
    return in.flags() & std::ios_base::skipws;
  }
}

bool khasnulin::isSpace(char ch)
{
  return ch == ' ';
}

char *khasnulin::getLine(std::istream &in, size_t &size, size_t &capacity, bool &eol, filter check)
{
  char *str = makeStr(start_length);
  if (!str)
  {
    capacity = 0;
    size = 0;
    return nullptr;
  }

  capacity = start_length;
  size = 0;
  char ch;
  while ((in >> ch) && !check(ch) && ch != '\n')
  {
    str[size] = ch;
    size++;
    ensureCapacity(&str, size, capacity);
    if (!str)
    {
      return nullptr;
    }
  }
  eol = (in.eof() || ch == '\n');
  str[size] = '\0';
  return str;
}

khasnulin::Line *khasnulin::buildLine(std::istream &in, bool &eol, filter check)
{
  size_t size;
  size_t capacity;
  char *str = getLine(in, size, capacity, eol, check);
  Line *line = makeLine();
  if (!str || !line)
  {
    free(line);
    free(str);
    return nullptr;
  }
  line->str = str;
  line->size = size;
  line->capacity = capacity;
  return line;
}

khasnulin::Line **khasnulin::getWordsFromLine(std::istream &in, size_t &size, filter check)
{
  bool skip_ws = getSkipWsState(in);
  if (skip_ws)
  {
    in >> std::noskipws;
  }

  Line **lines = nullptr;
  size_t lines_count = 0;

  bool eol = false;
  while (!eol)
  {
    Line *line = buildLine(in, eol, check);
    if (!line)
    {
      clearLines(lines, lines_count);
      return nullptr;
    }
    expandLines(&lines, lines_count, lines_count + 1);
    if (!lines)
    {
      free(line);
      clearLines(lines, lines_count);
      return nullptr;
    }
    lines[lines_count++] = line;
  }

  if (skip_ws)
  {
    in >> std::skipws;
  }
  size = lines_count;
  return lines;
}
