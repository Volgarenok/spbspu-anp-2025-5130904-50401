#include <iostream>
#include <stdlib.h>
#include <cctype>

namespace kudaev
{
  size_t getLine(std::istream&, char*, size_t, size_t);
  size_t strLen(const char*);
  char* getStr(char*);
  size_t hasSame(const char*, const char*);
  void latRmv(const char*, char*, size_t);
}

int main()
{
  char* str1 = nullptr;
  const char* str2 = "Ilovecpp";
  const char* str3 = "abs213fsd";
  str1 = kudaev::getStr(str1);
  if (!str1)
  {
    std::cerr << "Failed to read input\n";
    if (str1)
    {
      free(str1);
    }
    return 1;
  }
  std::cout << kudaev::hasSame(str1, str2) << '\n';
  size_t buffer_size = kudaev::strLen(str3) + 1;
  char* buffer = static_cast< char* >(malloc(buffer_size));
  if (!buffer)
  {
    std::cerr << "Memory allocation failed\n";
    free(str1);
    return 1;
  }
  kudaev::latRmv(str3, buffer, buffer_size);
  std::cout << buffer << '\n';
  free(buffer);
  free(str1);
  return 0;
}

size_t kudaev::getLine(std::istream& in, char* str, size_t length, size_t capacity)
{
  in >> std::noskipws;
  char ch;
  while (in >> ch)
  {
    if (ch == '\n')
    {
      break;
    }
    str[length++] = ch;
    if (length >= capacity - 1)
    {
      return length;
    }
  }
  str[length] = '\0';
  return length;
}

size_t kudaev::strLen(const char* str)
{
  if (str == nullptr)
  {
    return 0;
  }
  size_t length = 0;
  while (str[length] != '\0')
  {
    length++;
  }
  return length;
}

char* kudaev::getStr(char* str)
{
  size_t capacity = 2, length = 0;
  try
  {
    str = static_cast< char* >(malloc(capacity * sizeof(char)));
    if (!str)
    {
       throw;
    }
    while (length < capacity - 1 || std::cin.eof())
    {
      length = getLine(std::cin, str, length, capacity);
      capacity *= 2;
      char* new_str = static_cast< char* >(malloc(capacity * sizeof(char)));
      if (!new_str)
      {
        free(str);
        throw;
      }
      for (size_t i = 0; i < length; ++i)
      {
        new_str[i] = str[i];
      }
      free(str);
      str = new_str;
    }
  }
  catch (...)
  {
    if (str)
    {
      free(str);
      str = nullptr;
    }
    return nullptr;
  }
  if (length == 0)
  {
    free(str);
    str = nullptr;
    return nullptr;
  }
  return str;
}

size_t kudaev::hasSame(const char* str1, const char* str2)
{
  if (str1 == nullptr || str2 == nullptr)
  {
    return 0;
  }
  size_t count = 0;
  size_t len1 = strLen(str1);
  size_t len2 = strLen(str2);
  for (size_t i = 0; i < len1; ++i)
  {
    for (size_t j = 0; j < len2; ++j)
    {
      if (str1[i] == str2[j])
      {
        count++;
      }
    }
  }
  return count;
}

void kudaev::latRmv(const char* src, char* dest, size_t dest_size)
{
  if (src == nullptr || dest == nullptr || dest_size == 0)
  {
    return;
  }
  size_t j = 0;
  for (size_t i = 0; src[i] != '\0' && j < dest_size - 1; ++i)
  {
    if (!std::isalpha(static_cast< unsigned char >(src[i])))
    {
      dest[j++] = src[i];
    }
  }
  dest[j] = '\0';
}
