#include <fstream>
#include <sstream>
#include "archiver.hpp"
using namespace std;

string archiver::read_input_text(ifstream& fs){
    stringstream buffer;
    buffer << fs.rdbuf();
    
    return buffer.str();
}

map<char, int> archiver::create_symbols_table(string input){
    map<char, int> symbols;

    for (size_t i = 0; i < input.length(); i++)    
        symbols[input[i]]++; 

    return symbols;
}

huffman_queue archiver::create_queue_from_table(map<char, int> symbols){
    huffman_queue q;

    for (const auto& n : symbols){
        HuffmanNode* node = createNode(n.first, n.second);
        q.push(node);
    }
    return q;
};

void archiver::write_int_byte_to_file(int num, ofstream& outfs){
    string int_bin = bitset<8>(num).to_string();
    int tmp = stoi(int_bin, nullptr, 2);
    outfs.write((char*)&tmp, 1);
}

void archiver::encode(ifstream& fs, ofstream& outfs){

    string input = read_input_text(fs);

    //cout << input << endl;

    
    map<char, int> symbols = create_symbols_table(input); 

    
	    
    // for (const auto& n : symbols) 
    //     cout << n.first << " = " << n.second << "; ";
    // cout << '\n';

    // priority_queue <HuffmanNode*, vector<HuffmanNode*>, decltype(cmp)> q2(cmp);
    // for (const auto& n : symbols){
    //     HuffmanNode* node = createNode(n.first, n.second);
    //     q2.push(node);
    // }
    
    huffman_queue q = create_queue_from_table(symbols);

    huffman_queue q2 = create_queue_from_table(symbols);

    // for (const auto& n : symbols){
    //     HuffmanNode* node = createNode(n.first, n.second);
    //     q.push(node);
    // }
    
    // HuffmanNode* kek = createNode('w', 3);
    // q.push(kek);


    // while(!q2.empty()) {
    //     std::cout << q2.top()->ch << ": " << q2.top()->freq << ", ";
    //     q2.pop();
    // }
    // std::cout << '\n';

    HuffmanTree tree = HuffmanTree(q);
    // tree.print_desc_leaves(tree.get_root());

    map<char, string> code;
    tree.create_code(tree.get_root(), "", code);

    // for (const auto& n : code) 
    //     cout << n.first << " = " << n.second << "; ";
    // cout << '\n';
      
    int number_of_symbols = symbols.size();
    write_int_byte_to_file(number_of_symbols, outfs);


    for(const auto& n: symbols){
        outfs.write((char*)&n.first, 1); //записали символ в int формате
        write_int_byte_to_file(n.second, outfs);
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
    
    int padding_size = 0;

    if (buffer_.length() % 8 != 0){
        while(buffer_.length() != 8){
            buffer_ += "0";
            padding_size++;
        }

        int tmp = stoi(buffer_, nullptr, 2);
        outfs.write((char*)&tmp, 1);
        buffer_.clear();
    }
    
    write_int_byte_to_file(padding_size, outfs);

    fs.close();
    outfs.close();

}

int read_byte_from_file(std::ifstream& file) {
    int8_t val;
    file.read((char*)&val, 1);
    return val;
}

void archiver::decode(ifstream& fs, ofstream& outfs){
    fs.seekg(0, fs.end);
    int filelength = fs.tellg();
    fs.seekg(0, fs.beg);

    fs.seekg(-1, fs.end);
    int padding_size = read_byte_from_file(fs); //количество добавочных 0 encoded_message
    fs.seekg(0, fs.beg);
    // cout << length << endl;
    int number_of_symbols = read_byte_from_file(fs);
    
    
    
    // cout << padding_size << endl;
    // cout << number_of_symbols << endl;
    map<char, int> symbols;

    
    for (int i = 0; i < number_of_symbols; i++){
        int symbol_int = read_byte_from_file(fs);
        char c = symbol_int; //символ в своём int формате
        // cout << symbol_int << endl;
        // cout << c << endl;

        int symbol_freq = read_byte_from_file(fs);
        // cout << symbol_freq << endl;
        symbols[c] = symbol_freq;
    }

    // for (const auto& n : symbols) 
    //     cout << n.first << " = " << n.second << "; ";
    // cout << '\n';
    huffman_queue q = create_queue_from_table(symbols);
    HuffmanTree tree = HuffmanTree(q);

    // tree.print_desc_leaves(tree.get_root());
    int encoded_message_len = filelength - 1 - 2*number_of_symbols - 1;
    char buffer[encoded_message_len];

    fs.read(buffer, encoded_message_len);

    tree.decode_from_message(buffer, encoded_message_len, padding_size, outfs);
    
    // cout << ((buffer[2] >> 7) & 1) << ((buffer[2] >> 6) & 1) << ((buffer[2] >> 5) & 1) << ((buffer[2] >> 4) & 1);
    

}