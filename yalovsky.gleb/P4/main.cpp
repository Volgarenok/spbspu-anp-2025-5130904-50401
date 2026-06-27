#include <iostream>
#include <cstddef>
#include <cctype>
#include <cstring>

namespace yalovsky
{
  char* createString(size_t capacity)
  {
    if (capacity == 0)
    {
      return nullptr;
    }

    char* str = nullptr;
    try
    {
      str = new char[capacity];
    }
    catch (const std::bad_alloc&)
    {
      std::cerr << "bad alloc\n";
      return nullptr;
    }
    return str;
  }

  char* readLine(std::istream& input)
  {
    const size_t kInitialCapacity = 64;
    size_t capacity = kInitialCapacity;
    size_t length = 0;

    char* buffer = createString(capacity);
    if (!buffer)
    {
      return nullptr;
    }

    char currentChar = 0;
    bool wasSkipws = input.flags() & std::ios_base::skipws;

    if (wasSkipws)
    {
      input >> std::noskipws;
    }

    if (!input.get(currentChar))
    {
      delete[] buffer;
      if (wasSkipws)
      {
        input >> std::skipws;
      }
      return nullptr;
    }

    do
    {
      if (currentChar == '\n')
      {
        break;
      }

      if (length + 1 >= capacity)
      {
        size_t newCapacity = capacity * 2;
        char* newBuffer = createString(newCapacity);
        if (!newBuffer)
        {
          delete[] buffer;
          if (wasSkipws)
          {
            input >> std::skipws;
          }
          return nullptr;
        }

        for (size_t i = 0; i < length; ++i)
        {
          newBuffer[i] = buffer[i];
        }

        delete[] buffer;
        buffer = newBuffer;
        capacity = newCapacity;
      }

      buffer[length] = currentChar;
      ++length;
    }
    while (input.get(currentChar));

    buffer[length] = '\0';

    if (wasSkipws)
    {
      input >> std::skipws;
    }

    return buffer;
  }

  char* removeVowels(const char* source)
  {
    if (!source)
    {
      return nullptr;
    }

    size_t sourceLength = std::strlen(source);
    char* result = createString(sourceLength + 1);
    if (!result)
    {
      return nullptr;
    }

    size_t resultIndex = 0;
    for (size_t i = 0; i < sourceLength; ++i)
    {
      char currentChar = source[i];
      bool isVowel = false;

      if (std::isalpha(static_cast< unsigned char >(currentChar)))
      {
        char lowerChar = std::tolower(static_cast< unsigned char >(currentChar));
        switch (lowerChar)
        {
          case 'a':
          case 'e':
          case 'i':
          case 'o':
          case 'u':
            isVowel = true;
            break;
          default:
            break;
        }
      }

      if (!isVowel)
      {
        result[resultIndex] = currentChar;
        ++resultIndex;
      }
    }

    result[resultIndex] = '\0';
    return result;
  }

  int hasSequentialDuplicates(const char* str)
  {
    if (!str)
    {
      return -1;
    }

    size_t length = std::strlen(str);
    if (length < 2)
    {
      return 0;
    }

    for (size_t i = 1; i < length; ++i)
    {
      if (str[i] == str[i - 1])
      {
        return 1;
      }
    }

    return 0;
  }
}

int main()
{
  using namespace yalovsky;

  char* inputStr = readLine(std::cin);
  if (!inputStr)
  {
    std::cerr << "Error: failed to read input string\n";
    return 1;
  }

  int hasDuplicates = hasSequentialDuplicates(inputStr);
  if (hasDuplicates == -1)
  {
    std::cerr << "Error: failed to check for sequential duplicates\n";
    delete[] inputStr;
    return 1;
  }

  char* noVowelsStr = removeVowels(inputStr);
  if (!noVowelsStr)
  {
    std::cerr << "Error: failed to remove vowels\n";
    delete[] inputStr;
    return 1;
  }

  std::cout << hasDuplicates << '\n';
  std::cout << noVowelsStr << '\n';

  delete[] inputStr;
  delete[] noVowelsStr;

  return 0;
}
