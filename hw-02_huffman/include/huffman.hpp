#ifndef HUFFMAN_HPP_
#define HUFFMAN_HPP_

#include <iostream>
#include <queue>
using namespace std;


struct HuffmanNode
{
    HuffmanNode *left, *right;
	char ch;
	int freq;
};

HuffmanNode* createNode(char ch, int freq);

auto cmp = [](HuffmanNode* left, HuffmanNode* right) { return (left->freq < right->freq); };

class HuffmanTree{
public:
    HuffmanTree(priority_queue<HuffmanNode*, vector<HuffmanNode*>, decltype(cmp)> q){
    //int tree_size = q.size();
    // cout << q.size() << endl;
    while (q.size() != 1){
        //когда равные частоты сложно найти минимум, возможно это неважно

        HuffmanNode* rnode = q.top();
        q.pop();
        HuffmanNode* lnode = q.top();
        q.pop();

        HuffmanNode* parent = createNode(' ', rnode->freq + lnode->freq);
        parent->left = lnode;
        parent->right = rnode;
        q.push(parent);
    }
    // cout << "OK" << endl;
    root = q.top();
    q.pop();
    // cout << "OK" << endl;
}

    void print_left_leaf(HuffmanNode* parent){
        // cout << "OK" << endl;
        HuffmanNode* node = parent;
        while(node->left != nullptr)
            node = node->left;
        cout << node->ch << ": " << node->freq << endl;
    }

    void print_all_leaves(){
        HuffmanNode* node = root;
        while (node->right != nullptr){
            print_left_leaf(node);
            node = node->right;
        }
        
    }
private:
    HuffmanNode *root;
};

#endif