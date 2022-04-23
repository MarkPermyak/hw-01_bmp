#include <iostream>
#include <map>
#include <string>

#include <functional>

#include "huffman.hpp"

using namespace std;


int main(){
    map<char, int> symbols;

    string input;
    getline(cin, input);
    for (size_t i = 0; i < input.length(); i++) 
        if(!isspace(input[i]))
	        symbols[input[i]]++; 
	    
    // for (const auto& n : symbols) 
    //     cout << n.first << " = " << n.second << "; ";
    // cout << '\n';

    
    priority_queue <HuffmanNode*, vector<HuffmanNode*>, decltype(cmp)> q(cmp);

    for (const auto& n : symbols){
        HuffmanNode* node = createNode(n.first, n.second);
        q.push(node);
    }
    
    // HuffmanNode* kek = createNode('w', 3);
    // q.push(kek);

    // while(!q.empty()) {
    //     std::cout << q.top()->ch << ": " << q.top()->freq << ", ";
    //     q.pop();
    // }
    // std::cout << '\n';

    HuffmanTree tree = HuffmanTree(q);
    tree.print_all_leaves();
}