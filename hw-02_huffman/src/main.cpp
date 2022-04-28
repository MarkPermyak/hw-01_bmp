#include <string.h>

#include "huffmanTree.hpp"
#include "archiver.hpp"

int main(int argc, char** argv){
    char* input_file = NULL;
    char* output_file = NULL;

    bool compress = false;
    bool decompress = false;
    bool outarg = false;
    bool inarg = false;

    try{
        if(argc != 6)
            throw huffmanArchiverException("Invalid number of arguments");
        for(int i = 0; i < argc; i++){
            if (std::string(argv[i]) == "-f" || std::string(argv[i]) == "--file"){
                input_file = argv[i+1];
                inarg = true;
            }
            
            if (std::string(argv[i]) == "-o" || std::string(argv[i]) == "--output_file"){
                output_file = argv[i+1];
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
        
        
        
        if(compress)
            huff.encode(input_file, output_file);
        if(decompress)
            huff.decode(input_file, output_file);
        
    }
    catch(huffmanArchiverException& e){
        std::cerr << e.what() << '\n';
        return 1;
    }
    
    return 0;
}
