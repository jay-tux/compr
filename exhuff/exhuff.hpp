#ifndef _JCOMP_HUFFMAN
#define _JCOMP_HUFFMAN

#define DEBUG
#include "../bitstream.hpp"
#include <map>

namespace jay::compression::lossless {
  class ExtendedHuffman {
    public:
      typedef jay::compression::bitstream stream;
      typedef std::map<std::string, std::string> table;
      typedef std::map<std::string, std::string> invtable;
      static stream &encode(stream &target, std::string in, table &outtable, int per);
      static std::string decode(stream &input, table &table, int per);
  };
}

#endif
