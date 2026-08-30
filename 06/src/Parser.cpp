#include "Parser.h"
#include <iostream>
#include <algorithm>

Parser::Parser(const std::string& filename): file(filename), currentInstruction("") {
    if (!file.is_open()) {
        std::cerr << "file open failed\n";
    }
}

bool Parser::hasMoreLines() {
    return file.peek() != EOF;
}

std::string Parser::trim(const std::string &str) const {
    size_t first = str.find_first_not_of(" \t\r\n");
    if (first == std::string::npos) return "";
    size_t last = str.find_last_not_of(" \t\r\n"); 
    return str.substr(first, last - first + 1);
} 

std::string Parser::cleanLine(const std::string& line) const {
    std::string s = line;
    size_t commentPos = s.find("//");
    if (commentPos != std::string::npos) {
        s = s.substr(0, commentPos);
    }

    s.erase(remove(s.begin(), s.end(), ' '), s.end());
    s.erase(remove(s.begin(), s.end(), '\t'), s.end());

    return trim(s);
}

void Parser::advance() {
    std::string rawLine;
    while (std::getline(file, rawLine)) {
        std::string cleaned = cleanLine(rawLine);
        if (cleaned != "") {
            currentInstruction = cleaned;
            return;
        }
    }
    currentInstruction = "";
}

InstructionType Parser::instructionType() const {
    if (currentInstruction[0] == '@') {
        return InstructionType::A_INSTRUCTION;
    }
    else if (currentInstruction.front() == '(' && currentInstruction.back() == ')') {
        return InstructionType::L_INSTRUCTION;
    }
    else {
        return InstructionType::C_INSTRUCTION;
    }
}

std::string Parser::symbol() const {
    if (instructionType() == InstructionType::A_INSTRUCTION) {
        return currentInstruction.substr(1);
    }
    if (instructionType() == InstructionType::L_INSTRUCTION) {
        return currentInstruction.substr(1, currentInstruction.length() - 2);
    }
    return "";
}

std::string Parser::dest() const {
    size_t eqPos = currentInstruction.find('=');
    if (eqPos != std::string::npos) {
        return currentInstruction.substr(0, eqPos);
    }
    return "";
}

std::string Parser::comp() const {
    size_t eqPos = currentInstruction.find('=');
    size_t semiPos = currentInstruction.find(';');
    
    size_t start = (eqPos != std::string::npos) ? (eqPos + 1) : 0;
    
    size_t len;
    if (semiPos != std::string::npos) {
        len = semiPos - start;
    }
    else {
        len = currentInstruction.length() - start;
    }

    return currentInstruction.substr(start, len);
}

std::string Parser::jump() const {
    size_t semiPos = currentInstruction.find(';');
    if (semiPos != std::string::npos) {
        return currentInstruction.substr(semiPos + 1);
    }
    return "";
}