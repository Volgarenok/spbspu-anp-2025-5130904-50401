#include <iostream>
#include <cstddef>
#include <limits>
#include <new>

namespace burukov
{
  size_t stringLength(const char* str);
  char* getline(std::istream& input);
  
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

int main()
{
  return 0;
}