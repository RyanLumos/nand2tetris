#include <iostream>
#include <string>
#include <bitset>
#include <fstream>
#include <cctype>

#include "Parser.h"
#include "Code.hpp"
#include "SymbolTable.hpp"



int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Error!\n";
        return 1;
    }

    std::string inputPath = argv[1];
    size_t dotPos = inputPath.find_last_of('.');
    std::string outputPath = inputPath.substr(0, dotPos) + ".hack";
    std::ofstream outFile(outputPath);

    SymbolTable symbolTable;
    
    Parser parser1(inputPath);
    int romAddress = 0;
    while (parser1.hasMoreLines()) {
        parser1.advance();
        if (parser1.instructionType() == InstructionType::L_INSTRUCTION) {
            std::string lable = parser1.symbol();
            symbolTable.addEntry(lable, romAddress);
        }
        else {
            romAddress++;
        }
    }

    Parser parser2(inputPath);
    int ramAddress = 16;
    while (parser2.hasMoreLines()) {
        parser2.advance();
        if (parser2.instructionType() == InstructionType::A_INSTRUCTION) {
            std::string sym = parser2.symbol();
            int addr;
            if (std::isdigit(sym[0])) {
                addr = std::stoi(sym);
            }
            else if (symbolTable.contains(sym)) {
                addr = symbolTable.getAddress(sym);
            }
            else {
                symbolTable.addEntry(sym, ramAddress);
                addr = ramAddress;
                ramAddress++;
            }
            std::string bin = std::bitset<16>(addr).to_string();
            outFile << bin << "\n";
        }
        else if (parser2.instructionType() == InstructionType::C_INSTRUCTION) {
            std::string comp = parser2.comp();
            std::string dest = parser2.dest();
            std::string jump = parser2.jump();

            std::string compBin = Code::comp(comp);
            std::string destBin = Code::dest(dest);
            std::string jumpBin = Code::jump(jump);

            std::string bin = "111" + compBin + destBin + jumpBin;
            outFile << bin << "\n";
        }
    }
    outFile.close();
    std::cout << "Assembly finished successfully -> " << outputPath << "\n"; 
    return 0;
}