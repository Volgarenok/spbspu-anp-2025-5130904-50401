#include <cstdlib>
#include <fstream>
#include <iostream>

namespace parsov {
  int check_args(int argc);
  int get_mode(const char *num, size_t &mode);
  bool read_mtx(std::istream &in, int *data, size_t n, size_t m);
  size_t sq_side(size_t n, size_t m);
  void write_mtx(std::ostream &out, const int *data, size_t n, size_t m);
  bool lft_top_clk(int *data, size_t n, size_t m);
  bool lft_bot_cnt(int *data, size_t n, size_t m);

  const size_t MAX_STATIC = 10000;
}

int main(int argc, char **argv)
{
  int arg_status = parsov::check_args(argc);
  if (arg_status == 1) {
    std::cerr << "Not enough arguments\n";
    return 1;
  } else if (arg_status == 2) {
    std::cerr << "Too many arguments\n";
    return 1;
  }

  size_t mode = 0;
  int mode_status = parsov::get_mode(argv[1], mode);
  if (mode_status == 1) {
    std::cerr << "First parameter is not a number\n";
    return 1;
  } else if (mode_status == 2) {
    std::cerr << "First parameter is out of range\n";
    return 1;
  }

  std::ifstream in(argv[2]);
  if (!in) {
    std::cerr << "Cannot open input file\n";
    return 2;
  }

  size_t n = 0;
  size_t m = 0;
  in >> n >> m;

  if (!in) {
    std::cerr << "Cannot read matrix header\n";
    return 2;
  }

  if (n == 0 || m == 0) {
    std::ofstream out(argv[3]);
    if (!out) {
      std::cerr << "Cannot open output file\n";
      return 1;
    }
    out << "0 0\n";
    return 0;
  }

  if (mode == 1 && n * m > parsov::MAX_STATIC) {
    std::cerr << "Static buffer overflow\n";
    return 1;
  }

  int *data = nullptr;
  int static_buf[parsov::MAX_STATIC] = {};

  if (mode == 1) {
    data = static_buf;
  } else {
    data = static_cast<int *>(std::malloc(n * m * sizeof(int)));
    if (!data) {
      std::cerr << "Memory allocation failed\n";
      return 1;
    }
  }

  if (!parsov::read_mtx(in, data, n, m)) {
    std::cerr << "Cannot read matrix values\n";
    if (mode == 2) {
      std::free(data);
    }
    return 2;
  }

  in.close();

  bool ok = false;
  if (mode == 1) {
    ok = parsov::lft_top_clk(data, n, m);
  } else {
    ok = parsov::lft_bot_cnt(data, n, m);
  }

  if (!ok) {
    std::cerr << "Memory allocation failed\n";
    if (mode == 2) {
      std::free(data);
    }
    return 1;
  }

  std::ofstream out(argv[3]);
  if (!out) {
    std::cerr << "Cannot open output file\n";
    if (mode == 2) {
      std::free(data);
    }
    return 1;
  }

  parsov::write_mtx(out, data, n, m);
  out << "\n";

  if (mode == 2) {
    std::free(data);
  }

  return 0;
}

int parsov::check_args(const int argc)
{
  if (argc < 4) {
    return 1;
  } else if (argc > 4) {
    return 2;
  }
  return 0;
}

int parsov::get_mode(const char *num, size_t &mode)
{
  const char *p = num;
  if (*p == '\0') {
    return 1;
  }

  while (*p != '\0') {
    if (*p < '0' || *p > '9') {
      return 1;
    }
    ++p;
  }

  if (num[0] == '1' && num[1] == '\0') {
    mode = 1;
    return 0;
  }
  if (num[0] == '2' && num[1] == '\0') {
    mode = 2;
    return 0;
  }

  return 2;
}

bool parsov::read_mtx(std::istream &in, int *data, const size_t n, const size_t m)
{
  const size_t total = n * m;
  for (size_t i = 0; i < total; i++) {
    in >> data[i];
  }
  return static_cast<bool>(in);
}

size_t parsov::sq_side(const size_t n, const size_t m)
{
  if (n < m) {
    return n;
  } else {
    return m;
  }
}

void parsov::write_mtx(std::ostream &out, const int *data, const size_t n, const size_t m)
{
  const size_t side = parsov::sq_side(n, m);

  out << side << " " << side;

  if (side == 0) {
    return;
  }

  out << " ";

  for (size_t r = 0; r < side; ++r) {
    for (size_t c = 0; c < side; c++) {
      out << data[r * m + c];
      if (r * side + c + 1 < side * side) {
        out << " ";
      }
    }
  }
}

bool parsov::lft_top_clk(int *data, const size_t n, const size_t m)
{
  const size_t side = parsov::sq_side(n, m);
  if (side == 0) {
    return true;
  }

  size_t top = 0;
  size_t bottom = side - 1;
  size_t left = 0;
  size_t right = side - 1;

  size_t r = 0;
  size_t c = 0;
  size_t cnt = 0;
  int step = 1;
  int d = 0;

  while (cnt < side * side) {
    data[r * m + c] -= step;
    step++;
    cnt++;

    if (cnt == side * side) {
      break;
    }

    if (d == 0) {
      if (c == right) {
        d = 1;
        top++;
        r++;
      } else {
        c++;
      }
    } else if (d == 1) {
      if (r == bottom) {
        d = 2;
        right--;
        c--;
      } else {
        r++;
      }
    } else if (d == 2) {
      if (c == left) {
        d = 3;
        bottom--;
        r--;
      } else {
        c--;
      }
    } else if (d == 3) {
      if (r == top) {
        d = 0;
        left++;
        c++;
      } else {
        r--;
      }
    }
  }

  return true;
}

bool parsov::lft_bot_cnt(int *data, const size_t n, const size_t m)
{
  const size_t side = parsov::sq_side(n, m);
  if (side == 0) {
    return true;
  }

  size_t top = 0;
  size_t bottom = side - 1;
  size_t left = 0;
  size_t right = side - 1;

  size_t r = side - 1;
  size_t c = 0;
  size_t cnt = 0;
  int step = 1;
  int d = 0;

  while (cnt < side * side) {
    data[r * m + c] += step;
    step++;
    cnt++;

    if (cnt == side * side) {
      break;
    }

    if (d == 0) {
      if (c == right) {
        d = 1;
        bottom--;
        r--;
      } else {
        c++;
      }
    } else if (d == 1) {
      if (r == top) {
        d = 2;
        right--;
        c--;
      } else {
        r--;
      }
    } else if (d == 2) {
      if (c == left) {
        d = 3;
        top++;
        r++;
      } else {
        c--;
      }
    } else if (d == 3) {
      if (r == bottom) {
        d = 0;
        left++;
        c++;
      } else {
        r++;
      }
    }
  }

  return true;
}
