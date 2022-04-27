#include <fstream>
#include <sstream>
#include <string.h>
#include <bitset>

#include "huffmanTree.hpp"
#include "archiver.hpp"

using namespace std;


int main(int argc, char** argv){
    char* filename = NULL;
    char* output = NULL;

    bool compress = false;
    bool decompress = false;

    for(int i = 0; i < argc; i++){
        if (string(argv[i]) == "-f" || string(argv[i]) == "--file")
            //проблемы с аргументами
            filename = argv[i+1];
        
        if (string(argv[i]) == "-o" || string(argv[i]) == "--output")
            output = argv[i+1];
        
        if (string(argv[i]) == "-c")
            compress = true;

        if (string(argv[i]) == "-u")
            decompress = true;
    }

    archiver huff;

    ifstream fs(filename, ios::out | ios::binary);
    ofstream outfs(output, ios::out | ios::binary);

    if (compress && decompress){
        cout << "Invalid arguments" << endl;
        return 1;
    } 
    
    if (!compress && !decompress){
        cout << "Invalid arguments" << endl;
        return 1;
    }

    if(compress)
        huff.encode(fs, outfs);
    if(decompress)
        huff.decode(fs ,outfs);


}