#include <iostream>

#include "arrays_operations.hpp"
#include "lines_operations.hpp"
#include "read_line.hpp"

int main()
{
  using namespace khasnulin;

  size_t size = 0;
  Line **lines = getWordsFromLine(std::cin, size, isSpace);
  if (!lines)
  {
    std::cerr << "Failed to allocate dynamic memory for the input data.\n";
    return 1;
  }

  if (lines[0]->size)
  {
    const size_t new_str_size = khasnulin::eng_alpabet_size + 1;
    char new_str[new_str_size] = {};

    for (size_t i = 0; i < size; ++i)
    {
      shrSym(new_str, lines[i]->str, lines[i]->size);
      std::cout << "[ SHR-SYM ] word: " << lines[i]->str << ", result: " << new_str << "\n";
    }

    const char str2[] = "def_";
    const size_t size2 = 4;
    char *uni_str = nullptr;

    for (size_t i = 0; i < size; ++i)
    {
      uni_str = makeStr(lines[i]->size + size2 + 1);
      if (!uni_str)
      {
        clearLines(lines, size);
        std::cerr << "Failed to allocate dynamic memory for the new string.\n";
        return 1;
      }

      uniTwo(uni_str, lines[i]->str, lines[i]->size, str2, size2);
      std::cout << "[ UNI-TWO ] string 1: " << lines[i]->str << ", string 2: " << str2
                << ", result: " << uni_str << "\n";
      free(uni_str);
    }

    clearLines(lines, size);
  }
  else
  {
    std::cerr << "Empty input error\n";
    clearLines(lines, size);
    return 1;
  }
}
