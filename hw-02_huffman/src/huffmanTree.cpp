#include "huffmanTree.hpp"
#include "archiver.hpp"

huffmanTree::huffmanTree(huffman_queue q){
    while (q.size() != 1){
        huffmanNode* rnode = q.top();
        q.pop();
        huffmanNode* lnode = q.top();
        q.pop();
        

        huffmanNode* parent = new huffmanNode('\0', rnode->freq + lnode->freq);
        tree_size++;
        parent->left = lnode;
        parent->right = rnode;
        q.push(parent);
    }
    root = q.top();
    q.pop();
}

huffmanTree::~huffmanTree(){
    delete root;
}

huffmanNode* huffmanTree::get_root() { return root; }
 int huffmanTree::get_size() { return tree_size; }

void huffmanTree::print_desc_leaves(huffmanNode* parent){
    if(parent->left != nullptr)
        print_desc_leaves(parent->left);

    if(parent->right != nullptr)
        print_desc_leaves(parent->right);

    if(parent->left == nullptr && parent->right == nullptr)
        std::cout << parent->ch << ": " << parent->freq << std::endl;
}

void huffmanTree::create_code(huffmanNode* parent, std::string codeword, std::map<char, std::string> &code){
    //1 слева, 0 справа
    if(parent->left != nullptr)
        create_code(parent->left, codeword + "1", code);

    if(parent->right != nullptr)
        create_code(parent->right, codeword + "0", code);

    if(parent->left == nullptr && parent->right == nullptr){
        if(tree_size == 1)  // if there is only 1 node in tree
            code[parent->ch] = "0";
        else
            code[parent->ch] = codeword;
    }
        
}
int huffmanTree::decode_from_message(char* buffer, int encoded_message_len_bytes, int padding_size, std::ofstream& outfs){
    huffmanNode* node = root;

    int writed_symbols = 0;

    if(tree_size == 1){
        int pos = 0;
        int bit = 0;
        while(pos != encoded_message_len_bytes){
            if(pos == encoded_message_len_bytes - 1 && bit == byte_size - padding_size) //padding starts
                break;
            if(bit == byte_size){
                pos++;
                bit = 0;
            }
            outfs.write(&node->ch, sizeof(char));
            bit++;
            writed_symbols++;
        }
    }
    else{
        int pos = 0;
        int bit = 0;
        while(pos != encoded_message_len_bytes){
            if(pos == encoded_message_len_bytes - 1 && bit == byte_size - padding_size) //padding starts
                break;

            while(node->left || node->right){
                if(bit == byte_size){
                    pos++;
                    bit = 0;
                }
                int j_bit = (buffer[pos] >> (byte_size - 1 - bit)) & 1;
                if(j_bit == 0)
                    node = node->right;
                else   //j_bit == 1
                    node = node->left;
                bit++;
            }
            outfs.write(&node->ch, sizeof(char));
            writed_symbols++;
            node = root;
        }
    }

    return writed_symbols;
}
