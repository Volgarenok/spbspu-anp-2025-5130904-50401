#include <iostream>
#include <iomanip>

namespace goltsov
{
  void increaseSize(char** str, size_t& size);
  void reduceSize(char** str, size_t& size);
  void getLine(std::istream& in, char** str, size_t& size);
  void spcRmv(char* str, size_t size, char* new_str, size_t& new_size);
  void getStr(std::istream& in, char** str, size_t& size);
  int hasSam(char* el1, char* el2, size_t size);
  void makeNormal(char* normal, size_t normal_size, char* abnormal);
}

int main()
{
  char* str = nullptr;
  size_t size = 0;
  try
  {
    goltsov::getLine(std::cin, & str, size);
  }
  catch (const std::bad_alloc& e)
  {
    delete[] str;
    return 1;
  }

  if (std::cin.eof())
  {
    delete[] str;
    return 1;
  }

  size_t new_size = 0;
  char* new0_str = nullptr;
  try
  {
    new0_str = new char[size + 1];
  }
  catch (const std::bad_alloc& e)
  {
    delete[] str;
    delete[] new0_str;
    return 1;
  }

  goltsov::spcRmv(str, size, new0_str, new_size);

  char* new_str = nullptr;
  try
  {
    new_str = new char[new_size + 1];
  }
  catch (const std::bad_alloc& e)
  {
    delete[] str;
    delete[] new0_str;
    delete[] new_str;
    return 1;
  }

  goltsov::makeNormal(new_str, new_size + 1, new0_str);

  char my_str[4] = "abs";
  size_t my_size = 3;

  int has_sam = goltsov::hasSam(str, my_str, (size < my_size ? size : my_size));

  std::cout << "Expects output (return 0) with second string " << "\"" << my_str << "\"" << ": " << has_sam << '\n';
  std::cout << "Expects output (return 0): " << new_str << '\n';

  delete[] str;
  delete[] new0_str;
  delete[] new_str;

  return 0;
}

void goltsov::increaseSize(char** str, size_t& size)
{
  ++size;
  char* new_str = new char[size];
  for (size_t i = 0; i + 1 < size; ++i)
  {
    new_str[i] = str[0][i];
  }
  delete[] * str;
  * str = new_str;
}

void goltsov::reduceSize(char** str, size_t& size)
{
  --size;
  char* new_str = new char[size];
  for (size_t i = 0; i + 1 < size; ++i)
  {
    new_str[i] = str[0][i];
  }
  delete[] * str;
  * str = new_str;
}

void goltsov::getLine(std::istream& in, char** str, size_t& size)
{
  bool is_skipws = in.flags() & std::ios_base::skipws;
  if (is_skipws)
  {
    in >> std::noskipws;
  }

  goltsov::increaseSize(str, size);

  char a = '\0';
  while (std::cin >> a && a != '\n')
  {
    str[0][size - 1] = a;
    goltsov::increaseSize(str, size);
  }

  if (in.eof())
  {
    return;
  }

  str[0][size - 1] = '\0';

  --size;

  if (is_skipws)
  {
    in >> std::skipws;
  }
}

void goltsov::spcRmv(char* str, size_t size, char* new_str, size_t& new_size)
{
  size_t i = 0;
  size_t j = 0;
  if (str[i] == '\0')
  {
    new_str[j] = '\0';
    return;
  }
  while (str[i] == ' ')
  {
    ++i;
  }
  if (str[i] == '\0')
  {
    new_str[j] = '\0';
    return;
  }
  new_str[j] = str[i];
  ++i;
  ++j;

  for (; i < size; ++i)
  {
    if (!(str[i] == ' ' && new_str[j - 1] == ' '))
    {
      new_str[j] = str[i];
      ++j;
    }
  }
  if (new_str[j - 1] == ' ')
  {
    --j;
  }
  new_str[j] = '\0';

  new_size = j;
}

int goltsov::hasSam(char* el1, char* el2, size_t size)
{
  for (size_t i = 0; i < size; ++i)
  {
    for (size_t j = 0; j < size; ++j)
    {
      if (el1[i] == el2[j])
      {
        return 1;
      }
    }
  }
  return 0;
}

void goltsov::makeNormal(char* normal, size_t normal_size, char* abnormal)
{
  for (size_t i = 0; i < normal_size; ++i)
  {
    normal[i] = abnormal[i];
  }
}
