#include "Tokenizer.hpp"
#include <cctype>

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