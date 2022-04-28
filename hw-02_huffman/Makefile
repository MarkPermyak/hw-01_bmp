CXX = g++
CXXFLAGS = -O2 -Wall -Werror -std=c++11 -Iinclude
LDFLAGS = 

EXE = hw-02_huffman
SRCDIR = src
OBJDIR = obj

OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(wildcard $(SRCDIR)/*.cpp))

all: $(EXE)

$(EXE): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(EXE) $(LDFLAGS)
	
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c -MMD -o $@ $<

include $(wildcard $(OBJDIR)/*.d)

$(OBJDIR):
	mkdir -p $(OBJDIR)

obj/test.o: test/doctest.h test/test.cpp src/archiver.cpp
	g++ -c $(CFLAGS) test/test.cpp -o obj/test.o

test: obj obj/huffmanTree.o obj/archiver.o obj/test.o
	g++ obj/huffmanTree.o obj/archiver.o obj/test.o -o hw-02_huffman_test

clean:
	rm -rf $(OBJDIR) $(EXE)

.PHONY: clean all
