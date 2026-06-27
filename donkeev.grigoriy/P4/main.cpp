#include <iostream>
#include <iomanip>
#include <cctype>

namespace donkeev
{
  char* reduceSize(char* oldData, const size_t& realSize);
  char* getline(std::istream& input, size_t* size);
  size_t differenceLetters(const char* const array, char* buffer, const size_t sizeOfBuffer);
  char* changeRegister(const char* const array, char* changedArray, const size_t size);
}
char* donkeev::reduceSize(char* oldData, const size_t& realSize)
{
  char* temp = reinterpret_cast< char* > (malloc(sizeof(char) * realSize));
  for (size_t i = 0; i < realSize; ++i)
  {
    temp[i] = oldData[i];
  }
  free(oldData);
  return temp;
}
char* donkeev::getline(std::istream& input, size_t* size)
{
  bool isSkipws = input.flags() & std::ios_base::skipws;
  if (isSkipws)
  {
    input >> std::noskipws;
  }
  size_t extendedSize = 5;
  char* data = reinterpret_cast< char* > (malloc(sizeof(char) * extendedSize));
  if (data == nullptr)
  {
    return data;
  }
  size_t readen = 0;
  char ch;
  input >> ch;
  if (!input)
  {
    free(data);
    throw std::logic_error("empty input");
  }
  while (input)
  {
    data[readen] = ch;
    ++readen;
    if (readen == extendedSize - 1)
    {
      extendedSize += 5;
      char* newData = reinterpret_cast< char* > (malloc(sizeof(char) * extendedSize));
      if (newData == nullptr)
      {
        free(data);
        return nullptr;
      }
      for (size_t i = 0; i < readen; ++i)
      {
        newData[i] = data[i];
      }
      free(data);
      data = newData;
    }
    input >> ch;
  }
  data[readen] = '\0';
  if(isSkipws)
  {
    input >> std::skipws;
  }
  *size = readen + 1;
  if (*size == extendedSize)
  {
    return data;
  }
  char* reducedData = reduceSize(data, *size);
  return reducedData;
}
size_t donkeev::differenceLetters(const char* const array, char* buffer, const size_t sizeOfBuffer)
{
  size_t id = 0;
  if (sizeOfBuffer == 1)
  {
    return 0;
  }
  for(size_t i = 0; i < sizeOfBuffer; ++i)
  {
    if (std::isalpha(array[i]))
    {
      if (std::isupper(array[i]))
      {
        buffer[id] = std::tolower(array[i]);
      }
      else
      {
        buffer[id] = array[i];
      }
      char current = buffer[id];
      ++id;
      for (size_t j = 0; j < id - 1; ++j)
      {
        if (current == buffer[j])
        {
          buffer[id - 1] = '0';
          --id;
        }
      }
    }
  }
  return id;
}
char* donkeev::changeRegister(const char* const array, char* changedArray, const size_t size)
{
  for (size_t i = 0; i < size; ++i)
  {
    if (std::isalpha(array[i]))
    {
      if (std::isupper(array[i]))
      {
        changedArray[i] = std::tolower(array[i]);
      }
      else
      {
        changedArray[i] = array[i];
      }
    }
    else
    {
      changedArray[i] = array[i];
    }
  }
  return changedArray;
}
int main()
{
  size_t size = 0;
  char* array = nullptr;
  try
  {
    array = donkeev::getline(std::cin, &size);
  }
  catch(std::logic_error& e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
  if (array == nullptr)
  {
    std::cerr << "Memory error\n";
    return 1;
  }
  char* buffer = reinterpret_cast< char* > (malloc(sizeof(char) * size));
  if (buffer == nullptr)
  {
    free(array);
    std::cerr << "Memory error\n";
    return 1;
  }
  size_t diflat = donkeev::differenceLetters(array, buffer, size);
  free(buffer);
  std::cout << '\n' << diflat << '\n';
  char* lowLetterArray = reinterpret_cast< char* > (malloc(sizeof(char) * size));
  if (lowLetterArray == nullptr)
  {
    free(array);
    std::cerr << "Memory error\n";
    return 1;
  }
  lowLetterArray = donkeev::changeRegister(array, lowLetterArray, size);
  std::cout << lowLetterArray << '\n';
  free(array);
  free(lowLetterArray);
}
