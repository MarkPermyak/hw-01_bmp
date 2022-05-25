#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../include/archiver.hpp"

std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

inline void delete_test_files() {
    exec("rm samples/compressed.bin");
    exec("rm samples/decoded_original.txt");
}

TEST_CASE("Test classes and methods"){
    SUBCASE("node struct"){
        huffmanNode* v1 = new huffmanNode;
        huffmanNode* v2 = new huffmanNode('k', 239);
        huffmanNode* v3 = new huffmanNode('m', 35);
        v3->left = v2;
        v3->right = v1;
        CHECK(v1->ch == '\0');
        CHECK(v1->freq == 0);
        CHECK(v1->left == nullptr);
        CHECK(v1->right == nullptr);
        CHECK(v2->ch == 'k');
        CHECK(v2->freq == 239);
        CHECK(v2->left == nullptr);
        CHECK(v2->right == nullptr);
        CHECK(v3->ch == 'm');
        CHECK(v3->freq == 35);
        CHECK(v3->left == v2);
        CHECK(v3->right == v1);
        
        nodeComparator n_cmp;
        CHECK(n_cmp(v1, v2) == 0);
        CHECK(n_cmp(v2, v3) == 1);
        CHECK(n_cmp(v2, v2) == 0);
        
        delete v3, v2, v1;
    }

    SUBCASE("huffman queue: regular"){
        archiver huff;
        
        huffmanNode* v1 = new huffmanNode('a', 3);
        huffmanNode* v2 = new huffmanNode('s', 4);
        huffmanNode* v3 = new huffmanNode('d', 5);
        huffmanNode* v4 = new huffmanNode('f', 1);
        
        huffmanQueue q1 = {};
        q1.push(v1); q1.push(v2); q1.push(v3); q1.push(v4);

        std::map<char, int> symbols { {'a', 3}, {'s', 4}, {'d', 5}, {'f', 1}};               
        huffmanQueue q2 = huff.create_queue_from_table(symbols);
        
         for (int i = 0; i < 4; i++){
                CHECK(q1.top()->freq == q2.top()->freq);
                CHECK(q1.top()->ch == q2.top()->ch);
                q1.pop();
                q2.pop();
        }
   
        delete v4, v3, v2, v1;
    }
    SUBCASE("huffman queue: one symbol"){
        archiver huff;
    
        huffmanNode* v1 = new huffmanNode('x', 6);
         
        huffmanQueue q1 = {};
        q1.push(v1);
        
        std::map<char, int> symbols { {'x', 6} };
        
        huffmanQueue q2 = huff.create_queue_from_table(symbols);
        
     
        CHECK(q1.top()->freq == q2.top()->freq);
        CHECK(q1.top()->ch == q2.top()->ch);
        q1.pop();
        q2.pop();

        delete v1;
    }

    SUBCASE("huffman tree: regular"){
        archiver huff;

        huffmanNode* v1 = new huffmanNode('a', 3);
        huffmanNode* v2 = new huffmanNode('s', 4);
        huffmanNode* v3 = new huffmanNode('d', 5);
        huffmanNode* v4 = new huffmanNode('f', 1);
        
        huffmanQueue q1 = {};
        q1.push(v1); q1.push(v2); q1.push(v3); q1.push(v4);

        huffmanTree tree(q1);
                
        CHECK(tree.get_size() == 4);
        CHECK(tree.get_root()->ch == '\0');
        CHECK(tree.get_root()->freq == 13);
        CHECK(tree.get_root()->right == v3);
        CHECK(tree.get_root()->left->right == v2);
        
        std::map<char, std::string> code;
        tree.create_code(tree.get_root(), "", code);

        CHECK(code['a'] == "111");
        CHECK(code['s'] == "10");
        CHECK(code['d'] == "0");
        CHECK(code['f'] == "110");

    }
    
    SUBCASE("archiver"){
        archiver huff;
        std::ifstream fs("samples/reading_tests/input.txt", std::ios::out | std::ios::binary);

        SUBCASE("reading bytes"){


            exec("echo hello > samples/reading_tests/input.txt");
            // hello = 01101000 01100101 01101100 01101100 01101111
            CHECK(huff.read_byte_from_file(fs) == 104); // 01101000 = 104
            CHECK(huff.read_byte_from_file(fs) == 101); // etc.
            CHECK(huff.read_byte_from_file(fs) == 108);
            CHECK(huff.read_byte_from_file(fs) == 108);
            CHECK(huff.read_byte_from_file(fs) == 111);

        }

        SUBCASE("reading 4bytes"){
            std::ifstream fs("samples/reading_tests/input.txt", std::ios::out | std::ios::binary);

            exec("echo rikimaru > samples/reading_tests/input.txt");
            // rikimaru = 01110010 01101001 01101011 01101001 01101101 01100001 01110010 01110101
            CHECK(huff.read_4byte_from_file(fs) == 1768647026);
            //1768647026 = 01101001 01101011 01101001 01110010 because write() and read() work that way
            CHECK(huff.read_4byte_from_file(fs) == 1970430317);
        }

        SUBCASE("creating symbols table"){

            std::ifstream fs("samples/reading_tests/input.txt", std::ios::out | std::ios::binary);
            exec("echo -n never gonna let you down > samples/reading_tests/input.txt");
            
            std::string input = huff.read_input_text(fs);
            CHECK(input == "never gonna let you down");

            std::map<char, int> expected{{' ', 4}, {'a', 1}, {'d', 1}, {'e', 3}, {'g', 1}, 
            {'l', 1}, {'n', 4}, {'o', 3}, {'r', 1}, {'t', 1}, {'u', 1}, {'v', 1}, {'w', 1}, {'y', 1}};
            
            std::map<char, int> symbols = huff.create_symbols_table(input);

            CHECK(symbols == expected);
        }
    }
}

