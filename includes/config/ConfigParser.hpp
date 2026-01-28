#pragma once

#include <vector>
#include "Token.hpp"
#include "AST.hpp"
#include "ConfigErrors.hpp"

class ConfigParser {
public:
    explicit ConfigParser(const std::vector<Token>& tokens);

    ConfigAST parse();

private:
    const std::vector<Token>& _tokens;
    size_t _pos;

    // helpers
    bool eof() const;
    const Token& current() const;
    const Token& consume();
    void expect(TokenType type, const std::string& msg);

    // grammar
    ServerNode parseServer();
    LocationNode parseLocation();
    Directive parseDirective();
};
