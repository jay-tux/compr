CC=g++
CCARGS=-g
LDARGS=

all: setup bin/sfano

setup:
	if [ ! -d bin/ ];       then mkdir bin/;       fi
	if [ ! -d obj/ ];       then mkdir obj/;       fi
	if [ ! -d obj/sfano/ ]; then mkdir obj/sfano/; fi

bin/sfano: obj/sfano/sfano.o obj/sfano/sfano_ex.o obj/bitstream.o
	$(CC) $(LDARGS) $^ -o $@

obj/%.o: %.cpp Makefile
	$(CC) $(CCARGS) -c $< -o $@

clean:
	rm -rf bin/
	rm -rf obj/
	make setup

.PHONY: all setup clean
