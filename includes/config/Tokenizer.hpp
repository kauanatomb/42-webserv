#pragma once

#include <vector>
#include <string>
#include <istream>
#include "Token.hpp"

class Tokenizer {
public:
    explicit Tokenizer(std::istream& in);

    std::vector<Token> tokenize();

private:
    std::istream& _in;

    void skipWhitespace();
    void skipComment();
    Token readWord();
};
