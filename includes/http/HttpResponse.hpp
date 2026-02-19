#pragma once
#include <string>
#include <map>

class HttpResponse {
    public:
        int status_code;
        std::string reason_phrase;
        std::map<std::string, std::string> headers;
        std::string body;

        HttpResponse();
        std::string serialize() const;
        static HttpResponse fromStatus(int status);
    
    private:
        static std::string getReasonPhrase(int status);
};
