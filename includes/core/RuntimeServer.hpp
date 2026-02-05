#pragma once
#include <string>
#include "RuntimeConfig.hpp"
#include "RuntimeLocation.hpp"
#include <vector>

class RuntimeServer {
    private:
        std::vector<SocketKey> listens;
        std::vector<std::string> server_names;
        std::string root;
        std::vector<std::string> index;
        size_t client_max_body_size;
        std::map<int, std::string> error_pages;
        std::vector<RuntimeLocation> locations;
};
