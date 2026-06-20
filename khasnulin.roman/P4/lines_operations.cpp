#include "lines_operations.hpp"
#include <algorithm>
#include <cctype>

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
