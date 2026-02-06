#include "core/RuntimeServer.hpp"

std::vector<SocketKey>& RuntimeServer::getListens() { return listens; }

const std::vector<SocketKey>& RuntimeServer::getListens() const { return listens; }

void RuntimeServer::addListen(const SocketKey& key) { listens.push_back(key); }

void RuntimeServer::addServerNames(const std::vector<std::string>& names) {
    server_names.insert(server_names.end(), names.begin(), names.end());
}

void RuntimeServer::setRoot(const std::string& value) { root = value; }

void RuntimeServer::addIndex(const std::vector<std::string>& values) {
    index.insert(index.end(), values.begin(), values.end());
}

void RuntimeServer::setClientMaxBodySize(size_t value) { client_max_body_size = value; }

void RuntimeServer::addErrorPage(int status, const std::string& path) {
    error_pages[status] = path;
}

const std::vector<std::string>& RuntimeServer::getServerNames() const { 
    return server_names; 
}

const std::string& RuntimeServer::getRoot() const { return root; }

const std::vector<std::string>& RuntimeServer::getIndex() const { return index; }

size_t RuntimeServer::getClientMaxBodySize() const { return client_max_body_size; }

std::map<int, std::string>& RuntimeServer::getErrorPages() { return error_pages; }

const std::map<int, std::string>& RuntimeServer::getErrorPages() const { 
    return error_pages; 
}

void RuntimeServer::addLocation(const RuntimeLocation& loc) { locations.push_back(loc); }

void RuntimeServer::sortLocations() {} //implement