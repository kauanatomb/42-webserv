#include <fstream>
#include <iostream>
#include "ConfigLoader.hpp"
#include "Tokenizer.hpp"
// #include "ConfigParser.hpp"
// #include "ConfigValidator.hpp"
#include "ConfigErrors.hpp"

void ConfigLoader::load(const std::string& path) {
    if (path.empty())
        throw ConfigError("config path is empty");

    std::ifstream file(path.c_str());
    if (!file.is_open())
        throw ConfigError("cannot open config file");

    if (file.peek() == std::ifstream::traits_type::eof())
        throw ConfigError("config file is empty");

    Tokenizer tokenizer(file);
    std::vector<Token> tokens = tokenizer.tokenize();

    //print tokens for debug
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
    // ConfigParser parser(tokens);
    // ConfigAST ast = parser.parse();

    // ConfigValidator validator;
    // validator.validate(ast);

    // return ast;
}
