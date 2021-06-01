#include "exhuff.hpp"

using namespace jay::compression;
using namespace jay::compression::lossless;

int main() {
  std::cout << "Enter a message to encode/decode: ";
  std::string msg;
  std::getline(std::cin, msg);
  int k;
  do {
    std::cout << "Enter symbol length (must be divisor of " << msg.length() << "): ";
    std::cin >> k;
  } while(msg.length() % k != 0);

  ExtendedHuffman::table table;
  ExtendedHuffman::stream stream;
  ExtendedHuffman::encode(stream, msg, table, k).dump();
  std::cout << std::endl << std::endl;
  int len = stream.size();
  std::cout << msg << std::endl << ExtendedHuffman::decode(stream, table, k) << std::endl;

  std::cout << "Compression ratio: " << (float)len / msg.length() << std::endl;
}
