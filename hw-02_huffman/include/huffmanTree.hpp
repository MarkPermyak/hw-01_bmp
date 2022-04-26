#ifndef HUFFMAN_TREE_HPP_
#define HUFFMAN_TREE_HPP_

#include <iostream>
#include <queue>
#include <map>
#include <string>

using namespace std;


struct HuffmanNode
{
    HuffmanNode *left, *right;
	char ch;
	int freq;
};

HuffmanNode* createNode(char ch, int freq);

struct NodeComparator {
        bool operator()(HuffmanNode *a, HuffmanNode *b) {
            return a->freq > b->freq;
        }
};

class HuffmanTree{
public:
    HuffmanTree( priority_queue<HuffmanNode*, vector<HuffmanNode*>, NodeComparator> q){
        while (q.size() != 1){
            //когда равные частоты сложно найти минимум, возможно это неважно

            HuffmanNode* rnode = q.top();
            q.pop();
            HuffmanNode* lnode = q.top();
            q.pop();
            

            HuffmanNode* parent = createNode('\0', rnode->freq + lnode->freq);
            parent->left = lnode;
            parent->right = rnode;
            q.push(parent);
        }
        root = q.top();
        q.pop();
    }
    
    HuffmanNode* get_root();
    // void print_left_leaf(HuffmanNode* parent);
    void print_desc_leaves(HuffmanNode* parent);
    void create_code(HuffmanNode* parent, string codeword, map<char, string> &code);
    // HuffmanTree create_tree_from_code(map<char, string> code);

private:
    HuffmanNode *root;
};

#endif