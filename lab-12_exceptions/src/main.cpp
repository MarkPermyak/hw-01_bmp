#include <iostream>

#include "matrix.hpp"

int main(){
    Registers a;

    while(std::cin){
        try{         
            std::string cmd;

            std::cin >> cmd;
            if(cmd == "exit")
                break;
            
            else if(cmd == "load"){
                std::string strreg, filename;
                std::cin >> strreg >> filename;
                
                int reg = a.get_reg(strreg);
                Matrix m = read_matrix_from_file(filename);
                a.load(m, reg);
            } 
            else if(cmd == "print"){
                std::string strreg;
                std::cin >> strreg;

                int reg = a.get_reg(strreg);
                a.print(reg);
            }
            else if(cmd == "add"){
                std::string strreg1, strreg2;
                std::cin >> strreg1 >> strreg2;

                int reg1, reg2;
                reg1 = a.get_reg(strreg1);
                reg2 = a.get_reg(strreg2);
                a.add(reg1, reg2);
            }
            else if(cmd == "mul"){
                std::string strreg1, strreg2;
                std::cin >> strreg1 >> strreg2;

                int reg1, reg2;
                reg1 = a.get_reg(strreg1);
                reg2 = a.get_reg(strreg2);
                a.mul(reg1, reg2);
            }
            else if(cmd == "elem"){
                std::string strreg;
                std::cin >> strreg;

                int reg = a.get_reg(strreg);
                int row, col;
                std::cin >> row >> col;

                a.elem(reg, row, col);
            }
        }
        catch (std::bad_alloc& e) {
            std::cout << "Unable to allocate memory." << std::endl;
            continue;
        }
        catch(const std::exception& e){
            std::cout << e.what() << '\n';
        }
    }

    return 0;
}
