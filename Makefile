CC=g++
CCARGS=-g
LDARGS=

all: setup bin/sfano bin/huffman bin/exhuff

setup:
	if [ ! -d bin/ ];         then mkdir bin/;         fi
	if [ ! -d obj/ ];         then mkdir obj/;         fi
	if [ ! -d obj/sfano/ ];   then mkdir obj/sfano/;   fi
	if [ ! -d obj/huffman/ ]; then mkdir obj/huffman/; fi
	if [ ! -d obj/exhuff/ ];  then mkdir obj/exhuff/;  fi

bin/sfano: obj/sfano/sfano.o obj/sfano/sfano_ex.o obj/bitstream.o
	$(CC) $(LDARGS) $^ -o $@

bin/huffman: obj/huffman/huffman.o obj/huffman/huffman_ex.o obj/bitstream.o
	$(CC) $(LDARGS) $^ -o $@

bin/exhuff: obj/exhuff/exhuff.o obj/exhuff/exhuff_ex.o obj/bitstream.o
	$(CC) $(LDARGS) $^ -o $@

obj/%.o: %.cpp Makefile
	$(CC) $(CCARGS) -c $< -o $@

clean:
	rm -rf bin/
	rm -rf obj/
	make setup

.PHONY: all setup clean
