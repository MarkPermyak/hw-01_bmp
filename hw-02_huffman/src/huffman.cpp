#include "huffman.hpp"

HuffmanNode* createNode(char ch, int freq){
    
    HuffmanNode* node = new HuffmanNode();
    node->ch = ch;
    node->freq = freq;
    node->left = nullptr;
    node->right = nullptr;

    return node;
};

// HuffmanTree::