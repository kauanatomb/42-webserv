#pragma once

#include <string>
#include <map>

class HttpRequest {
    public:
        std::string method;
        std::string uri;
        std::string version;
        std::map<std::string, std::string> headers;
        std::string body;

        // Getters
        const std::string& getMethod() const;
        const std::string& getUri() const;
        const std::string& getVersion() const;
        const std::string& getBody() const;
        std::string getHeader(const std::string& key) const;
        size_t getContentLength() const;

        // Debug
        void print() const;
};
