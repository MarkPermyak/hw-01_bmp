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

TEST_CASE("Compare decoded file and original file"){
    archiver huff;

    SUBCASE("empty file"){
        huff.encode("samples/empty.txt", "samples/compressed.bin");
        huff.decode("samples/compressed.bin", "samples/decoded_original.txt");
        CHECK(exec("diff samples/empty.txt samples/decoded_original.txt") == "");
        delete_test_files();
    }

    SUBCASE("one symbol file"){
        huff.encode("samples/one.txt", "samples/compressed.bin");
        huff.decode("samples/compressed.bin", "samples/decoded_original.txt");
        CHECK(exec("diff samples/one.txt samples/decoded_original.txt") == "");
        delete_test_files();
    }
    
    SUBCASE("simple file"){
        huff.encode("samples/simple.txt", "samples/compressed.bin");
        huff.decode("samples/compressed.bin", "samples/decoded_original.txt");
        CHECK(exec("diff samples/simple.txt samples/decoded_original.txt") == "");
        delete_test_files();
    }
    
    SUBCASE("song file"){
        huff.encode("samples/song.txt", "samples/compressed.bin");
        huff.decode("samples/compressed.bin", "samples/decoded_original.txt");
        CHECK(exec("diff samples/song.txt samples/decoded_original.txt") == "");
        delete_test_files();
    }
    
    SUBCASE("russian file"){
        huff.encode("samples/russian.txt", "samples/compressed.bin");
        huff.decode("samples/compressed.bin", "samples/decoded_original.txt");
        CHECK(exec("diff samples/russian.txt samples/decoded_original.txt") == "");
        delete_test_files();
    }
    
    SUBCASE("big frequency file"){
        huff.encode("samples/bigfreq.txt", "samples/compressed.bin");
        huff.decode("samples/compressed.bin", "samples/decoded_original.txt");
        CHECK(exec("diff samples/bigfreq.txt samples/decoded_original.txt") == "");
        delete_test_files();
    }

    SUBCASE("all ascii symbols file"){
        huff.encode("samples/allascii.txt", "samples/compressed.bin");
        huff.decode("samples/compressed.bin", "samples/decoded_original.txt");
        CHECK(exec("diff samples/allascii.txt samples/decoded_original.txt") == "");
        delete_test_files();
    }

    SUBCASE("big file"){
        huff.encode("samples/big.txt", "samples/compressed.bin");
        huff.decode("samples/compressed.bin", "samples/decoded_original.txt");
        CHECK(exec("diff samples/big.txt samples/decoded_original.txt") == "");
        delete_test_files();
    }
}