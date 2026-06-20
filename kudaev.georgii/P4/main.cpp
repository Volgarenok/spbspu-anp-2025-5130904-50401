#include <iostream>
#include <cstdlib>
#include <cctype>

namespace kudaev
{
  size_t getLine(std::istream&, char*, size_t, size_t);
  char* getStr();
  size_t hasSame(const char*, const char*);
  char* latRmv(const char*);
}

int main()
{
  char* str1 = kudaev::getStr();
  const char* str2 = "Ilovecpp";
  const char* str3 = "abs213fsd";
  if (!str1)
  {
    std::cerr << "Failed to read input\n";
    return 1;
  }
  std::cout << kudaev::hasSame(str1, str2) << '\n';
  char* buffer = kudaev::latRmv(str3);
  if (!buffer)
  {
    std::cerr << "Memory allocation failed\n";
    free(str1);
    return 1;
  }
  std::cout << buffer << '\n';
  free(buffer);
  free(str1);
  return 0;
}

size_t kudaev::getLine(std::istream& in, char* str, size_t length, size_t capacity)
{
  bool needSkipws = (in.flags() & std::ios::skipws) != 0;
  in.unsetf(std::ios::skipws);
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
      if (needSkipws)
      {
        in.setf(std::ios::skipws);
      }
      return length;
    }
  }
  str[length] = '\0';
  if (needSkipws)
  {
    in.setf(std::ios::skipws);
  }
  return length;
}

char* kudaev::getStr()
{
  size_t capacity = 2, length = 0;
  char* str = static_cast< char* >(malloc(capacity * sizeof(char)));
  if (!str)
  {
    return nullptr;
  }
  while (!std::cin.eof())
  {
    length = getLine(std::cin, str, length, capacity);
    if (length < capacity - 1)
    {
      break;
    }
    capacity *= 2;
    char* new_str = static_cast< char* >(malloc(capacity * sizeof(char)));
    if (!new_str)
    {
      free(str);
      return nullptr;
    }
    for (size_t i = 0; i < length; ++i)
    {
      new_str[i] = str[i];
    }
    free(str);
    str = new_str;
  }
  if (length == 0)
  {
    free(str);
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
  for (size_t i = 0; str1[i] != '\0'; ++i)
  {
    for (size_t j = 0; str2[j] != '\0'; ++j)
    {
      if (str1[i] == str2[j])
      {
        count++;
      }
    }
  }
  return count;
}

char* kudaev::latRmv(const char* src)
{
  if (src == nullptr)
  {
    return nullptr;
  }
  size_t count = 0;
  for (size_t i = 0; src[i] != '\0'; ++i)
  {
    if (!std::isalpha(static_cast< unsigned char >(src[i])))
    {
      count++;
    }
  }
  char* dest = static_cast< char* >(malloc(count + 1));
  if (!dest)
  {
    return nullptr;
  }
  size_t j = 0;
  for (size_t i = 0; src[i] != '\0'; ++i)
  {
    if (!std::isalpha(static_cast< unsigned char >(src[i])))
    {
      dest[j++] = src[i];
    }
  }
  dest[j] = '\0';
  return dest;
}
