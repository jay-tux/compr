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

  template <class T_>
  class gStream {
    public:
      template<class T>
      gStream(T _ignored) : values{std::queue<T>()} {}

      template<class T>
      gStream<T> &write(T value) { values.push(value); return *this; }

      template<class T>
      T read() {
        T value = values.front();
        values.pop();
        return value;
      }

      size_t size() { return values.size(); }

      template<class T>
      void dump() {
        long curr = 0;
        std::queue<T> next;
        while(!values.empty()) {
          T value = read();
          std::cout << value << std::endl;
        }
        values = next;
      }

      bool eof() { return values.size() == 0; }

    private:
      std::queue<T_> values;
  };
}

#endif
