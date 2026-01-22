#include <iostream>
#include <cstddef>
#include <iomanip>
#include <memory>
#include <cctype>

namespace sedov
{
  char * extend(char * a, size_t k, size_t d);
  char * getline(std::istream & in, size_t & s, size_t & st);
  size_t getDifLat(const char * a, size_t s);
  size_t getCountOfVowels(const char * a, size_t s);
  void getRmvVow(const char * a, size_t s, char * str);
}

int main()
{
  size_t size = 0, st = 0;
  char * str1 = sedov::getline(std::cin, size, st);
  if (str1 == nullptr)
  {
    if (st)
    {
      std::cerr << "Error, end of file\n";
      return 2;
    }
    std::cerr << "Bad alloc\n";
    return 1;
  }
  size_t res1 = sedov::getDifLat(str1, size);
  size_t countOfVowels = sedov::getCountOfVowels(str1, size);
  char * str2 = reinterpret_cast< char * >(malloc(sizeof(char) * (size - countOfVowels + 1)));
  if (str2 == nullptr)
  {
    std::cerr << "Bad alloc\n";
    free(str1);
    return 1;
  }
  sedov::getRmvVow(str1, size, str2);
  std::cout << res1 << "\n";
  std::cout << str2 << "\n";
  free(str1);
  free(str2);
  return 0;
}

char * sedov::extend(char * a, size_t k, size_t d)
{
  char * newArray = reinterpret_cast< char * >(malloc(sizeof(char) * d));
  if (newArray != nullptr)
  {
    for (size_t i = 0; i < k; ++i)
    {
      newArray[i] = a[i];
    }
  }
  return newArray;
}

char * sedov::getline(std::istream & in, size_t & s, size_t & st)
{
  char * str = reinterpret_cast< char * >(malloc(sizeof(char)));
  if (str == nullptr)
  {
    return str;
  }
  str[0] = '\0';
  s = 0;
  bool isSkipWs = in.flags() & std::ios_base::skipws;
  if (isSkipWs)
  {
    in >> std::noskipws;
  }
  char t = 0;
  while (in >> t && t != '\n')
  {
    char * str1 = extend(str, s, s + 2);
    if (str1 == nullptr)
    {
      if (isSkipWs)
      {
        in >> std::skipws;
      }
      return str1;
    }
    free(str);
    str = str1;
    str[s] = t;
    str[s + 1] = '\0';
    ++s;
  }
  if (in.eof())
  {
    st = 1;
    free(str);
    return nullptr;
  }
  if (isSkipWs)
  {
    in >> std::skipws;
  }
  return str;
}

size_t sedov::getDifLat(const char * a, size_t s)
{
  size_t arrOfAlpha[52] = {0};
  for (size_t i = 0; i < s; ++i)
  {
    char ind = a[i];
    if (ind >= 'a' && ind <= 'z')
    {
      arrOfAlpha[ind - 'a']++;
    }
    else if (ind >= 'A' && ind <= 'Z')
    {
      arrOfAlpha[ind - 'A' + 26]++;
    }
  }
  size_t count = 0;
  for (size_t i = 0; i < 52; ++i)
  {
    if (arrOfAlpha[i])
    {
      count++;
    }
  }
  return count;
}

size_t sedov::getCountOfVowels(const char * a, size_t s)
{
  size_t count = 0;
  for (size_t i = 0; i < s; ++i)
  {
    char ind = a[i];
    char lInd = std::tolower(ind);
    if (lInd == 'a' || lInd == 'e' || lInd == 'i' || lInd == 'o' || lInd == 'u' || lInd == 'y')
    {
      count++;
    }
  }
  return count;
}

void sedov::getRmvVow(const char * a, size_t s, char * str)
{
  size_t count = 0;
  for (size_t i = 0; i < s; ++i)
  {
    char ind = a[i];
    char lInd = std::tolower(ind);
    if (lInd != 'a' && lInd != 'e' && lInd != 'i' && lInd != 'o' && lInd != 'u' && lInd != 'y')
    {
      str[count] = a[i];
      ++count;
    }
  }
  str[count] = '\0';
}
