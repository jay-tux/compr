# Compression
*A small collection of compression algorithms, in C++*

## Algorithms
The names between brackets indicate the directories, Makefile targets and executables:  

 Algorithm | Directory | Makefile target | executable  
 --- | --- | --- | ---  
 Example (`ex`) | `./ex/` | `make bin/ex` | `bin/ex`  

It also indicates the files existing for that encoder (using the same example): `./ex/ex.hpp` (header file), `./ex/ex.cpp` (source file), and `./ex/ex_ex.cpp` (example use).

 - Lossless Algorithms  
   - Shannon-Fano (`sfano`)  
   - Huffman  
     - Normal Huffman (`huffman`)  
     - Extended Huffman (`exhuff`)