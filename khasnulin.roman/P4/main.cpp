#include <cctype>
#include <cstddef>
#include <ios>
#include <iostream>
#include <istream>

namespace khasnulin
{
  const size_t eng_alpabet_size = 26;

  bool getSkipWsState(std::istream &in);

  const size_t len_increment = 50;
  char *makeStr(size_t size);

  char *getResizedStr(const char *str, size_t oldSize, size_t newSize);

  char *getLine(std::istream &in, size_t &size);
  char *getLineWithWs(std::istream &in, size_t &size);

  bool isSymbIncluded(const char *str, size_t size, char symb);

  void fillEngAlphabet(char *str);

  char *shrSym(char *result, const char *origin_str, size_t size);
  char *uniTwo(char *result, const char *str1, size_t size1, const char *str2, size_t size2);
}

int main()
{
  size_t size;
  char *str = khasnulin::getLineWithWs(std::cin, size);
  if (!str)
  {
    std::cerr << "Failed to allocate dynamic memory for the input data.\n";
    return 1;
  }

  if (size)
  {
    const size_t new_str_size = khasnulin::eng_alpabet_size + 1;
    char new_str[new_str_size] = {};

    khasnulin::shrSym(new_str, str, size);
    std::cout << new_str << "\n";

    const char str2[] = "def_";
    const size_t size2 = 4;

    char *uni_str = khasnulin::makeStr(size + size2 + 1);
    if (!uni_str)
    {
      free(str);
      std::cerr << "Failed to allocate dynamic memory for the new string.\n";
      return 1;
    }

    khasnulin::uniTwo(uni_str, str, size, str2, size2);
    std::cout << uni_str << "\n";

    free(str);
    free(uni_str);
  }
  else
  {
    std::cerr << "Empty input error\n";
    free(str);
    return 1;
  }
}

bool khasnulin::getSkipWsState(std::istream &in)
{
  return in.flags() & std::ios_base::skipws;
}

char *khasnulin::makeStr(size_t size)
{
  return reinterpret_cast<char *>(malloc(sizeof(char) * size));
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

char *khasnulin::getLine(std::istream &in, size_t &size)
{
  char *str = makeStr(len_increment);
  if (!str)
  {
    size = 0;
    return nullptr;
  }

  size = len_increment;
  size_t i = 0;

  char ch;
  while ((in >> ch) && (ch != '\n'))
  {
    if (i == size)
    {
      char *newStr = getResizedStr(str, size, size + len_increment);
      if (!newStr)
      {
        size = 0;
        free(str);
        return nullptr;
      }
      free(str);
      str = newStr;
      size += len_increment;
    }
    str[i] = ch;
    i++;
  }
  char *newStr = getResizedStr(str, size, i + 1);
  if (!newStr)
  {
    free(str);
    size = 0;
    return nullptr;
  }
  free(str);
  str = newStr;
  size = i;
  str[i] = '\0';
  return str;
}

char *khasnulin::getLineWithWs(std::istream &in, size_t &size)
{
  bool skip_ws = getSkipWsState(in);
  if (skip_ws)
  {
    in >> std::noskipws;
  }

  char *str = getLine(in, size);

  if (skip_ws)
  {
    in >> std::skipws;
  }
  return str;
}

void khasnulin::fillEngAlphabet(char *str)
{
  char startSymb = 'a';
  for (size_t i = 0; i < eng_alpabet_size; i++)
  {
    str[i] = startSymb;
    startSymb++;
  }
}

bool khasnulin::isSymbIncluded(const char *str, size_t size, char symb)
{
  for (size_t i = 0; i < size; i++)
  {
    if (std::tolower(str[i]) == std::tolower(symb))
    {
      return true;
    }
  }
  return false;
}

char *khasnulin::shrSym(char *result, const char *origin_str, size_t size)
{
  char eng_alhp[eng_alpabet_size + 1] = {};
  fillEngAlphabet(eng_alhp);
  eng_alhp[eng_alpabet_size] = '\0';
  size_t new_str_len = 0;
  for (size_t i = 0; i < eng_alpabet_size; i++)
  {
    if (!isSymbIncluded(origin_str, size, eng_alhp[i]))
    {
      result[new_str_len] = eng_alhp[i];
      new_str_len++;
    }
  }
  result[new_str_len] = '\0';
  return result;
}

char *khasnulin::uniTwo(char *result, const char *str1, size_t size1, const char *str2, size_t size2)
{
  size_t minS = std::min(size1, size2);
  for (size_t i = 0; i < minS; i++)
  {
    result[i * 2] = str1[i];
    result[i * 2 + 1] = str2[i];
  }
  const char *max_str = minS == size1 ? str2 : str1;
  size_t maxS = minS == size1 ? size2 : size1;
  size_t res_i = minS * 2;
  for (size_t i = minS; i < maxS; i++)
  {
    result[res_i] = max_str[i];
    res_i++;
  }
  result[res_i] = '\0';

  return result;
}
