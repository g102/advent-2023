EXTLIBS = $(wildcard ./lib/*.o)
CXXFLAGS = --std=c++23 -Wall -fPIC -O2 -DNDEBUG $(EXTLIBS)
