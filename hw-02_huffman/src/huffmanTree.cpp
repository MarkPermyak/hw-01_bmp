#include "huffmanTree.hpp"
#include "archiver.hpp"
HuffmanNode* createNode(char ch, int freq){
    
    HuffmanNode* node = new HuffmanNode(ch, freq);
    return node;
};

HuffmanTree::HuffmanTree(huffman_queue q){
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

HuffmanTree::~HuffmanTree(){
    delete root;
}

HuffmanNode* HuffmanTree::get_root() { return root; }

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
void HuffmanTree::decode_from_message(char* buffer, int encoded_message_len_bytes, int padding_size, ofstream& outfs){
    HuffmanNode* node = root;

    int pos = 0;
    int bit = 0;
    while(pos != encoded_message_len_bytes){
        if(pos == encoded_message_len_bytes - 1 && bit == 8 - padding_size) //padding starts
            break;

        while(node->left || node->right){
            if(bit == 8){
                pos++;
                bit = 0;
            }
            int j_bit = (buffer[pos] >> (7 - bit)) & 1;
            if(j_bit == 0)
                node = node->right;
            else   //j_bit == 1
                node = node->left;
            bit++;
        }
        outfs.write(&node->ch, sizeof(char));
        node = root;
    }
    //cout << endl;
}