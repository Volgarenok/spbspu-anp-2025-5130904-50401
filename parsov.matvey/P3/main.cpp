#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cstdlib>

namespace parsov
{
  void check_args(int argc);
  size_t get_mode(const char * num);

  void read_hdr(std::istream & in, size_t & n, size_t & m);

  std::istream & read_mtx_static(std::istream & in, int * buf, size_t n, size_t m);

  std::istream & read_mtx_dyn(std::istream & in, int * data, size_t n, size_t m);

  size_t sq_side(size_t n, size_t m);

  std::ostream & write_mtx(std::ostream & out, const int * data, size_t n, size_t m);

  bool spiral_mod(int * data, size_t cols, size_t side, size_t sr, size_t sc, const int dr[4], const int dc[4], int sign);

  bool lft_top_clk(int * data, size_t n, size_t m);
  bool lft_bot_cnt(int * data, size_t n, size_t m);

  const size_t MAX_STATIC = 10000;
}

int main(int argc, char ** argv)
{
  int * data = nullptr;
  size_t mode = 0;

  try {
    parsov::check_args(argc);

    mode = parsov::get_mode(argv[1]);

    std::ifstream in(argv[2]);
    if(!in) {
      throw std::runtime_error("Cannot open input file\n");
    }

    size_t n = 0;
    size_t m = 0;
    parsov::read_hdr(in, n, m);

    if(n == 0 || m == 0) {
      std::ofstream out(argv[3]);
      if(!out) {
        throw std::runtime_error("Cannot open output file\n");
      }
      out << "0 0\n";
      return 0;
    }

    if(mode == 1 && n * m > parsov::MAX_STATIC) {
      throw std::runtime_error("Static buffer overflow\n");
    }

    int static_buf[parsov::MAX_STATIC] = {};
    if (mode == 1) {
      data = static_buf;
      if (!parsov::read_mtx_static(in, data, n, m)) {
        throw std::runtime_error("Cannot read matrix values\n");
      }
    } else {
      data = static_cast <int *> (std::malloc(n * m * sizeof(int)));
      if (!data) {
        throw std::runtime_error("Memory allocation failed\n");
      }
      if (!parsov::read_mtx_dyn(in, data, n, m)) {
        throw std::runtime_error("Cannot read matrix values\n");
      }
    }

    in.close();

    bool ok = (mode == 1 ? parsov::lft_top_clk(data, n, m) : parsov::lft_bot_cnt(data, n, m));

    if (!ok) {
      if (mode == 2 && data) {
        std::free(data);
      }
      throw std::runtime_error("Processing error\n");
    }

    std::ofstream out(argv[3]);
    if(!out) {
      if(mode == 2 && data) {
        std::free(data);
      }
      throw std::runtime_error("Cannot open output file\n");
    }

    parsov::write_mtx(out, data, n, m);
    out << "\n";

    if(mode == 2 && data) {
      std::free(data);
    }

    return 0;

  } catch (std::runtime_error & e) {
    std::cerr << e.what();
    if (mode == 2 && data) {
      std::free(data);
    }
    return 1;
  } catch (...) {
    std::cerr << "Unknown error\n";
    if (mode == 2 && data) {
      std::free(data);
    }
    return 1;
  }
}

void parsov::check_args(int argc)
{
  if(argc < 4) {
    throw std::runtime_error("Not enough arguments\n");
  } else if(argc > 4) {
    throw std::runtime_error("Too many arguments\n");
  }
}

size_t parsov::get_mode(const char * num)
{
  const char * p = num;

  if(*p == '\0') {
    throw std::runtime_error("First parameter is not a number\n");
  }

  while(*p) {
    if(*p < '0' || *p > '9') {
      throw std::runtime_error("First parameter is not a number\n");
    }
    ++p;
  }

  if(num[0] == '1' && num[1] == '\0') {
    return 1;
  }
  if(num[0] == '2' && num[1] == '\0') {
    return 2;
  }

  throw std::runtime_error("First parameter is out of range\n");
}

void parsov::read_hdr(std::istream & in, size_t & n, size_t & m)
{
  int rn = 0;
  int rm = 0;

  in >> rn >> rm;

  if(!in || rn < 0 || rm < 0) {
    throw std::runtime_error("Cannot read matrix header\n");
  }

  n = static_cast<size_t>(rn);
  m = static_cast<size_t>(rm);
}

std::istream & parsov::read_mtx_static(std::istream& in, int* buf, size_t n, size_t m)
{
    const size_t total = n * m;

    for(size_t i = 0; i < total; i++) {
        in >> buf[i];
    }

    return in;
}

std::istream & parsov::read_mtx_dyn(std::istream & in, int * data, size_t n, size_t m)
{
  const size_t total = n * m;
  for(size_t i = 0; i < total; i++) {
    in >> data[i];
  }
  return in;
}

size_t parsov::sq_side(size_t n, size_t m)
{
  return std::min(n, m);
}

std::ostream & parsov::write_mtx(std::ostream & out, const int * data, size_t n, size_t m)
{
  const size_t side = sq_side(n, m);

  out << side << " " << side;

  if(side == 0) {
    return out;
  }

  out << " ";

  const size_t total = side * side;

  for(size_t i = 0; i < total; i++) {
    out << data[i];
    if(i + 1 < total) {
      out << " ";
    }
  }

  return out;
}

bool parsov::spiral_mod(int * data, size_t cols, size_t side, size_t sr, size_t sc,
                        const int dr[4], const int dc[4], int sign)
{
  if(side == 0) {
    return true;
  }

  bool * used = static_cast <bool *> (std::malloc(side * side * sizeof(bool)));
  if(!used) {
    throw std::runtime_error("Memory allocation failed\n");
  }
  for(size_t i = 0; i < side * side; i++) {
    used[i] = false;
  }

  size_t r = sr;
  size_t c = sc;
  size_t cnt = 0;
  int step = 1;
  int d = 0;

  while(cnt < side * side) {
    used[r * side + c] = true;
    data[r * cols + c] += sign * step;
    ++step;
    ++cnt;

    if(cnt == side * side) {
      break;
    }

    size_t nr = static_cast<size_t>(static_cast<int>(r) + dr[d]);
    size_t nc = static_cast<size_t>(static_cast<int>(c) + dc[d]);

    if(nr >= side || nc >= side || used[nr * side + nc]) {
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
