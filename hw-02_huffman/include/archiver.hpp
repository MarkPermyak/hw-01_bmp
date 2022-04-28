#ifndef ARCHIVER_HPP_
#define ARCHIVER_HPP_

#include <bitset>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <cmath>
#include <exception>

#include "huffmanTree.hpp"

class archiver{
    public:
        void encode(std::string input_file, std::string output_file);
        void decode(std::string input_file, std::string output_file);

    private:
        const size_t byte_size = 8;

        bool is_empty(std::ifstream& fs);

        std::string read_input_text(std::ifstream& fs);
        
        std::map<char, int> create_symbols_table(std::string input);
        huffman_queue create_queue_from_table(std::map<char, int> symbols);

        void write_32int_byte_to_file(int num, std::ofstream& outfs);
        void write_8int_byte_to_file(int num, std::ofstream& outfs);
        int read_byte_from_file(std::ifstream& file);
        int read_4byte_from_file(std::ifstream& file);

};

class huffmanArchiverException : public std::exception {
    
    public:
        explicit huffmanArchiverException(const char* message)
                : what_message(message) {}

        const char* what() const noexcept override { return what_message.c_str(); }
    
    private:
        std::string what_message;
};

#endif
