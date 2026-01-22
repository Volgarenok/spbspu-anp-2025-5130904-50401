#include <iostream>
#include <cstddef>
#include <iomanip>
#include <fstream>
#include <cctype>
#include <cstdlib>
#include <limits>
namespace vasyakin
{
  void cutLetters(const char* str, char* str1);
  void excludeCharsFromSecond(const char* str1, const char* str2, char* result);
  char* extend(char* a, size_t k, size_t k1);
  char* getline(std::istream& input, size_t& length);
  const size_t MAX = std::numeric_limits< size_t >::max();
}
char* vasyakin::extend(char* a, size_t k, size_t k1)
{
  char* new_arr = reinterpret_cast< char* >(malloc(sizeof(char) * k1));
  if (new_arr == nullptr)
  {
    free(a);
    return nullptr;
  }
  for (size_t i = 0; i < k; ++i)
  {
    new_arr[i] = a[i];
  }
  free(a);
  return new_arr;
}
char* vasyakin::getline(std::istream& input, size_t& length)
{
  char* str = reinterpret_cast< char* >(malloc(sizeof(char)));
  if (str == nullptr)
  {
    return nullptr;
  }
  str[0] = '\0';
  size_t len = 0;
  bool is_skipws = input.flags() & std::ios_base::skipws;
  if (is_skipws)
  {
    input >> std::noskipws;
  }
  char i = 0;
  while (input >> i && i != '\n')
  {
    if (len + 1 > vasyakin::MAX - 1)
    {
      free(str);
      return nullptr;
    }
    char* new_str = vasyakin::extend(str, len, len + 2);
    if (new_str == nullptr)
    {
      free(str);
      return nullptr;
    }
    str = new_str;
    str[len] = i;
    str[len + 1] = '\0';
    ++len;
  }
  if (is_skipws)
  {
    input >> std::skipws;
  }
  length = len;
  return str;
}
void vasyakin::cutLetters(const char* str, char* str1)
{
  size_t j = 0;
  for (size_t i = 0; str[i] != '\0'; ++i)
  {
    if (!std::isalpha(str[i]))
    {
      str1[j] = str[i];
      j++;
    }
  }
  str1[j] = '\0';
}
void vasyakin::excludeCharsFromSecond(const char* str1, const char* str2, char* result)
{
  size_t j = 0;
  for (size_t i = 0; str1[i] != '\0'; ++i)
  {
    bool flag = false;
    for (size_t k = 0; str2[k] != '\0'; ++k)
    {
      if (str1[i] == str2[k])
      {
        flag = true;
        break;
      }
    }
    if (!flag)
    {
      result[j] = str1[i];
      j++;
    }
  }
  result[j] = '\0';
}
int main()
{
  size_t str_len = 0;
  char* str = vasyakin::getline(std::cin, str_len);
  if (str == nullptr)
  {
    std::cerr << "Memory allocation failed or overflow error" << '\n';
    return 1;
  }
  if (std::cin.fail() && !std::cin.eof())
  {
    std::cerr << "Input stream in fail state" << '\n';
    free(str);
    return 1;
  }
  if (str[0] == '\0')
  {
    std::cerr << "Empty string" << '\n';
    free(str);
    return 1;
  }
  char* result1 = reinterpret_cast< char* >(malloc(sizeof(char) * (str_len + 1)));
  char* result2 = reinterpret_cast< char* >(malloc(sizeof(char) * (str_len + 1)));
  if (!result1 || !result2)
  {
    std::cerr << "Memory allocation failed" << '\n';
    free(str);
    free(result1);
    free(result2);
    return 1;
  }
  const char* str1 = "abc";
  vasyakin::cutLetters(str, result1);
  vasyakin::excludeCharsFromSecond(str, str1, result2);
  std::cout << result1 << '\n';
  std::cout << result2 << '\n';
  free(str);
  free(result1);
  free(result2);
  return 0;
}
