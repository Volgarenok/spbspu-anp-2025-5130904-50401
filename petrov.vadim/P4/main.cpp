#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <iomanip>

namespace petrov
{
  char* getLine(std::istream& input, size_t& size);
  char* extend(char* old_str, char a, size_t& size);
  char* checkStr(char* str1, size_t size1, char* str2, size_t size2, char* new_str, size_t& ns);
  char* uncSym(char* str1, size_t size1, char* str2, size_t size2, char* res);
  int seqSym(char* str, size_t size);
  char* removeDuplicates(char* str, size_t& size, char* res);
  char* resize(char* old_str, size_t old_size, size_t new_size);
}

char* petrov::resize(char* old_str, size_t old_size, size_t new_size)
{
  char* new_str = static_cast< char* >(malloc(new_size));
  if (!new_str)
  {
  return nullptr;
  }
  for (size_t i = 0; i < old_size; ++i)
  {
    new_str[i] = old_str[i];
  }
  free(old_str);
  return new_str;
}

char* petrov::removeDuplicates(char* str, size_t& size, char* result)
{
  if (!str)
  {
    return nullptr;
  }

  bool seen[256] = {false};
  size_t rsize = 0;
  result[0] = '\0';

  for (size_t i = 0; i <= size; ++i)
  {
    unsigned char c = str[i];
    if (!seen[c])
    {
      seen[c] = true;
      char* temp = extend(result, c, rsize);
      if (!temp)
      {
        free(result);
        return nullptr;
      }
      result = temp;
    }
  }
  size = rsize;
  return result;
}

char* petrov::getLine(std::istream& input, size_t& size)
{
  bool is_skipws = input.flags() & std::ios_base::skipws;
  if (is_skipws) {
    input >> std::noskipws;
  }

  size_t str_size = (size > 0) ? size : 1, i = 0;
  char* str = reinterpret_cast< char* >(malloc(str_size));

  while (input)
  {
    if (i >= str_size - 1)
    {
      size_t new_size = str_size + 5;
      char* new_str = resize(str, i, new_size);
      if (!new_str)
      {
        free(str);
        return nullptr;
      }
      str = new_str;
      str_size = new_size;
    }
    char ch = 0;
    input >> ch;
    if (ch == '\n')
    {
      break;
    }
    str[i] = ch;
    ++i;
  }

  if (!input || i == 0)
  {
    std::cerr << "bad input\n";
    free(str);
    return nullptr;
  }
  str[i] = '\0';
  size = i;
  if (is_skipws) {
    input >> std::skipws;
  }
  return str;
}

char* petrov::extend(char* old_str, char a, size_t& size)
{
  char* new_str = static_cast< char* >(malloc(size + 2));
  if (!new_str)
  {
    std::cerr << "malloc failed\n";
    return nullptr;
  }

  if (old_str)
  {
    for(size_t i = 0; i < size; ++i)
    {
      new_str[i] = old_str[i];
    }
  }

  new_str[size] = a;
  new_str[size + 1] = '\0';

  ++size;
  free(old_str);
  return new_str;
}

char* petrov::checkStr(char* str1, size_t size1, char* str2, size_t size2, char* new_str, size_t& ns)
{
  if (!str1 || !str2)
  {
    return new_str;
  }

  for (size_t i = 0; i < size1; i++)
  {
    bool flag = true;
    for (size_t j = 0; j < size2; j++)
    {
      if (str1[i] == str2[j])
      {
        flag = false;
        break;
      }
    }
    if (flag)
    {
      new_str = extend(new_str, str1[i], ns);
    }
  }
  return new_str;
}

char* petrov::uncSym(char* str1, size_t size1, char* str2, size_t size2, char* res)
{
  char* new_str = static_cast< char* >(malloc(1));
  size_t ns = 0;
  new_str[0] = '\0';

  new_str = checkStr(str1, size1, str2, size2, new_str, ns);
  new_str = checkStr(str2, size2, str1, size1, new_str, ns);

  char* result = removeDuplicates(new_str, ns, res);
  free(new_str);
  return result;
}

int petrov::seqSym(char* str, size_t size)
{
  if (size < 2)
  {
    return 0;
  }
  for (size_t i = 0; i < size - 1; ++i)
  {
    if (str[i] == str[i + 1])
    {
      return 1;
    }
  }
  return 0;
}

int main()
{
  size_t len1 = 1;
  char* str1 = petrov::getLine(std::cin, len1);
  if (!str1)
  {
    return 1;
  }
  char string[] = "abcd135790";
  size_t len2 = 10;
  char* str2 = string;

  char* task1 = static_cast< char* >(malloc(1));
  task1 = petrov::uncSym(str1, len1, str2, len2, task1);
  if (!task1)
  {
    free(str1);
    return 1;
  }
  size_t task2 = petrov::seqSym(str1, len1);

  std::cout << task1 << "\n";
  std::cout << task2 << "\n";

  free(str1);
  free(task1);
  return 0;
}
