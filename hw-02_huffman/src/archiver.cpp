#include "archiver.hpp"

void print_stats(stats& huffman_stats){
    std::cout << std::get<0>(huffman_stats) << std::endl;
    std::cout << std::get<1>(huffman_stats) << std::endl;
    std::cout << std::get<2>(huffman_stats) << std::endl;
}

bool archiver::is_empty(std::ifstream& fs){
    return fs.peek() == std::ifstream::traits_type::eof();
}

std::string archiver::read_input_text(std::ifstream& fs){
    std::stringstream buffer;
    buffer << fs.rdbuf();
    
    return buffer.str();
}

std::map<char, int> archiver::create_symbols_table(const std::string& input){
    std::map<char, int> symbols;

    for (size_t i = 0; i < input.length(); i++)    
        symbols[input[i]]++; 

    return symbols;
}

huffman_queue archiver::create_queue_from_table(std::map<char, int>& symbols){
    huffman_queue q;

    for (const auto& n : symbols){
        huffmanNode* node = new huffmanNode(n.first, n.second);
        q.push(node);
    }
    return q;
};

// void archiver::write_32int_byte_to_file(int num, std::ofstream& outfs){
//     // std::string int_bin = std::bitset<32>(num).to_string();
//     // int tmp = stoi(int_bin, nullptr, 2);
//     outfs.write((char*)&num, sizeof(uint32_t));
// }

// void archiver::write_8int_byte_to_file(int num, std::ofstream& outfs){
//     // std::string int_bin = std::bitset<8>(num).to_string();
//     // int tmp = stoi(int_bin, nullptr, 2);
//     outfs.write((char*)&num, sizeof(uint8_t));
// }

uint8_t archiver::read_byte_from_file(std::ifstream& file) {
    uint8_t val;
    file.read((char*)&val, sizeof(char));
    return val;
}

uint32_t archiver::read_4byte_from_file(std::ifstream& file) {
    uint32_t val;
    file.read((char*)&val, sizeof(int));
    return val;
}

stats archiver::encode(const std::string& input_file, const std::string& output_file){
    stats compress_stats;

    std::ifstream fs(input_file, std::ios::out | std::ios::binary);

    if(!fs)
        throw huffmanArchiverException("Input file error");

    std::ofstream outfs(output_file, std::ios::out | std::ios::binary);
    
    if(!outfs)
        throw huffmanArchiverException("Output file error");

    if (is_empty(fs)){
        // cout << 0 << endl;
        // cout << 0 << endl;
        // cout << 0 << endl;
        return compress_stats;
    } 

    std::string input = read_input_text(fs);
    
    std::map<char, int> symbols = create_symbols_table(input); 
    
    huffman_queue q = create_queue_from_table(symbols);

    huffmanTree tree = huffmanTree(q);

    std::map<char, std::string> code;
    tree.create_code(tree.get_root(), "", code);
      
    uint32_t number_of_symbols = symbols.size();

    // write_32int_byte_to_file(number_of_symbols, outfs);
    outfs.write((char*)&number_of_symbols, sizeof(uint32_t));

    for(const auto& n: symbols){
        outfs.write((char*)&n.first, sizeof(char)); //записали символ в int8 формате
        outfs.write((char*)&n.second, sizeof(uint32_t));  //записали его частоту в int32 формате
    }


    int encoded_text_len = 0;
    std::string buffer;

    for(size_t i = 0; i < input.length(); i++){
        std::string codestr = code[input[i]];
        encoded_text_len += codestr.length();
        for(size_t j = 0; j < codestr.length(); j++){
            buffer += codestr[j];

            if(buffer.length() == byte_size){
                uint8_t tmp = stoi(buffer, nullptr, 2);
                outfs.write((char*)&tmp, sizeof(uint8_t));
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

        uint8_t tmp = stoi(buffer, nullptr, 2);
        outfs.write((char*)&tmp, sizeof(uint8_t));
        buffer.clear();
    }
    
    outfs.write((char*)&padding_size, sizeof(uint8_t));   //записали padding в int8 формате

    // cout << input.size() << endl;                           //size of input file
    // cout << ceil((double)encoded_text_len / 8.0) << endl;   //size of coded message itself
    // cout << sizeof(int) + number_of_symbols * (sizeof(char) + sizeof(int)) + sizeof(char) << endl;            
    // //size of additional info(num of symbols, symbol table, padding size)

    int input_file_size = input.size();
    int coded_message_size = ceil((double)encoded_text_len / 8.0);
    int additional_data_size = sizeof(int) + number_of_symbols * (sizeof(char) + sizeof(int)) + sizeof(char);
    //num of symbols, symbol table, padding size
    compress_stats = {input_file_size, coded_message_size, additional_data_size};

    return compress_stats;
}

stats archiver::decode(const std::string& input_file, const std::string& output_file){
    stats decompress_stats;

    std::ifstream fs(input_file, std::ios::out | std::ios::binary);

    if(!fs)
        throw huffmanArchiverException("Input file error");

    std::ofstream outfs(output_file, std::ios::out | std::ios::binary);
    
    if(!outfs)
        throw huffmanArchiverException("Output file error");

    if (is_empty(fs)){
        // cout << 0 << endl;
        // cout << 0 << endl;
        // cout << 0 << endl;
        return decompress_stats;
    } 

    fs.seekg(0, fs.end);
    int filelength = fs.tellg();
    fs.seekg(0, fs.beg);

    fs.seekg(-1, fs.end);
    uint8_t padding_size = read_byte_from_file(fs); //количество добавочных 0 в последнем байте encoded_message
    fs.seekg(0, fs.beg);

    uint32_t number_of_symbols = read_4byte_from_file(fs);
        
    std::map<char, int> symbols;

    
    for (uint32_t i = 0; i < number_of_symbols; i++){
        uint8_t symbol_int = read_byte_from_file(fs);
        char c = symbol_int;                    //символ в своём int8 формате

        uint32_t symbol_freq = read_4byte_from_file(fs);
        symbols[c] = symbol_freq;
    }

    huffman_queue q = create_queue_from_table(symbols);
    huffmanTree tree = huffmanTree(q);

    int encoded_message_len_bytes = filelength - (sizeof(int) + number_of_symbols * (sizeof(char) + sizeof(int)) + sizeof(char));
    //1 byte for number of symbols, 2*number_of_symbols bytes for table, 1 byte for padding size

    char buffer[encoded_message_len_bytes];

    fs.read(buffer, encoded_message_len_bytes);

    int writed_symbols = tree.decode_from_message(buffer, encoded_message_len_bytes, padding_size, outfs);

    // cout << encoded_message_len_bytes << endl;
    // cout << writed_symbols << endl;
    // cout << sizeof(int) + number_of_symbols * (sizeof(char) + sizeof(int)) + sizeof(char) << endl;
    int additional_data_size = sizeof(int) + number_of_symbols * (sizeof(char) + sizeof(int)) + sizeof(char);

    decompress_stats = {encoded_message_len_bytes, writed_symbols, additional_data_size};

    return decompress_stats;
}
