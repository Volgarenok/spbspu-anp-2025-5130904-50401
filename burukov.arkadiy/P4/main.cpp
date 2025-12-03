#include <iostream>
#include <cstddef>
#include <limits>
#include <new>

namespace burukov
{
  size_t stringLength(const char* str);
  char* getline(std::istream& input);
  void removeVowels(const char* source, char* result);
  void excludeFromFirst(const char* str1, const char* str2, char* result);

  const size_t MAX = std::numeric_limits< size_t >::max();
}

size_t burukov::stringLength(const char* str)
{
  size_t count = 0;
  while (str[count] != '\0')
  {
    ++count;
  }
  return count;
}

char* burukov::getline(std::istream& input)
{
  if (input.fail())
  {
    return nullptr;
  }

  size_t capacity = 16;
  char* str = new(std::nothrow) char[capacity];

  if (str == nullptr)
  {
    return nullptr;
  }

  size_t size = 0;
  char currentChar = 0;

  while (input.get(currentChar) && currentChar != '\n')
  {
    if (size + 1 >= capacity)
    {
      if (capacity > burukov::MAX / 2)
      {
        delete[] str;
        return nullptr;
      }

      size_t newCapacity = capacity * 2;
      char* newStr = new(std::nothrow) char[newCapacity];

      if (newStr == nullptr)
      {
        delete[] str;
        return nullptr;
      }

      for (size_t i = 0; i < size; ++i)
      {
        newStr[i] = str[i];
      }

      delete[] str;
      str = newStr;
      capacity = newCapacity;
    }

    str[size] = currentChar;
    ++size;
  }

  if (size + 1 >= capacity)
  {
    char* newStr = new(std::nothrow) char[size + 1];

    if (newStr == nullptr)
    {
      delete[] str;
      return nullptr;
    }

    for (size_t i = 0; i < size; ++i)
    {
      newStr[i] = str[i];
    }

    delete[] str;
    str = newStr;
  }

  str[size] = '\0';

  if (input.bad())
  {
    delete[] str;
    return nullptr;
  }

  return str;
}

void burukov::removeVowels(const char* source, char* result)
{
  size_t resultIndex = 0;

  for (size_t sourceIndex = 0; source[sourceIndex] != '\0'; ++sourceIndex)
  {
    char currentChar = source[sourceIndex];

    bool isVowel = false;
    if (currentChar == 'a' || currentChar == 'e' || currentChar == 'i' ||
        currentChar == 'o' || currentChar == 'u' || currentChar == 'y' ||
        currentChar == 'A' || currentChar == 'E' || currentChar == 'I' ||
        currentChar == 'O' || currentChar == 'U' || currentChar == 'Y')
    {
      isVowel = true;
    }

    if (!isVowel)
    {
      result[resultIndex] = currentChar;
      ++resultIndex;
    }
  }

  result[resultIndex] = '\0';
}

void burukov::excludeFromFirst(const char* str1, const char* str2, char* result)
{
  size_t resultIndex = 0;

  for (size_t i = 0; str1[i] != '\0'; ++i)
  {
    bool foundInSecond = false;

    for (size_t j = 0; str2[j] != '\0'; ++j)
    {
      char c1 = str1[i];
      char c2 = str2[j];

      char lowerC1 = c1;
      char lowerC2 = c2;

      if (c1 >= 'A' && c1 <= 'Z')
      {
        lowerC1 = c1 + ('a' - 'A');
      }

      if (c2 >= 'A' && c2 <= 'Z')
      {
        lowerC2 = c2 + ('a' - 'A');
      }

      if (lowerC1 == lowerC2)
      {
        foundInSecond = true;
        break;
      }
    }

    if (!foundInSecond)
    {
      result[resultIndex] = str1[i];
      ++resultIndex;
    }
  }

  result[resultIndex] = '\0';
}

int main()
{
  char* inputStr = burukov::getline(std::cin);

  if (inputStr == nullptr)
  {
    std::cerr << "Memory allocation failed or input error\n";
    return 1;
  }

  if (inputStr[0] == '\0')
  {
    std::cerr << "Empty string\n";
    delete[] inputStr;
    return 1;
  }

  size_t strLen = burukov::stringLength(inputStr);

  char* result1 = new(std::nothrow) char[strLen + 1];
  char* result2 = new(std::nothrow) char[strLen + 1];

  if (result1 == nullptr || result2 == nullptr)
  {
    std::cerr << "Memory allocation failed for result arrays\n";
    delete[] inputStr;
    delete[] result1;
    delete[] result2;
    return 1;
  }

  const char* secondStr = "abc";

  burukov::removeVowels(inputStr, result1);
  burukov::excludeFromFirst(inputStr, secondStr, result2);

  std::cout << result1 << '\n';
  std::cout << result2 << '\n';

  delete[] inputStr;
  delete[] result1;
  delete[] result2;

  return 0;
}
