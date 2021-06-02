#ifndef _JCOMP_RLC
#define _JCOMP_RLC

#include "../bitstream.hpp"
#include <utility>

namespace jay::compression::lossless {
  class RLC {
    public:
      typedef std::pair<int, char> pair_t;
      typedef jay::compression::gStream<pair_t> stream;

      static stream &encode(stream &target, std::string in);
      static std::string decode(stream &input);
      static pair_t ignorable;
  };
}

#endif
