#pragma once
#include <string>
#include <fstream>

enum class InstructionType {
    A_INSTRUCTION,
    C_INSTRUCTION,
    L_INSTRUCTION
};

class Parser {
private:
    std::ifstream file;
    std::string currentInstruction;
    std::string trim(const std::string &str) const;
    std::string cleanLine(const std::string& line) const;

public:
    Parser(const std::string& filename);
    bool hasMoreLines();
    void advance();
    InstructionType instructionType() const;
    std::string symbol() const;
    std::string dest() const;
    std::string comp() const;
    std::string jump() const;
};