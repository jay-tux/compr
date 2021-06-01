#ifndef _JCOMP_LZW
#define _JCOMP_LZW

#include "../bitstream.hpp"
#include <map>

namespace jay::compression::lossless {
  class LZW {
    public:
      typedef jay::compression::bitstream stream;
      typedef std::map<std::string, std::string> table;
      typedef std::map<std::string, std::string> invtable;
      static stream &encode(stream &target, std::string in, int len = 12);
      static std::string decode(stream &input, int len = 12);
  };
}

#endif
