#include <iostream>
#include <stdexcept>

namespace parsov
{
  void check_argc_validity(int argc);
  size_t get_first_parameter(const char* num);
} // namespace parsov

int main(int argc, char** argv)
{
  try
  {
    parsov::check_argc_validity(argc);
    size_t mode = parsov::get_first_parameter(argv[1]);
    (void)mode;
    return 0;
  }
  catch (std::runtime_error& e)
  {
    std::cerr << e.what();
    return 1;
  }
  catch (...)
  {
    std::cerr << "Unknown error\n";
    return 1;
  }
}

void parsov::check_argc_validity(int argc)
{
  if (argc < 4)
  {
    throw std::runtime_error("Not enough arguments\n");
  }
  if (argc > 4)
  {
    throw std::runtime_error("Too many arguments\n");
  }
}

size_t parsov::get_first_parameter(const char* num)
{
  const char* p = num;

  if (*p == '\0')
  {
    throw std::runtime_error("First parameter is not a number\n");
  }

  while (*p)
  {
    if (*p < '0' || *p > '9')
    {
      throw std::runtime_error("First parameter is not a number\n");
    }
    ++p;
  }

  if (num[0] == '1' && num[1] == '\0')
  {
    return 1;
  }
  if (num[0] == '2' && num[1] == '\0')
  {
    return 2;
  }

  throw std::runtime_error("First parameter is out of range\n");
}
