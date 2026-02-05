#pragma once
#include "RuntimeServer.hpp"
#include <map>

struct SocketKey {
    uint32_t ip;
    uint16_t port;
};

struct RuntimeConfig {
    std::map<SocketKey, std::vector<RuntimeServer>> servers;
};

enum HttpMethod {
    GET,
    POST,
    DELETE
};

struct ReturnRule {
    int status_code;
    std::string target;
};
