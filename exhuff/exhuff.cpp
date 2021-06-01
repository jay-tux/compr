#include "exhuff.hpp"
#include "../tree.hpp"
#include <list>
#include <algorithm>
#include <stdexcept>

using namespace jay::compression;
using namespace jay::compression::lossless;
typedef ExtendedHuffman huff;
typedef std::pair<bintree<std::string> *, int> pair_t;

void genTable(huff::table &table, bintree<std::string> *tree, std::string prefix = "") {
  if(tree->value != "") {
    table[tree->value] = (prefix == "") ? "0" : prefix;
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

huff::stream &huff::encode(huff::stream &target, std::string in, huff::table &outtable, int per) {
  if(in.length() % per != 0) {
    throw std::logic_error("String remainder will cause data loss.");
  }

  std::map<std::string, int> occurences;
  for(int i = 0; i < in.length(); i+=per) {
    std::string s = "";
    for(int j = i; j < i + per; j++) {
      s += in[j];
    }

    if(occurences.find(s) == occurences.end()) {
      occurences[s] = 1;
    }
    else {
      occurences[s]++;
    }
  }

  std::vector<pair_t> sorted;
  for(auto pair : occurences) {
    sorted.push_back(std::make_pair(new bintree<std::string>(pair.first), pair.second));
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
      new bintree<std::string>(std::string(""), t1.first, t2.first),
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

  for(int i = 0; i < in.length(); i += per) {
    std::string s;
    for(int j = i; j < i + per; j++) s += in[j];
    write_rlz(target, outtable[s]);
  }

  return target;
}

std::string huff::decode(huff::stream &input, huff::table &table, int per) {
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
