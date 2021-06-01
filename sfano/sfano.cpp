#include "sfano.hpp"
#include "../tree.hpp"
#include <algorithm>
#include <functional>
#include <iterator>

using namespace jay::compression;
using namespace jay::compression::lossless;
typedef ShannonFano sfano;
typedef std::pair<char, int> pair_t;

template<typename TIn, typename TOut>
std::vector<TOut> map(std::vector<TIn> vec, std::function<TOut(TIn)> mapper) {
  std::vector<TOut> result;
  for(auto elem : vec) {
    result.push_back(mapper(elem));
  }
  return result;
}

void write_rlz(sfano::stream &s, std::string l) {
  for(auto c : l) {
    s.write(c == '1');
  }
}

bintree<char> *sfano_div(std::vector<pair_t> &v, int begin, int end, int len) {
  if(end - begin == 1) {
    return new bintree<char>(v[begin].first);
  }

  bintree<char> *tree = new bintree<char>('\0'); // \0 is invalid character
  int split = begin;
  float total = 0.0f;
  while(total < len / 2) {
    total += v[split].second;
    split++;
  }

  tree->setLeft(sfano_div(v, begin, split, total));
  tree->setRight(sfano_div(v, split, end, len - total));
  return tree;
}

void genTable(sfano::table &table, bintree<char> *tree, std::string prefix = "") {
  if(tree->value != '\0') {
    table[tree->value] = prefix;
  }
  else {
    genTable(table, tree->left, prefix + "0");
    genTable(table, tree->right, prefix + "1");
  }
}

sfano::stream &sfano::encode(sfano::stream &target, std::string in, sfano::table &outtable) {
  std::map<char, int> occurences;
  for(auto c : in) {
    if(occurences.find(c) == occurences.end()) {
      occurences[c] = 1;
    }
    else {
      occurences[c]++;
    }
  }

  std::vector<pair_t> sorted;
  for(auto pair : occurences) { sorted.push_back(pair); }
  std::sort(sorted.begin(), sorted.end(), [](auto p1, auto p2) {
    return p1.second > p2.second;
  });

#ifdef DEBUG
  std::cout << " == Alphabet == " << std::endl;
  for(auto pair : sorted) {
    std::cout << " " << pair.first << " ~ frequency: " << pair.second << std::endl;
  }
#endif

  auto tree = sfano_div(sorted, 0, sorted.size(), in.length());
  genTable(outtable, tree);
  delete tree;

#ifdef DEBUG
  std::cout << " == Table == " << std::endl;
  for(auto pair : outtable) {
    std::cout << " " << pair.first << " ~ " << pair.second << std::endl;
  }
#endif

  for(auto c : in) {
    write_rlz(target, outtable[c]);
  }

  return target;
}

std::string sfano::decode(sfano::stream &input, sfano::table &table) {
  //invert Table
  std::string s;
  sfano::invtable invmap;
  for(auto pair : table) { invmap[pair.second] = pair.first; }

#ifdef DEBUG
  std::cout << " == Inverse table == " << std::endl;
  for(auto pair : invmap) {
    std::cout << " " << pair.first << " = " << pair.second << std::endl;
  }
#endif

  std::string current;
  while(!input.eof()) {
    current += (input.read()) ? "1" : "0";
    if(invmap.find(current) != invmap.end()) {
      s += invmap[current];
      current = "";
    }
  }
  if(current != "") std::cout << "Loss of data detected!" << std::endl;

  return s;
}
