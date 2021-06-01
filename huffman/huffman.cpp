#include "huffman.hpp"
#include "../tree.hpp"
#include <list>
#include <algorithm>

using namespace jay::compression;
using namespace jay::compression::lossless;
typedef Huffman huff;
typedef std::pair<bintree<char> *, int> pair_t;

void genTable(huff::table &table, bintree<char> *tree, std::string prefix = "") {
  if(tree->value != '\0') {
    table[tree->value] = prefix;
  }
  else {
    genTable(table, tree->left, prefix + "0");
    genTable(table, tree->right, prefix + "1");
  }
}

void write_rlz(huff::stream &s, std::string l) {
  for(auto c : l) {
    s.write(c == '1');
  }
}

huff::stream &huff::encode(huff::stream &target, std::string in, huff::table &outtable) {
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
  for(auto pair : occurences) {
    sorted.push_back(std::make_pair(new bintree<char>(pair.first), pair.second));
  }

  #ifdef DEBUG
  std::cout << " == Alphabet == " << std::endl;
  for(auto pair : sorted) {
    std::cout << " " << pair.first->value << " ~ frequency: " << pair.second << std::endl;
  }
  #endif

  while(sorted.size() > 1) {
    std::sort(sorted.begin(), sorted.end(), [](auto p1, auto p2) {
      return p1.second > p2.second;
    });

    pair_t t1 = sorted[sorted.size() - 1];
    pair_t t2 = sorted[sorted.size() - 2];

    sorted[sorted.size() - 2] = std::make_pair(
      new bintree<char>('\0', t1.first, t2.first),
      t1.second + t2.second
    );
    sorted.pop_back();
  }

  genTable(outtable, sorted[0].first);
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

std::string huff::decode(huff::stream &input, huff::table &table) {
  //invert Table
  std::string s;
  huff::invtable invmap;
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
