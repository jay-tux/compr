#include "lzw.hpp"

using namespace jay::compression;
using namespace jay::compression::lossless;

int main() {
  std::cout << "Enter a message to encode/decode: ";
  std::string msg;
  std::getline(std::cin, msg);

  LZW::stream stream;
  LZW::encode(stream, msg).dump();
  std::cout << std::endl << "(" << stream.size() << ")" << std::endl << std::endl;
  int len = stream.size();
  std::cout << msg << std::endl << LZW::decode(stream) << std::endl;

  std::cout << "Compression ratio: " << (float)len / msg.length() / 8 << std::endl;
}
