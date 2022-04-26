#include <fstream>
#include <sstream>
#include "archiver.hpp"
using namespace std;

string Archiver::read_input_text(ifstream& fs){
    stringstream buffer;
    buffer << fs.rdbuf();
    
    return buffer.str();
}

map<char, int> Archiver::create_symbols_table(string input){
    map<char, int> symbols;

    for (size_t i = 0; i < input.length(); i++)    
        symbols[input[i]]++; 

    return symbols;
}

huffman_queue Archiver::create_queue_from_table(map<char, int> symbols){
    huffman_queue q;

    for (const auto& n : symbols){
        HuffmanNode* node = createNode(n.first, n.second);
        q.push(node);
    }
    return q;
};
