#include "http/RequestParser.hpp"
#include <iostream>
#include <sstream>

bool RequestParser::parse(std::string& buffer, HttpRequest& request) {
    size_t header_end = buffer.find("\r\n\r\n");
    if (header_end == std::string::npos)
        return false;

    size_t first_line_end = buffer.find("\r\n");
    if (first_line_end == std::string::npos)
        return false;

    getFirstLine(buffer, first_line_end, request);

    _state = HEADERS;
    std::string header_section = buffer.substr(first_line_end + 2, header_end - (first_line_end + 2));
    getHeaders(header_section, request);

    if (getBody(header_end, request, buffer))
        return true;
    return false;
}

void RequestParser::getFirstLine(const std::string& buffer, size_t end_first_line, HttpRequest& request) {
    _state = START_LINE;
    std::string first_line = buffer.substr(0, end_first_line);
    std::istringstream iss(first_line);
    iss >> request.method >> request.uri >> request.version;
}

void RequestParser::getHeaders(const std::string& header_section, HttpRequest& request) {
    std::istringstream header_stream(header_section);
    std::string line;
    while (std::getline(header_stream, line)) {
        if (!line.empty() && line[line.size() - 1] == '\r')
            line.erase(line.size() - 1);
        size_t pos = line.find(':');
        if (pos == std::string::npos)
            continue;
        std::string key = line.substr(0, pos);
        std::string value = line.substr(pos + 1);
        if (!value.empty() && value[0] == ' ')
            value.erase(0, 1);
        request.headers[key] = value;
    }
}

bool RequestParser::getBody(size_t header_end, HttpRequest& request, std::string& buffer) {
    size_t body_start = header_end + 4;
    size_t content_length = request.getContentLength();
    if (buffer.size() < body_start + content_length)
        return false;
    _state = BODY;
    request.body = buffer.substr(body_start, content_length);
    _state = COMPLETE;
    buffer.erase(0, body_start + content_length);
    return true;
}

bool RequestParser::isComplete() const {
    return _state == COMPLETE;
}

bool RequestParser::hasError() const {
    return false;
}
