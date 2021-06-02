#ifndef _JCOMP_BAC
#define _JCOMP_BAC

//#define DEBUG
#include "../bitstream.hpp"

namespace jay::compression::lossless {
  class AdaptiveBinaryArithmeticCoder {
    public:
      typedef jay::compression::bitstream stream;
      typedef double prec_t;
      typedef long iprec_t;
      static stream &encode(stream &target, std::string in);
      static std::string decode(stream &input, int len);
  };
}

#endif
