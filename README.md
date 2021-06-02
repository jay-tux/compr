# Compression
*A small collection of compression algorithms, in C++*

## Algorithms
The names between brackets indicate the directories, Makefile targets and executables:  

 Algorithm | Directory | Makefile target | executable  
 --- | --- | --- | ---  
 Example (`ex`) | `./ex/` | `make bin/ex` | `bin/ex`  

It also indicates the files existing for that encoder (using the same example): `./ex/ex.hpp` (header file), `./ex/ex.cpp` (source file), and `./ex/ex_ex.cpp` (example use).

 - Lossless Algorithms (namespace `jay::compression::lossless`)  
   - Shannon-Fano (`sfano`, class name: `ShannonFano`)  
   - Huffman  
     - Normal Huffman (`huffman`, class name: `Huffman`)  
     - Extended Huffman (`exhuff`, class name: `ExtendedHuffman`)  
   - LZW (`lzw`, class name: `LZW`)  
   - Arithmetic Coders (![Warning](https://img.shields.io/badge/_-Warning:-red) due to floating-point precision, message length is limited.)  
     - Binary Arithmetic Coder (`bac`, class name: `BinaryArithmeticCoder`)  
     - Adaptive Binary Arithmetic Coder (`abac`, class name: `AdaptiveBinaryArithmeticCoder`)
