#include <iostream>
#include <cstddef>
#include <cctype>
#include <iomanip>

namespace studilova
{
  char* getLine();
  size_t stringLength(const char* str);
  int isVowel(char c);
  void excludeCharsFromSecond(const char* input, char* output, size_t output_size);
  void removeVowels(const char* input, char* output, size_t output_size);
}

char* studilova::getLine()
{
  const size_t first_capacity = 32;
  size_t capacity = first_capacity;
  size_t length = 0;

  char* buffer = nullptr;
  try {
    buffer = new char[capacity];
  } catch (...) {
    return nullptr;
  }

  bool is_skipws = std::cin.flags() & std::ios_base::skipws;
  if (is_skipws)
  {
    std::cin >> std::noskipws;
  }

  char ch;
  while (std::cin >> ch && ch != '\n')
  {
    if (length + 1 >= capacity)
    {
      size_t new_capacity = capacity * 2;
      char* new_buffer = nullptr;
      try {
        new_buffer = new char[new_capacity];
      } catch (...) {
        if (is_skipws)
        {
          std::cin >> std::skipws;
        }
        delete[] buffer;
        return nullptr;
      }

      for (size_t i = 0; i < length; ++i)
      {
        new_buffer[i] = buffer[i];
      }

      delete[] buffer;
      buffer = new_buffer;
      capacity = new_capacity;
    }

    buffer[length] = ch;
    length++;
  }

  if (is_skipws)
  {
    std::cin >> std::skipws;
  }

  if (length == 0)
  {
    if (std::cin.eof())
    {
      delete[] buffer;
      return nullptr;
    }
    else
    {
      buffer[0] = '\0';
      return buffer;
    }
  }

  buffer[length] = '\0';
  return buffer;
}

size_t studilova::stringLength(const char* str)
{
  size_t len = 0;
  for (size_t i = 0; str[i] != '\0'; ++i)
  {
    len++;
  }
  return len;
}

int studilova::isVowel(char c)
{
  if (!std::isalpha(c))
  {
    return 0;
  }

  char lower = std::tolower(c);
  if (lower == 'a' || lower == 'e' || lower == 'i' || lower == 'o' || lower == 'u' || lower == 'y')
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

void studilova::excludeCharsFromSecond(const char* input, char* output, size_t output_size)
{
  if (output_size == 0)
  {
    return;
  }

  const char* second_string = "abc";
  size_t j = 0;
  for (size_t i = 0; input[i] != '\0'; ++i)
  {
    if (j >= output_size - 1)
    {
      break;
    }

    bool exclude = false;
    for (size_t k = 0; second_string[k] != '\0'; ++k)
    {
      if (input[i] == second_string[k])
      {
        exclude = true;
        break;
      }
    }

    if (!exclude){
      output[j] = input[i];
      j++;
    }
  }
  output[j] = '\0';
}

void studilova::removeVowels(const char* input, char* output, size_t output_size)
{
  if (output_size == 0)
  {
    return;
  }

  size_t j = 0;
  for (size_t i = 0; input[i] != '\0'; ++i)
  {
    if (j >= output_size - 1)
    {
      break;
    }

    if (!studilova::isVowel((input[i])))
    {
      output[j] = input[i];
      j++;
    }
  }
  output[j] = '\0';
}

int main()
{
  char* input_string = nullptr;
  char* result1 = nullptr;
  char* result2 = nullptr;

  input_string = studilova::getLine();

  if (!input_string)
  {
    std::cerr << "Input error" << "\n";
    return 1;
  }

  size_t input_len = studilova::stringLength(input_string);

  try{
    result1 = new char[input_len + 1];
    result2 = new char[input_len + 1];
  } catch (...) {
    std::cerr << "Memory allocation error" << "\n";
    delete[] input_string;
    return 1;
  }

  studilova::excludeCharsFromSecond(input_string, result1, input_len + 1);
  studilova::removeVowels(input_string, result2, input_len + 1);

  std::cout << result1 << "\n";
  std::cout << result2 << "\n";

  delete[] input_string;
  delete[] result1;
  delete[] result2;

  return 0;
}