TEST_CASE("Compare decoded file and original file"){
    archiver huff;
    stats compress_stats, decompress_stats;

    SUBCASE("empty file"){
        compress_stats = huff.encode("samples/empty.txt", "samples/compressed.bin");
        decompress_stats = huff.decode("samples/compressed.bin", "samples/decoded_original.txt");
        print_stats(compress_stats);
        print_stats(decompress_stats);
        CHECK(exec("diff samples/empty.txt samples/decoded_original.txt") == "");
        delete_test_files();
    }

    SUBCASE("one symbol file"){
        compress_stats = huff.encode("samples/one.txt", "samples/compressed.bin");
        decompress_stats = huff.decode("samples/compressed.bin", "samples/decoded_original.txt");
        print_stats(compress_stats);
        print_stats(decompress_stats);
        CHECK(exec("diff samples/one.txt samples/decoded_original.txt") == "");
        delete_test_files();
    }
    
    SUBCASE("simple file"){
        compress_stats = huff.encode("samples/simple.txt", "samples/compressed.bin");
        decompress_stats = huff.decode("samples/compressed.bin", "samples/decoded_original.txt");
        print_stats(compress_stats);
        print_stats(decompress_stats);
        CHECK(exec("diff samples/simple.txt samples/decoded_original.txt") == "");
        delete_test_files();
    }
    
    SUBCASE("song file"){
        compress_stats = huff.encode("samples/song.txt", "samples/compressed.bin");
        decompress_stats = huff.decode("samples/compressed.bin", "samples/decoded_original.txt");
        print_stats(compress_stats);
        print_stats(decompress_stats);
        CHECK(exec("diff samples/song.txt samples/decoded_original.txt") == "");
        delete_test_files();
    }
    
    SUBCASE("russian file"){
        compress_stats = huff.encode("samples/russian.txt", "samples/compressed.bin");
        decompress_stats = huff.decode("samples/compressed.bin", "samples/decoded_original.txt");
        print_stats(compress_stats);
        print_stats(decompress_stats);
        CHECK(exec("diff samples/russian.txt samples/decoded_original.txt") == "");
        delete_test_files();
    }
    
    SUBCASE("big frequency file"){
        compress_stats = huff.encode("samples/bigfreq.txt", "samples/compressed.bin");
        decompress_stats = huff.decode("samples/compressed.bin", "samples/decoded_original.txt");
        print_stats(compress_stats);
        print_stats(decompress_stats);
        CHECK(exec("diff samples/bigfreq.txt samples/decoded_original.txt") == "");
        delete_test_files();
    }

    SUBCASE("all ascii symbols file"){
        compress_stats = huff.encode("samples/allascii.txt", "samples/compressed.bin");
        decompress_stats = huff.decode("samples/compressed.bin", "samples/decoded_original.txt");
        print_stats(compress_stats);
        print_stats(decompress_stats);
        CHECK(exec("diff samples/allascii.txt samples/decoded_original.txt") == "");
        delete_test_files();
    }

    SUBCASE("big file"){
        compress_stats = huff.encode("samples/big.txt", "samples/compressed.bin");
        decompress_stats = huff.decode("samples/compressed.bin", "samples/decoded_original.txt");
        print_stats(compress_stats);
        print_stats(decompress_stats);
        CHECK(exec("diff samples/big.txt samples/decoded_original.txt") == "");
        delete_test_files();
    }
}
