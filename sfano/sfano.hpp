#ifndef _JCOMP_SFANO
#define _JCOMP_SFANO

//#define DEBUG

#include <iostream>
#include <map>
#include <vector>
#include "../bitstream.hpp"

namespace jay::compression::lossless {
  class ShannonFano {
    public:
      typedef jay::compression::bitstream stream;
      typedef std::map<char, std::string> table;
      static stream &encode(stream &target, std::string in, table &outtable);
      static std::string decode(stream &input, table &table);
  };
}

#endif
