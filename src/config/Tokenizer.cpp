#include "config/Tokenizer.hpp"
#include <cctype>
#include <iostream>

Tokenizer::Tokenizer(std::istream& in)
    : _in(in) {}

std::vector<Token> Tokenizer::tokenize() {
    std::vector<Token> tokens;

    while (_in.good()) {
        skipWhitespace();

        if (!_in.good())
            break;

        char c = _in.peek();

        if (c == '#') {
            skipComment();
        }
        else if (c == '{') {
            _in.get();
            tokens.push_back(Token(LBRACE, "{"));
        }
        else if (c == '}') {
            _in.get();
            tokens.push_back(Token(RBRACE, "}"));
        }
        else if (c == ';') {
            _in.get();
            tokens.push_back(Token(SEMICOLON, ";"));
        }
        else {
            tokens.push_back(readWord());
        }
    }

    return tokens;
}

void Tokenizer::skipWhitespace() {
    while (_in.good() && std::isspace(_in.peek())) {
        _in.get();
    }
}

void Tokenizer::skipComment() {
    while (_in.good() && _in.get() != '\n') {
        // Skip characters until end of line
    }
}

Token Tokenizer::readWord() {
    std::string value;
    while (_in.good()) {
        char c = _in.peek();
        if (std::isspace(c) || c == '{' || c == '}' || c == ';' || c == '#') {
            break;
        }
        value += _in.get();
    }
    return Token(WORD, value);
}

void Tokenizer::printTokens(const std::vector<Token>& tokens) {
    for (size_t i = 0; i < tokens.size(); ++i) {
        const Token& token = tokens[i];
        std::string typeStr;
        switch (token.type) {
            case WORD: typeStr = "WORD"; break;
            case LBRACE: typeStr = "LBRACE"; break;
            case RBRACE: typeStr = "RBRACE"; break;
            case SEMICOLON: typeStr = "SEMICOLON"; break;
            default: typeStr = "UNKNOWN"; break;
        }
        std::cout << "Token " << i << ": Type=" << typeStr << ", Value=\"" << token.value << "\"" << std::endl;
    }
}
