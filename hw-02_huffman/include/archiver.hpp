#ifndef ARCHIVER_HPP_
#define ARCHIVER_HPP_

#include <bitset>
#include <fstream>
#include <sstream>

#include "huffmanTree.hpp"
using namespace std;

class archiver{
    public:
        void encode(ifstream& fs, ofstream& outfs);
        void decode(ifstream& fs, ofstream& outfs);
    private:
        string read_input_text(ifstream& fs);
        map<char, int> create_symbols_table(string input);
        huffman_queue create_queue_from_table(map<char, int> symbols);
        void write_int_byte_to_file(int num, ofstream& outfs);
};


#endif
