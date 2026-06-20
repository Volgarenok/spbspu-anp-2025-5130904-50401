#include "arrays_operations.hpp"
#include <algorithm>
#include <cstdlib>

char *khasnulin::makeStr(size_t size)
{
  return reinterpret_cast<char *>(malloc(sizeof(char) * size));
}

khasnulin::Line **khasnulin::makeLines(size_t size)
{
  return reinterpret_cast<Line **>(malloc(sizeof(struct Line *) * size));
}

khasnulin::Line *khasnulin::makeLine()
{
  return reinterpret_cast<Line *>(malloc(sizeof(struct Line)));
}

void khasnulin::clearLines(Line **lines, size_t size)
{
  for (size_t i = 0; i < size; i++)
  {
    free(lines[i]->str);
    free(lines[i]);
  }
  free(lines);
}

void khasnulin::expandLines(Line ***lines, size_t size, size_t newSize)
{
  Line **newLines = makeLines(newSize);
  if (newLines)
  {
    for (size_t i = 0; i < size; ++i)
    {
      newLines[i] = (*lines)[i];
    }
    free(*lines);
  }
  *lines = newLines;
}

char *khasnulin::getResizedStr(const char *str, size_t oldSize, size_t newSize)
{
  char *newStr = makeStr(newSize);
  if (!newStr)
  {
    return nullptr;
  }
  size_t minS = std::min(oldSize, newSize);
  for (size_t i = 0; i < minS; i++)
  {
    newStr[i] = str[i];
  }
  return newStr;
}

void khasnulin::ensureCapacity(char **str, size_t &size, size_t &capacity)
{
  if (size == capacity)
  {
    size_t new_capacity = capacity_coef * capacity;
    char *newStr = getResizedStr(*str, size, new_capacity);
    free(*str);
    if (!newStr)
    {
      capacity = 0;
      size = 0;
      *str = nullptr;
    }
    else
    {
      *str = newStr;
      capacity = new_capacity;
    }
  }
}
