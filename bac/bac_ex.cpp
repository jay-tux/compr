#include <iostream>
#include "bac.hpp"

using namespace jay::compression::lossless;

int main() {
  std::string msg;
  std::cout << "String to encode: ";
  std::getline(std::cin, msg);

  BinaryArithmeticCoder::stream strm;
  BinaryArithmeticCoder::prec_t prob;
  BinaryArithmeticCoder::encode(strm, msg, prob).dump();
  int len = strm.size();
  std::cout << std::endl << BinaryArithmeticCoder::decode(strm, prob, msg.length()) << std::endl;
  std::cout << "Compression ratio: " << (float)len / (8 * msg.length()) << std::endl;

}
