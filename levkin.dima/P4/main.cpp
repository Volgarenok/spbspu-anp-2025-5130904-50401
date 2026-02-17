#include <cctype>
#include <cstddef>
#include <ios>
#include <iostream>

namespace levkin {
  char* extend(char* old_buffer, size_t old_size, size_t new_size);
  char* getLine(std::istream& in, size_t& size);
  int hasRep(const char* s);
  char* latRmv(const char* original, char* destination, size_t& s);
}

int main()
{
  size_t len = 0;
  char* str = levkin::getLine(std::cin, len);

  if (!str || len == 0) {
    std::cerr << "Error: cannot allocate memory or empty input\n";
    return 1;
  }

  std::cout << "Has repeated: " << levkin::hasRep(str) << "\n";

  char* cleaned = static_cast< char* >(malloc(len + 1));
  if (!cleaned) {
    std::cerr << "Error: cannot allocate memory\n";
    free(str);
    return 1;
  }

  size_t cleaned_len = 0;
  levkin::latRmv(str, cleaned, cleaned_len);
  std::cout << "Removed English letter:: " << cleaned << "\n";

  free(cleaned);
  free(str);
  return 0;
}

char* levkin::extend(char* old_buffer, size_t old_size, size_t new_size)
{
  char* new_buffer = reinterpret_cast< char* >(malloc(new_size));
  if (!new_buffer) {
    return nullptr;
  }
  for (size_t i = 0; i < old_size; i++) {
    new_buffer[i] = old_buffer[i];
  }
  for (size_t i = old_size; i < new_size; i++) {
    new_buffer[i] = ' ';
  }
  free(old_buffer);
  return new_buffer;
}

char* levkin::getLine(std::istream& in, size_t& size)
{
  bool is_skip_ws = in.flags() & std::ios_base::skipws;

  if (is_skip_ws) {
    in >> std::noskipws;
  }

  size = 0;
  size_t capacity = 0;
  char* buffer = nullptr;
  char c;

  while (in >> c) {
    if (size == capacity) {
      size_t new_cap = capacity ? capacity + 5 : 5;
      char* tmp = extend(buffer, capacity, new_cap);

      if (!tmp) {
        free(buffer);

        if (is_skip_ws) {
          in >> std::skipws;
        }

        return nullptr;
      }

      buffer = tmp;
      capacity = new_cap;
    }

    buffer[size++] = c;
  }

  if (size == 0) {
    free(buffer);
    if (is_skip_ws) {
      in >> std::skipws;
    }
    return nullptr;
  }

  if (size == capacity) {
    char* tmp = extend(buffer, capacity, capacity + 1);
    if (!tmp) {
      free(buffer);

      if (is_skip_ws) {
        in >> std::skipws;
      }

      return nullptr;
    }
    buffer = tmp;
  }

  buffer[size] = '\0';

  if (is_skip_ws) {
    in >> std::skipws;
  }
  return buffer;
}

int levkin::hasRep(const char* s)
{
  unsigned char visited[256] = {0};

  if (!s) {
    return 0;
  }

  for (; *s; ++s) {
    unsigned char c = *s;

    if (visited[c]) {
      return 1;
    }

    visited[c] = 1;
  }
  return 0;
}

char* levkin::latRmv(const char* original, char* destination, size_t& s)
{
  if (!original || !destination) {
    s = 0;
    return nullptr;
  }
  size_t w = 0;
  for (size_t r = 0; original[r]; ++r) {
    char ch = original[r];
    if (isalpha(static_cast< unsigned char >(ch))) {
      continue;
    }
    destination[w++] = ch;
  }
  destination[w] = '\0';
  s = w;
  return destination;
}
