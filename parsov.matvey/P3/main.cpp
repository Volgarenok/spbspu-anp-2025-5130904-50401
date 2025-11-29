#include <iostream>
#include <fstream>
#include <cstdlib>

namespace parsov
{
  int check_args(int argc);
  int get_mode(const char * num, size_t & mode);

  bool read_hdr(std::istream & in, size_t & n, size_t & m);

  bool read_mtx(std::istream & in, int * data, size_t n, size_t m);

  size_t sq_side(size_t n, size_t m);

  void write_mtx(std::ostream & out, const int * data, size_t n, size_t m);

  bool spiral_mod(int * data, size_t cols, size_t side, size_t sr, size_t sc, const int dr[4], const int dc[4], int sign);

  bool lft_top_clk(int * data, size_t n, size_t m);
  bool lft_bot_cnt(int * data, size_t n, size_t m);

  const size_t MAX_STATIC = 10000;
}

int main(int argc, char ** argv)
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
    return 1;
  }

  size_t n = 0;
  size_t m = 0;
  if (!parsov::read_hdr(in, n, m)) {
    std::cerr << "Cannot read matrix header\n";
    return 1;
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

  int * data = nullptr;
  int static_buf[parsov::MAX_STATIC] = {};

  if (mode == 1) {
    data = static_buf;
  } else {
    data = static_cast <int *> (std::malloc(n * m * sizeof(int)));
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
    return 1;
  }

  in.close();

  bool ok = (mode == 1 ? parsov::lft_top_clk(data, n, m) : parsov::lft_bot_cnt(data, n, m));

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

int parsov::check_args(int argc)
{
  if (argc < 4) {
    return 1;
  } else if (argc > 4) {
    return 2;
  }
  return 0;
}

int parsov::get_mode(const char * num, size_t & mode)
{
  const char * p = num;

  if (*p == '\0') {
    return 1;
  }

  while (*p) {
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

bool parsov::read_hdr(std::istream & in, size_t & n, size_t & m)
{
  int rn = 0;
  int rm = 0;

  in >> rn >> rm;

  if (!in || rn < 0 || rm < 0) {
    return false;
  }

  n = static_cast<size_t>(rn);
  m = static_cast<size_t>(rm);
  return true;
}

bool parsov::read_mtx(std::istream & in, int * data, size_t n, size_t m)
{
  const size_t total = n * m;
  for (size_t i = 0; i < total; i++) {
    in >> data[i];
  }
  return static_cast<bool>(in);
}

size_t parsov::sq_side(size_t n, size_t m)
{
  return (n < m) ? n : m;
}

void parsov::write_mtx(std::ostream & out, const int * data, size_t n, size_t m)
{
  const size_t side = sq_side(n, m);

  out << side << " " << side;

  if (side == 0) {
    return;
  }

  out << " ";

  const size_t total = side * side;

  for (size_t i = 0; i < total; i++) {
    out << data[i];
    if (i + 1 < total) {
      out << " ";
    }
  }
}

bool parsov::spiral_mod(int * data, size_t cols, size_t side, size_t sr, size_t sc,
                        const int dr[4], const int dc[4], int sign)
{
  if (side == 0) {
    return true;
  }

  bool * used = static_cast <bool *> (std::malloc(side * side * sizeof(bool)));
  if (!used) {
    return false;
  }
  for (size_t i = 0; i < side * side; i++) {
    used[i] = false;
  }

  size_t r = sr;
  size_t c = sc;
  size_t cnt = 0;
  int step = 1;
  int d = 0;

  while (cnt < side * side) {
    used[r * side + c] = true;
    data[r * cols + c] += sign * step;
    ++step;
    ++cnt;

    if (cnt == side * side) {
      break;
    }

    size_t nr = static_cast<size_t>(static_cast<int>(r) + dr[d]);
    size_t nc = static_cast<size_t>(static_cast<int>(c) + dc[d]);

    if (nr >= side || nc >= side || used[nr * side + nc]) {
      d = (d + 1) % 4;
      nr = static_cast<size_t>(static_cast<int>(r) + dr[d]);
      nc = static_cast<size_t>(static_cast<int>(c) + dc[d]);
    }

    r = nr;
    c = nc;
  }

  std::free(used);
  return true;
}

bool parsov::lft_top_clk(int * data, size_t n, size_t m)
{
  const size_t side = sq_side(n, m);

  const int dr[4] = {0, 1, 0, -1};
  const int dc[4] = {1, 0, -1, 0};

  return spiral_mod(data, m, side, 0, 0, dr, dc, -1);
}

bool parsov::lft_bot_cnt(int * data, size_t n, size_t m)
{
  const size_t side = sq_side(n, m);

  const int dr[4] = {-1, 0, 1, 0};
  const int dc[4] = {0, 1, 0, -1};

  const size_t sr = side - 1;
  const size_t sc = 0;

  return spiral_mod(data, m, side, sr, sc, dr, dc, 1);
}
