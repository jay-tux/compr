#include "lzw.hpp"

using namespace jay::compression;
using namespace jay::compression::lossless;
typedef LZW lzw;

void write_rlz(lzw::stream &s, std::string l) {
  for(auto c : l) {
    s.write(c == '1');
  }
}

template<typename T>
std::string binstr(T v, int len) {
  std::string res = "";
  for(int i = len - 1; i >= 0; i--) res += (v & (1 << i) ? '1' : '0');
  return res;
}

lzw::stream &lzw::encode(lzw::stream &target, std::string in, int len) {
  if(len < 7) throw std::logic_error("Requiring at least 7 bit for ASCII.");

  table map;
  for(int c = 0; c < 128; c++) {
    std::string s = "";
    s += (char)c;
    map[s] = binstr((long)c, len);
  }
  long max = 1 << len;
  long next = 128;

  std::string curr = "";
  curr += in[0];
  for(int i = 1; i < in.length(); i++) {
    if(map.find(curr + in[i]) != map.end()) {
      curr += in[i];
    }
    else {
      write_rlz(target, map[curr]);
      if(next < max) map[curr + in[i]] = binstr(next, len);
      next++;
      curr = "";
      curr += in[i];
    }
  }
  write_rlz(target, map[curr]);
  return target;
}

std::string lzw::decode(lzw::stream &input, int len) {
  if(len < 7) throw std::logic_error("Requiring at least 7 bit for ASCII.");
  if(input.size() % len != 0) throw std::logic_error("Loss detected.");

  std::string res = "";

  invtable map;
  for(int c = 1; c < 128; c++) {
    std::string s = "";
    s += (char)c;
    map[binstr((long)c, len)] = s;
  }
  long max = 1 << len;
  long next = 128;

  std::string s = "";
  while(!input.eof()) {
    std::string curr = "";
    for(int i = 0; i < len; i++) curr += input.read() ? '1' : '0';
    std::string entry;
    if(map.find(curr) != map.end()) {
      entry = map[curr];
    }
    else {
      entry = s;
      entry += s[0];
    }

    res += entry;
    if(s != "" && next < max) {
      s += entry[0];
      map[binstr((long)next, len)] = s;
      next++;
    }
    s = entry;
  }

  return res;
}
