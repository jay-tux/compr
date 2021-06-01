#include "bitstream.hpp"

using namespace jay::compression;

bitstream::bitstream() : values{std::queue<bitstream::bit_t>()} {}

bitstream &bitstream::write(bitstream::bit_t value) {
  values.push(value);
  return *this;
}

bitstream::bit_t bitstream::read() {
  if(values.empty()) return false;
  bitstream::bit_t value = values.front();
  values.pop();
  return value;
}

size_t bitstream::size() { return values.size(); }

void bitstream::dump(int perword, int wperline) {
  long curr = 0;
  std::queue<bitstream::bit_t> next;
  while(!values.empty()) {
    bitstream::bit_t value = read();
    std::cout << (value) ? '1' : '0';
    next.push(value);
    curr++;
    if(curr % (wperline * perword) == 0) std::cout << std::endl;
    else if(curr % perword == 0) std::cout << " ";
  }
  values = next;
}

bool bitstream::eof() { return values.empty(); }
