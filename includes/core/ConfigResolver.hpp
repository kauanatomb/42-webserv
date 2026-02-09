#pragma once
#include "./config/AST.hpp"
#include "RuntimeConfig.hpp"

class ConfigResolver {
    public:
        static RuntimeConfig resolve(const ConfigAST& ast);
    private:
        static RuntimeServer buildServer(const ServerNode& node);
        static RuntimeLocation buildLocation(const LocationNode& node, const RuntimeServer& parent);
        static void applyServerDirectives(RuntimeServer& server, const std::vector<Directive>& directives);
        static void setDefaults(RuntimeServer& server);
        static void ApplyLocationDirectives(const Directive& dir, RuntimeLocation& loc);
};
