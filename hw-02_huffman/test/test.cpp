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

TEST_CASE("Test classes"){
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

    // SUBCASE("huffman tree"){
    //     // std::map<char, int> symbols { {'a', 10}, {'s', 0}, {'d', 9}, {'f', 3}};
    //     huffmanNode* v1 = new huffmanNode('a', 9);
    //     huffmanNode* v2 = new huffmanNode('s', 239);
    //     huffmanNode* v3 = new huffmanNode('d', 35);
    //     huffmanNode* v4 = new huffmanNode('f', 10);
        
    //     huffmanQueue q;
    //     q.push(v1); q.push(v2); q.push(v3); q.push(v4);

    //     huffmanTree tree = huffmanTree(q);
    //     CHECK(tree.get_size() == 4);
    //     CHECK(tree.get_root()->ch == '\0');
    //     CHECK(tree.get_root()->freq == 293);
    //     CHECK(tree.get_root()->left == v2);
    //     CHECK(tree.get_root()->right->left == v3);

    //     std::map<char, std::string> code;
    //     REQUIRE_NOTHROW(tree.create_code(tree.get_root(), "", code));

    //     CHECK(code['a'] == "000");
    //     CHECK(code['s'] == "1");
    //     CHECK(code['d'] == "01");
    //     CHECK(code['f'] == "001");
        
    //     delete v4, v3, v2, v1;
    // }
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