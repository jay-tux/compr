#ifndef _JCOMP_BITSTREAM
#define _JCOMP_BITSTREAM

#include <queue>
#include <iostream>

namespace jay::compression {
  class bitstream {
    public:
      bitstream();
      typedef bool bit_t;
      bitstream &write(bit_t value);
      bit_t read();
      size_t size();
      void dump(int perword = 8, int wperline = 4);
      bool eof();
    private:
      std::queue<bit_t> values;
  };
}

#endif
