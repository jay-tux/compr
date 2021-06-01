#ifndef _JCOMP_HUFFMAN
#define _JCOMP_HUFFMAN

//#define DEBUG
#include "../bitstream.hpp"
#include <map>

namespace jay::compression::lossless {
  class Huffman {
    public:
      typedef jay::compression::bitstream stream;
      typedef std::map<char, std::string> table;
      typedef std::map<std::string, char> invtable;
      static stream &encode(stream &target, std::string in, table &outtable);
      static std::string decode(stream &input, table &table);
  };
}

#endif
