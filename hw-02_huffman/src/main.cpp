#include <string.h>

#include "huffmanTree.hpp"
#include "archiver.hpp"

int main(int argc, char** argv){
    char* filename = NULL;
    char* output = NULL;

    bool compress = false;
    bool decompress = false;
    bool outarg = false;
    bool inarg = false;

    try{
        if(argc != 6)
            throw huffmanArchiverException("Invalid number of arguments");
        for(int i = 0; i < argc; i++){
            if (std::string(argv[i]) == "-f" || std::string(argv[i]) == "--file"){
                filename = argv[i+1];
                inarg = true;
            }
            
            if (std::string(argv[i]) == "-o" || std::string(argv[i]) == "--output"){
                output = argv[i+1];
                outarg = true;
            }
            
            if (std::string(argv[i]) == "-c")
                compress = true;

            if (std::string(argv[i]) == "-u")
                decompress = true;
        }

        if (!(inarg && outarg))
            throw huffmanArchiverException("Invalid arguments");

        if (compress && decompress)
            throw huffmanArchiverException("Invalid arguments");
         
        if (!compress && !decompress)
            throw huffmanArchiverException("Invalid arguments");

        archiver huff;    
        
        std::ifstream fs(filename, std::ios::out | std::ios::binary);

        if(!fs)
            throw huffmanArchiverException("Input file error");

        std::ofstream outfs(output, std::ios::out | std::ios::binary);
        
        if(!outfs)
            throw huffmanArchiverException("Output file error");
        
        if(compress)
            huff.encode(fs, outfs);
        if(decompress)
            huff.decode(fs ,outfs);
        
        fs.close();
        outfs.close();
    }
    catch(huffmanArchiverException& e){
        std::cerr << e.what() << '\n';
        return 1;
    }
    
    return 0;
}
