#include "sfano.hpp"

using namespace jay::compression;
using namespace jay::compression::lossless;

int main() {
  std::cout << "Enter a message to encode/decode: ";
  std::string msg;
  std::getline(std::cin, msg);
  ShannonFano::table table;
  ShannonFano::stream stream;
  ShannonFano::encode(stream, msg, table).dump();
  std::cout << std::endl << std::endl;
  int len = stream.size();
  std::cout << msg << std::endl << ShannonFano::decode(stream, table) << std::endl;

  std::cout << "Compression ratio: " << (float)len / msg.length() / 8 << std::endl;
}
