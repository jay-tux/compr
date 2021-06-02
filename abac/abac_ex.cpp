#include <iostream>
#include "abac.hpp"

using namespace jay::compression::lossless;

int main() {
  std::string msg;
  std::cout << "String to encode: ";
  std::getline(std::cin, msg);

  AdaptiveBinaryArithmeticCoder::stream strm;
  AdaptiveBinaryArithmeticCoder::prec_t prob;
  AdaptiveBinaryArithmeticCoder::encode(strm, msg).dump();
  int len = strm.size();
  std::cout << std::endl << AdaptiveBinaryArithmeticCoder::decode(strm, msg.length()) << std::endl;
  std::cout << "Compression ratio: " << (float)len / (8 * msg.length()) << std::endl;

}
