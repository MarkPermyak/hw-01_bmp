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

    huffmanNode(){
        ch = '\0';
        freq = 0;
        left = nullptr;
        right = nullptr;
    }

    huffmanNode(char ch_, int freq_){
        ch = ch_;
        freq = freq_;
        left = nullptr;
        right = nullptr;
    }

    ~huffmanNode(){
        delete left;
        delete right;
    }
};


struct nodeComparator {
    bool operator()(const huffmanNode *a, const huffmanNode *b) {
        return a->freq > b->freq;
    }
};

typedef std::priority_queue<huffmanNode*, std::vector<huffmanNode*>, nodeComparator> huffmanQueue;

class huffmanTree{
public:
    huffmanTree(huffmanQueue& q);
    ~huffmanTree();

    int get_size();
    huffmanNode* get_root();

    void print_desc_leaves(huffmanNode* parent);
    void create_code(huffmanNode* parent, const std::string& codeword, std::map<char, std::string>& code);
    int decode_from_message(const char* buffer, int encoded_message_len_bytes, int padding_size, std::ofstream& outfs);

private:
    const int byte_size = 8;
    huffmanNode *root;
    int tree_size = 1;
};

#endif
