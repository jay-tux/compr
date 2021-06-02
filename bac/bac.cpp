#include "bac.hpp"
#include <vector>

using namespace jay::compression;
using namespace jay::compression::lossless;
typedef BinaryArithmeticCoder bac;

bac::stream &bac::encode(bac::stream &target, std::string in, prec_t &prob) {
  std::vector<bac::stream::bit_t> bits;
  for(auto c : in) {
    std::cout << (int)c << std::endl;
    for(int i = 7; i >= 0; i--) bits.push_back(c & (1 << i));
  }

  bac::iprec_t cnt = 0;
  for(auto bit : bits) cnt += (bit) ? 1 : 0;
  bac::prec_t on = 1.0 - (bac::prec_t)cnt / bits.size();
  bac::prec_t low = 0, high = 1, range = 1;

#ifdef DEBUG
  std::cout << " == Bit vector == " << std::endl;
  for(auto bit : bits) std::cout << (bit ? '1' : '0');
  std::cout << std::endl;
  std::cout << " == Determining interval == " << std::endl;
  std::cout << "Probability: " << on << std::endl;
  std::cout << "Initial: interval: [" << low << ", " << high << "[ (length: " << range << ")" << std::endl;
#endif
  for(auto bit : bits) {
    while(high <= 0.5 || low >= 0.5) { //renormalizations
      if(high <= 0.5)  {
        //E1 normalization
        target.write(0);
        low *= 2; high *= 2;
#ifdef DEBUG
        std::cout << " E1 Normalization:";
#endif
      }
      if(low >= 0.5) {
        //E2 normalization
        target.write(1);
        low = low * 2 - 1; high = high * 2 - 1;
#ifdef DEBUG
        std::cout << " E2 Normalization:";
#endif
      }
#ifdef DEBUG
      std::cout << " [" << low << ", " << high << "[ (length: " << (high - low) << ")" << std::endl;
#endif
    }
    range = high - low;

    //encode bit
    if(bit) {
      low += range * on;
    }
    else {
      high = low + range * on;
    }
    range = high - low;
#ifdef DEBUG
    std::cout << "Bit: " << bit << ";  interval: [" << low << ", " << high
              << "[ (length: " << range << ")" << std::endl;
#endif
  }

#ifdef DEBUG
  std::cout << " == Code generation == " << std::endl;
#endif
  bac::prec_t curr = 0.0;
  bac::prec_t upd = 0.5;
  while(curr < low) {
    curr += upd;
#ifdef DEBUG
    std::cout << "~> curr: " << curr << "; upd: " << upd << std::endl;
#endif
    if(curr > high) {
      target.write(0);
#ifdef DEBUG
      std::cout << "  ~> outputting 0" << std::endl;
#endif
      curr -= upd;
    }
    else {
      target.write(1);
#ifdef DEBUG
      std::cout << "  ~> outputting 1" << std::endl;
#endif
    }

    upd /= 2.0;
  }

  prob = on;
  return target;
}

std::string bac::decode(bac::stream &input, bac::prec_t prob, int len) {
  prec_t value = 0.0, curr = 0.5;
  while(!input.eof()) {
    if(input.read()) value += curr;
    curr /= 2;
  }

  std::vector<bac::stream::bit_t> bits;
  prec_t low = 0.0, high = 1.0, range = 1.0;
  for(int i = 0; i < 8 * len; i++) {
    if(value > prob) {
      bits.push_back(1);
      value = (value - prob) / (1.0 - prob);
    }
    else {
      bits.push_back(0);
      value = (value) / (prob);
    }
  }

#ifdef DEBUG
  std::cout << " == Bit vector == " << std::endl;
  for(auto bit : bits) std::cout << (bit ? '1' : '0');
  std::cout << std::endl;
#endif

  std::string res = "";
  for(int i = 0; i < bits.size(); i += 8) {
    signed char c = 0;
    for(int j = 7; j >= 0; j--) {
      if(bits[i + ( 7 - j)]) {
        c = c | (1 << j);
      }
    }
    res += c;
  }
  return res;
}
