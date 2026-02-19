#include "http/RequestParser.hpp"
#include <iostream>
#include <sstream>

RequestParser::RequestParser() : _state(START_LINE), _error_status(0), _has_error(false) {}

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
    std::string first_line = buffer.substr(0, end_first_line);
    std::istringstream iss(first_line);
    iss >> request.method >> request.uri >> request.version;

    if (request.method.empty() || request.uri.empty() || request.version.empty()) {
        _has_error = true;
        _error_status = 400;
    }
    if (request.method != "GET" && request.method != "POST" && request.method != "DELETE") {
        _has_error = true;
        _error_status = 405;
    }
    if (request.version != "HTTP/1.0" && request.version != "HTTP/1.1") {
        _has_error = true;
        _error_status = 505;
    }
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
    if (request.headers.find("Host") == request.headers.end()) {
        _has_error = true;
        _error_status = 400;
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

bool RequestParser::getHasError() const {
    return _has_error;
}

int& RequestParser::getErrorStatus() {
    return _error_status;
}
