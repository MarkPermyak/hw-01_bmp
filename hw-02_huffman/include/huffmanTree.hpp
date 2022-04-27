#ifndef HUFFMAN_TREE_HPP_
#define HUFFMAN_TREE_HPP_

#include <iostream>
#include <queue>
#include <map>
#include <string>

struct huffmanNode{
    huffmanNode *left, *right;
    char ch;
    int freq;

    huffmanNode(char ch_, int freq_){
        ch = ch_;
        freq = freq_;
        left = nullptr;
        right = nullptr;
    }

    ~huffmanNode(){
        if(left)
            delete left;
        if(right)
            delete right;
    }
};


struct nodeComparator {
    bool operator()(huffmanNode *a, huffmanNode *b) {
        return a->freq > b->freq;
    }
};

typedef std::priority_queue<huffmanNode*, std::vector<huffmanNode*>, nodeComparator> huffman_queue;

class huffmanTree{
public:
    huffmanTree(huffman_queue q);
    ~huffmanTree();

    int get_size();
    huffmanNode* get_root();

    void print_desc_leaves(huffmanNode* parent);
    void create_code(huffmanNode* parent, std::string codeword, std::map<char, std::string> &code);
    int decode_from_message(char* buffer, int encoded_message_len_bytes, int padding_size, std::ofstream& outfs);

private:
    const int byte_size = 8;
    huffmanNode *root;
    int tree_size = 1;
};

#endif
