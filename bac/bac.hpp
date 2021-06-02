#ifndef _JCOMP_BAC
#define _JCOMP_BAC

//#define DEBUG
#include "../bitstream.hpp"

namespace jay::compression::lossless {
  class BinaryArithmeticCoder {
    public:
      typedef jay::compression::bitstream stream;
      typedef double prec_t;
      typedef long iprec_t;
      static stream &encode(stream &target, std::string in, prec_t &prob);
      static std::string decode(stream &input, prec_t prob, int len);
  };
}

#endif
