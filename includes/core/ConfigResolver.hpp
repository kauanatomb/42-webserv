#pragma once
#include "./config/AST.hpp"
#include "RuntimeConfig.hpp"
class ConfigResolver {
    public:
        static RuntimeConfig resolve(const ConfigAST& ast);
    private:
    // helpers
};
