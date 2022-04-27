#ifndef HUFFMAN_TREE_HPP_
#define HUFFMAN_TREE_HPP_

#include <iostream>
#include <queue>
#include <map>
#include <string>

using namespace std;


struct HuffmanNode{
    HuffmanNode *left, *right;
    char ch;
    int freq;
    HuffmanNode(char ch_, int freq_){
        ch = ch_;
        freq = freq_;
        left = nullptr;
        right = nullptr;
    }

    ~HuffmanNode(){
        if(left)
            delete left;
        if(right)
            delete right;
    }
};

HuffmanNode* createNode(char ch, int freq);

struct NodeComparator {
        bool operator()(HuffmanNode *a, HuffmanNode *b) {
            return a->freq > b->freq;
        }
};

typedef priority_queue<HuffmanNode*, vector<HuffmanNode*>, NodeComparator> huffman_queue;

class HuffmanTree{
public:
    HuffmanTree(huffman_queue q);
    ~HuffmanTree();

    HuffmanNode* get_root();
    void print_desc_leaves(HuffmanNode* parent);
    void create_code(HuffmanNode* parent, string codeword, map<char, string> &code);
    // HuffmanTree create_tree_from_code(map<char, string> code);
    void decode_from_message(char* buffer, int encoded_message_len_bytes, int padding_size, ofstream& outfs);
private:
    HuffmanNode *root;
};

#endif