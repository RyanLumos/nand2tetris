#pragma once
#include <string>
#include <unordered_map>

class SymbolTable {
private:
    std::unordered_map<std::string, int> table;

public:
    SymbolTable() {
        for (int i = 0; i <= 15; i++) {
            table["R" + std::to_string(i)] = i;
        }
        table["SCREEN"] = 16384;
        table["KBD"] = 24576;
        table["SP"] = 0;
        table["LCL"] = 1;
        table["ARG"] = 2;
        table["THIS"] = 3;
        table["THAT"] = 4;
    }
    void addEntry(std::string symbol, int address) {
        table[symbol] = address;
    }

    bool contains(std::string symbol) {
        return table.find(symbol) != table.end();
    }

    int getAddress(std::string symbol) {
        return table[symbol];
    }
};