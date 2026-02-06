#pragma once
#include <string>
#include <vector>
#include <map>
// #include "RuntimeConfig.hpp"
#include "RuntimeLocation.hpp"

class RuntimeServer {
    private:
        std::vector<SocketKey> listens;
        std::vector<std::string> server_names;
        std::string root;
        std::vector<std::string> index;
        size_t client_max_body_size;
        std::map<int, std::string> error_pages;
        std::vector<RuntimeLocation> locations;
    public:
        std::vector<SocketKey>& getListens();
        const std::vector<SocketKey>& getListens() const;
        void addListen(const SocketKey& key);
        void addServerNames(const std::vector<std::string>& names);
        void setRoot(const std::string& value);
        void addIndex(const std::vector<std::string>& values);
        void setClientMaxBodySize(size_t value);
        void addErrorPage(int status, const std::string& path);
        const std::vector<std::string>& getServerNames() const;
        const std::string& getRoot() const;
        const std::vector<std::string>& getIndex() const;
        size_t getClientMaxBodySize() const;
        std::map<int, std::string>& getErrorPages();
        const std::map<int, std::string>& getErrorPages() const;
        void addLocation(const RuntimeLocation& loc);
        void sortLocations();
};
