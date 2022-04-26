#ifndef ARCHIVER_HPP_
#define ARCHIVER_HPP_

#include "huffmanTree.hpp"
using namespace std;

typedef priority_queue<HuffmanNode*, vector<HuffmanNode*>, NodeComparator> huffman_queue;

class Archiver{
    public:
        string read_input_text(ifstream& fs);
        map<char, int> create_symbols_table(string input);
        huffman_queue create_queue_from_table(map<char, int> symbols);

};


#endif
