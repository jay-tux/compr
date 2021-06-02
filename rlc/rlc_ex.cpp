#include <iostream>
#include "rlc.hpp"

using namespace jay::compression::lossless;

int main() {
  std::string msg;
  std::cout << "String to encode: ";
  std::getline(std::cin, msg);

  RLC::stream strm(RLC::ignorable);
  RLC::encode(strm, msg);
  int len = strm.size();
  std::cout << std::endl << RLC::decode(strm) << std::endl;
  std::cout << "Compression ratio: " << (float)len / (msg.length()) << std::endl;
  std::cout << "  -> CR might be non-representative: a pair might not be coded with one byte." << std::endl;

}
