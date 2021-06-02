#include "rlc.hpp"

using namespace jay::compression;
using namespace jay::compression::lossless;
typedef RLC rlc;

rlc::pair_t rlc::ignorable = std::make_pair(0, '\0');

rlc::stream &rlc::encode(rlc::stream &target, std::string in) {
  int count = 1;
  char curr = in[0];

  for(int i = 1; i < in.length(); i++) {
    char c = in[i];

    if(c == curr) count++;
    else {
      target.write(std::make_pair(count, curr));
      count = 1;
      curr = c;
    }
  }

  target.write(std::make_pair(count, curr));
  return target;
}

std::string rlc::decode(rlc::stream &input) {
  std::string res = "";

  while(!input.eof()) {
    rlc::pair_t pair = input.read<rlc::pair_t>();
    for(int i = 0; i < pair.first; i++) {
      res += pair.second;
    }
  }

  return res;
}
