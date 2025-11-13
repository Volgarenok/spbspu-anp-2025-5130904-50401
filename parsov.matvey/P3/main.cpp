#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cstdlib>

namespace parsov
{
  void check_args(int argc);
  size_t get_mode(const char * num);
  void read_hdr(std::istream & in, size_t & n, size_t & m);
  std::istream & read_mtx_static(std::istream & in, int * buf,
                                 size_t n, size_t m);
  std::istream & read_mtx_dyn(std::istream & in, int * data,
                              size_t n, size_t m);
  size_t sq_side(size_t n, size_t m);
  std::ostream & write_mtx(std::ostream & out, const int * data,
                           size_t n, size_t m);
  bool spiral_mod(int * data,
                  size_t cols,
                  size_t side,
                  size_t sr,
                  size_t sc,
                  const int dr[4],
                  const int dc[4],
                  int sign);
  bool lft_top_clk(int * data, size_t n, size_t m);
  bool lft_bot_cnt(int * data, size_t n, size_t m);
  const size_t MAX_STATIC = 10000;
}

int main(int argc, char ** argv)
{
  try {
    parsov::check_args(argc);
    const size_t mode = parsov::get_mode(argv[1]);
    (void)mode;
    return 0;
  }catch(std::runtime_error & e) {
    std::cerr << e.what();
    return 1;
  }catch(...) {
    std::cerr << "Unknown error\n";
    return 1;
  }
}

void parsov::check_args(int argc)
{
  if(argc < 4) {
    throw std::runtime_error("Not enough arguments\n");
  }else if(argc > 4) {
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

std::istream & parsov::read_mtx_static(std::istream & in, int * buf,
                                       size_t n, size_t m)
{
  const size_t total = n * m;

  for(size_t i = 0; i < total; i++) {
    if(!(in >> buf[i])) {
      throw std::runtime_error("Cannot read matrix values\n");
    }
  }

  return in;
}

std::istream & parsov::read_mtx_dyn(std::istream & in, int * data,
                                    size_t n, size_t m)
{
  const size_t total = n * m;

  for(size_t i = 0; i < total; i++) {
    if(!(in >> data[i])) {
      throw std::runtime_error("Cannot read matrix values\n");
    }
  }

  return in;
}

size_t parsov::sq_side(size_t n, size_t m)
{
  return (n < m ? n : m);
}

std::ostream & parsov::write_mtx(std::ostream & out, const int * data,
                                 size_t n, size_t m)
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
