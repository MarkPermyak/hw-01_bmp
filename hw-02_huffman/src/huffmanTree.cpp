#include "huffmanTree.hpp"

HuffmanNode* createNode(char ch, int freq){
    
    HuffmanNode* node = new HuffmanNode();
    node->ch = ch;
    node->freq = freq;
    node->left = nullptr;
    node->right = nullptr;

    return node;
};

HuffmanNode* HuffmanTree::get_root() { return root; }

// void HuffmanTree::print_left_leaf(HuffmanNode* parent){
//     HuffmanNode* node = parent;
//     while(node->left != nullptr)
//         node = node->left;
//     cout << node->ch << ": " << node->freq << endl;
// }

void HuffmanTree::print_desc_leaves(HuffmanNode* parent){
    if(parent->left != nullptr)
        print_desc_leaves(parent->left);

    if(parent->right != nullptr)
        print_desc_leaves(parent->right);

    if(parent->left == nullptr && parent->right == nullptr)
        cout << parent->ch << ": " << parent->freq << endl;
}

void HuffmanTree::create_code(HuffmanNode* parent, string codeword, map<char, string> &code){
    //1 слева, 0 справа
    if(parent->left != nullptr)
        create_code(parent->left, codeword + "1", code);

    if(parent->right != nullptr)
        create_code(parent->right, codeword + "0", code);

    if(parent->left == nullptr && parent->right == nullptr){
        if(parent == root)  // if there is only 1 node in tree
            code[parent->ch] = "0";
        else
            code[parent->ch] = codeword;
    }
        
}

// HuffmanTree HuffmanTree::create_tree_from_code(map<char, string> code){

// }