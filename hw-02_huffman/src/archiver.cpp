#include "archiver.hpp"

using namespace std;

bool archiver::is_empty(ifstream& fs){
    return fs.peek() == ifstream::traits_type::eof();
}

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
        huffmanNode* node = new huffmanNode(n.first, n.second);
        q.push(node);
    }
    return q;
};

void archiver::write_32int_byte_to_file(int num, ofstream& outfs){
    string int_bin = bitset<32>(num).to_string();
    int tmp = stoi(int_bin, nullptr, 2);
    outfs.write((char*)&tmp, sizeof(int));
}

void archiver::write_8int_byte_to_file(int num, ofstream& outfs){
    string int_bin = bitset<8>(num).to_string();
    int tmp = stoi(int_bin, nullptr, 2);
    outfs.write((char*)&tmp, sizeof(char));
}

int archiver::read_byte_from_file(std::ifstream& file) {
    int8_t val;
    file.read((char*)&val, sizeof(char));
    return val;
}

int archiver::read_4byte_from_file(std::ifstream& file) {
    int32_t val;
    file.read((char*)&val, sizeof(int));
    return val;
}

void archiver::encode(std::string input_file, std::string output_file){
    std::ifstream fs(input_file, std::ios::out | std::ios::binary);

    if(!fs)
        throw huffmanArchiverException("Input file error");

    std::ofstream outfs(output_file, std::ios::out | std::ios::binary);
    
    if(!outfs)
        throw huffmanArchiverException("Output file error");

    if (is_empty(fs)){
        cout << 0 << endl;
        cout << 0 << endl;
        cout << 0 << endl;
        return;
    } 

    string input = read_input_text(fs);
    
    map<char, int> symbols = create_symbols_table(input); 
    
	    
    // for (const auto& n : symbols) 
    //     cout << n.first << " = " << n.second << "; ";
    // cout << '\n';

    
    huffman_queue q = create_queue_from_table(symbols);

    // huffman_queue q2 = create_queue_from_table(symbols);

    // for (const auto& n : symbols){
    //     huffmanNode* node = createNode(n.first, n.second);
    //     q.push(node);
    // }
    


    // while(!q2.empty()) {
    //     std::cout << q2.top()->ch << ": " << q2.top()->freq << ", ";
    //     q2.pop();
    // }
    // std::cout << '\n';

    huffmanTree tree = huffmanTree(q);

    map<char, string> code;
    tree.create_code(tree.get_root(), "", code);

    // for (const auto& n : code) 
    //     cout << n.first << " = " << n.second << "; ";
    // cout << '\n';
      
    int number_of_symbols = symbols.size();
    // int number_of_symbols = 1025;

    write_32int_byte_to_file(number_of_symbols, outfs);


    for(const auto& n: symbols){
        outfs.write((char*)&n.first, sizeof(char)); //записали символ в int формате
        write_32int_byte_to_file(n.second, outfs);
    }


    int encoded_text_len = 0;
    string buffer;

    for(size_t i = 0; i < input.length(); i++){
        string codestr = code[input[i]];
        encoded_text_len += codestr.length();
        for(size_t j = 0; j < codestr.length(); j++){
            buffer += codestr[j];

            if(buffer.length() == byte_size){
                int tmp = stoi(buffer, nullptr, 2);
                outfs.write((char*)&tmp, sizeof(char));
                buffer.clear();
            }
        }

    }
    
    int padding_size = 0;

    if (buffer.length() % byte_size != 0){
        while(buffer.length() != byte_size){
            buffer += "0";
            padding_size++;
        }

        int tmp = stoi(buffer, nullptr, 2);
        outfs.write((char*)&tmp, sizeof(char));
        buffer.clear();
    }
    
    write_8int_byte_to_file(padding_size, outfs);

    cout << input.size() << endl;                           //size of input file
    cout << ceil((double)encoded_text_len / 8.0) << endl;   //size of coded message itself
    cout << sizeof(int) + number_of_symbols * (sizeof(char) + sizeof(int)) + sizeof(char) << endl;            
    //size of additional info(num of symbols, symbol table, padding size)
                                                            
    fs.close();
    outfs.close();
}

void archiver::decode(std::string input_file, std::string output_file){
    std::ifstream fs(input_file, std::ios::out | std::ios::binary);

    if(!fs)
        throw huffmanArchiverException("Input file error");

    std::ofstream outfs(output_file, std::ios::out | std::ios::binary);
    
    if(!outfs)
        throw huffmanArchiverException("Output file error");

    if (is_empty(fs)){
        cout << 0 << endl;
        cout << 0 << endl;
        cout << 0 << endl;
        return;
    } 

    fs.seekg(0, fs.end);
    int filelength = fs.tellg();
    fs.seekg(0, fs.beg);

    fs.seekg(-1, fs.end);
    int padding_size = read_byte_from_file(fs); //количество добавочных 0 encoded_message
    fs.seekg(0, fs.beg);

    int number_of_symbols = read_4byte_from_file(fs);
            
    //cout << filelength << endl;
    //cout << padding_size << endl;
    // cout << number_of_symbols << endl;
    map<char, int> symbols;

    
    for (int i = 0; i < number_of_symbols; i++){
        int symbol_int = read_byte_from_file(fs);
        char c = symbol_int; //символ в своём int формате

        int symbol_freq = read_4byte_from_file(fs);
        symbols[c] = symbol_freq;
    }

    // for (const auto& n : symbols) 
    //     cout << n.first << " = " << n.second << "; ";
    // cout << '\n';

    huffman_queue q = create_queue_from_table(symbols);
    huffmanTree tree = huffmanTree(q);

    int encoded_message_len_bytes = filelength - (sizeof(int) + number_of_symbols * (sizeof(char) + sizeof(int)) + sizeof(char));
    //1 byte for number of symbols, 2*number_of_symbols bytes for table, 1 byte for padding size

    char buffer[encoded_message_len_bytes];

    fs.read(buffer, encoded_message_len_bytes);

    int writed_symbols = tree.decode_from_message(buffer, encoded_message_len_bytes, padding_size, outfs);

    cout << encoded_message_len_bytes << endl;
    cout << writed_symbols << endl;
    cout << sizeof(int) + number_of_symbols * (sizeof(char) + sizeof(int)) + sizeof(char) << endl;
    
    fs.close();
    outfs.close();
}
