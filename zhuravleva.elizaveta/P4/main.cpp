#include <iostream>
#include <cctype>
#include <cstdlib>
#include <iomanip>

namespace zhuravleva{
  void removeLatinLetters(const char* input, char* result)
  {
    size_t i = 0, j = 0;
    while (input[i] != '\0')
    {
      if (isalpha(input[i]))
      {
        i++;
        continue;
      }
      result[j] = input[i];
      j++;
      i++;
    }
    result[j] = '\0';
  }

  void excludeCommonSymbols(const char* str1, const char* str2, char* result)
  {
    size_t i = 0, j = 0;
    while (str1[i] != '\0')
    {
      int found = 0;
      for (size_t k = 0; str2[k] != '\0'; k++)
      {
        if (str1[i] == str2[k])
        {
          found = 1;
          break;
        }
      }
      if (!found)
      {
        result[j] = str1[i];
        j++;
      }
      i++;
    }
    result[j] = '\0';
  }

  size_t extend(char** buffer, size_t current_size, size_t new_size)
  {
    char* new_buffer = static_cast<char*>(malloc(sizeof(char) * new_size));
    if (new_buffer == nullptr)
    {
      return 1;
    }

    for (size_t i = 0; i < current_size; ++i)
    {
      new_buffer[i] = (*buffer)[i];
    }

    free(*buffer);
    *buffer = new_buffer;
    return 0;
  }

  size_t getline(std::istream& input, size_t& length, char** str)
  {
    size_t addSize = 64;
    size_t capacity = addSize;
    length = 0;
    *str = static_cast<char*>(std::malloc(sizeof(char) * capacity));

    if (*str == nullptr)
    {
      return 1;
    }
    bool is_skipws = input.flags() & std::ios_base::skipws;
    if (is_skipws)
    {
      input >> std::noskipws;
    }

    char ch;
    while (input >> ch && ch != '\n')
    {
      if (input.bad())
      {
        return 2;
      }
      if (length + 1 >= capacity)
      {
        size_t new_capacity = capacity + addSize;
        size_t result = extend(str, capacity, new_capacity);
        if (result != 0)
        {
          return result;
        }
        capacity = new_capacity;
      }
      (*str)[length] = ch;
      length++;
    }

    (*str)[length] = '\0';

    if (is_skipws)
    {
      input >> std::skipws;
    }
    return 0;
  }

  size_t stringLength(const char* str)
  {
    size_t len = 0;
    while (str[len] != '\0')
    {
      len++;
    }
    return len;
  }
}


int main()
{
  size_t lenOfFirst = 0;
  char* firstString = nullptr;
  size_t num1 = zhuravleva::getline(std::cin, lenOfFirst, &firstString);
  if (num1 != 0)
  {
    std::cerr << "Error: Reading input failed\n";
    if (firstString != nullptr)
    {
      std::free(firstString);
    }
    return 1;
  }
  if (zhuravleva::stringLength(firstString) == 0)
  {
    std::cerr << "Error: Empty string\n";
    std::free(firstString);
    return 1;
  }

  size_t lenOfSecond = 0;
  char* secondString = nullptr;
  size_t num2 = zhuravleva::getline(std::cin, lenOfSecond, &secondString);
  if (num2 != 0)
  {
    std::free(firstString);
    std::cerr << "Error: Reading input failed\n";
    if (secondString != nullptr)
    {
      std::free(secondString);
    }
    return 1;
  }
  if (zhuravleva::stringLength(secondString) == 0)
  {
    std::cerr << "Error: Empty string\n";
    std::free(firstString);
    std::free(secondString);
    return 1;
  }

  size_t max_len1 = zhuravleva::stringLength(firstString) + 1;
  size_t max_len2 = zhuravleva::stringLength(firstString) + 1;

  char* result1 = static_cast<char*>(std::malloc(sizeof(char) * max_len1));
  char* result2 = static_cast<char*>(std::malloc(sizeof(char) * max_len2));

  if (result1 == nullptr || result2 == nullptr)
  {
    std::cerr << "Error: Memory allocation failed for results\n";
    std::free(firstString);
    std::free(secondString);
    if (result1 != nullptr)
    {
      std::free(result1);
    }
    if (result2 != nullptr)
    {
      std::free(result2);
    }
    return 1;
  }

  zhuravleva::removeLatinLetters(firstString, result1);
  zhuravleva::excludeCommonSymbols(firstString, secondString, result2);

  std::cout << "Result №3 (remove Latin letters): " << result1 << "\n";
  std::cout << "Result №15 (exclude chars from second string): " << result2 << "\n";

  std::free(firstString);
  std::free(secondString);
  std::free(result1);
  std::free(result2);

  return 0;
}
