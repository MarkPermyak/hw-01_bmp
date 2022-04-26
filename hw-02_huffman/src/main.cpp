#include <fstream>
#include <sstream>
#include <string.h>
#include <bitset>

#include "huffmanTree.hpp"
#include "archiver.hpp"

using namespace std;


int main(int argc, char** argv){
    
    // cout << sizeof(char_to_binary('a')) << endl;
    // cout << sizeof("01100001") << endl;
    // cout << sizeof('a') << endl;

    // // cout << char_to_binary('b') << endl;
    // // cout << char_to_binary('1') << endl;
    // // cout << char_to_binary('0') << endl;
    // // cout << char_to_binary('ы') << endl;
    // cout << string_to_binary("abcd", 0) << endl;

    char* filename = NULL;
    char* output = NULL;

    for(int i = 0; i < argc; i++){
        if (string(argv[i]) == "-f" || string(argv[i]) == "--file")
            //проблемы с аргументами
            filename = argv[i+1];
        
        if (string(argv[i]) == "-o" || string(argv[i]) == "--output")
            output = argv[i+1];
    }

    Archiver huff;
















    ifstream fs(filename);

    string input = huff.read_input_text(fs);

    cout << input << endl;

    
    map<char, int> symbols = huff.create_symbols_table(input); 

    
	    
    // for (const auto& n : symbols) 
    //     cout << n.first << " = " << n.second << "; ";
    // cout << '\n';

    // priority_queue <HuffmanNode*, vector<HuffmanNode*>, decltype(cmp)> q2(cmp);
    // for (const auto& n : symbols){
    //     HuffmanNode* node = createNode(n.first, n.second);
    //     q2.push(node);
    // }
    
    huffman_queue q = huff.create_queue_from_table(symbols);

    huffman_queue q2 = huff.create_queue_from_table(symbols);

    // for (const auto& n : symbols){
    //     HuffmanNode* node = createNode(n.first, n.second);
    //     q.push(node);
    // }
    
    // HuffmanNode* kek = createNode('w', 3);
    // q.push(kek);


    while(!q2.empty()) {
        std::cout << q2.top()->ch << ": " << q2.top()->freq << ", ";
        q2.pop();
    }
    std::cout << '\n';

    HuffmanTree tree = HuffmanTree(q);
    // tree.print_desc_leaves(tree.get_root());

    map<char, string> code;
    tree.create_code(tree.get_root(), "", code);

    for (const auto& n : code) 
        cout << n.first << " = " << n.second << "; ";
    cout << '\n';
    
    ofstream outfs(output, ios::out | ios::binary);
    
  
    string symboltable_size_bin = bitset<8>(symbols.size()).to_string();
    int tmp = stoi(symboltable_size_bin, nullptr, 2);
    outfs.write((char*)&tmp, 1);


    for(const auto& n: symbols){
        outfs.write((char*)&n.first, 1);
        int freq = n.second;
        string freq_bin = bitset<8>(freq).to_string();
        int tmp = stoi(freq_bin, nullptr, 2);
        outfs.write((char*)&tmp, 1);
    }


    int encoded_text_len = 0;
    string buffer_;

    for(size_t i = 0; i < input.length(); i++){
        string codestr = code[input[i]];
        encoded_text_len += codestr.length();
        for(size_t j = 0; j < codestr.length(); j++){
            buffer_ += codestr[j];
            // cout << buffer_ << endl;

            if(buffer_.length() == 8){
                int tmp = stoi(buffer_, nullptr, 2);
                outfs.write((char*)&tmp, 1);
                buffer_.clear();
            }
        }

    }
    
    if (buffer_.length() % 8 != 0){
        while(buffer_.length() != 8)
            buffer_ += "0";

        int tmp = stoi(buffer_, nullptr, 2);
        outfs.write((char*)&tmp, 1);
        buffer_.clear();
    }
  
    fs.close();
    outfs.close();

}