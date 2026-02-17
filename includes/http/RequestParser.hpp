#pragma once

#include "HttpRequest.hpp"

class RequestParser {
    private:
        enum State { START_LINE, HEADERS, BODY, COMPLETE };
        State _state;
        void getFirstLine(const std::string& buffer, size_t end_first_line, HttpRequest& request);
        void getHeaders(const std::string& header_section, HttpRequest& request);
        bool getBody(size_t header_end, HttpRequest& request, std::string& buffer);
    public:
        bool parse(std::string& buffer, HttpRequest& request);
        bool isComplete() const;
        bool hasError() const;

};
