#include "config/ConfigParser.hpp"
#include <iostream>

ConfigParser::ConfigParser(const std::vector<Token>& tokens)
    : _tokens(tokens), _pos(0) {}

bool ConfigParser::eof() const {
    return _pos >= _tokens.size();
}

const Token& ConfigParser::current() const {
    if (eof())
        throw SyntaxError("unexpected end of file");
    return _tokens[_pos];
}

const Token& ConfigParser::consume() {
    const Token& tok = current();
    _pos++;
    return tok;
}

void ConfigParser::expect(TokenType type, const std::string& msg) {
    if (type != current().type)
        throw SyntaxError(msg);
    consume();
}

ConfigAST ConfigParser::parse() {
    ConfigAST ast;
    while(!eof()) {
        if (current().type == WORD && current().value == "server")
            ast.servers.push_back(parseServer());
        else
            throw SyntaxError("unexpected token outside server block");
    }
    return ast;
}

ServerNode ConfigParser::parseServer() {
    ServerNode server;

    consume();
    expect(LBRACE, "expected '{' after server");
    while(!eof() && current().type != RBRACE) {
        if (current().type == WORD && current().value == "location")
            server.locations.push_back(parseLocation());
        else
            server.directives.push_back(parseDirective());
    }
    expect(RBRACE, "expected '}' to close server block");
    return server;
}

LocationNode ConfigParser::parseLocation() {
    LocationNode loc;

    consume();
    if (current().type != WORD)
        throw SyntaxError("expected path after location");
    loc.path = consume().value;
    expect(LBRACE, "expected '{' after location");
    while(!eof() && current().type != RBRACE) {
        loc.directives.push_back(parseDirective());
    }
    expect(RBRACE, "expected '}' after location");
    return loc;
}

Directive ConfigParser::parseDirective() {
    Directive dir;

    if (current().type != WORD)
        throw SyntaxError("expected directive name");
    dir.name = consume().value;
    while(!eof() && current().type == WORD) {
        dir.args.push_back(consume().value);
    }
    expect(SEMICOLON, "expected ';' after directive args");
    return dir;
}

void ConfigParser::printAST(const ConfigAST& ast) {
    for (size_t i = 0; i < ast.servers.size(); ++i) {
        const ServerNode& server = ast.servers[i];
        std::cout << "Server " << i << ":\n";
        for (size_t j = 0; j < server.directives.size(); ++j) {
            const Directive& dir = server.directives[j];
            std::cout << "  Directive: " << dir.name << " Args:";
            for (size_t k = 0; k < dir.args.size(); ++k) {
                std::cout << " " << dir.args[k];
            }
            std::cout << "\n";
        }
        for (size_t j = 0; j < server.locations.size(); ++j) {
            const LocationNode& loc = server.locations[j];
            std::cout << "  Location: " << loc.path << "\n";
            for (size_t k = 0; k < loc.directives.size(); ++k) {
                const Directive& dir = loc.directives[k];
                std::cout << "    Directive: " << dir.name << " Args:";
                for (size_t l = 0; l < dir.args.size(); ++l) {
                    std::cout << " " << dir.args[l];
                }
                std::cout << "\n";
            }
        }
    }
}