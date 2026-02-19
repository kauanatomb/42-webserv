#include "http/HttpResponse.hpp"
#include <sstream>

HttpResponse::HttpResponse() : status_code(200), reason_phrase("OK") {}

std::string HttpResponse::getReasonPhrase(int status) {
    switch (status) {
        case 200: return "OK";
        case 201: return "Created";
        case 204: return "No Content";
        case 301: return "Moved Permanently";
        case 302: return "Found";
        case 304: return "Not Modified";
        case 400: return "Bad Request";
        case 403: return "Forbidden";
        case 404: return "Not Found";
        case 405: return "Method Not Allowed";
        case 408: return "Request Timeout";
        case 413: return "Payload Too Large";
        case 414: return "URI Too Long";
        case 500: return "Internal Server Error";
        case 501: return "Not Implemented";
        case 502: return "Bad Gateway";
        case 503: return "Service Unavailable";
        case 505: return "HTTP Version Not Supported";
        default:  return "Unknown";
    }
}

HttpResponse HttpResponse::fromStatus(int status) {
    HttpResponse response;
    response.status_code = status;
    response.reason_phrase = getReasonPhrase(status);
    response.headers["Content-Type"] = "text/html";
    response.headers["Connection"] = "close";

    std::ostringstream oss;
    oss << "<!DOCTYPE html><html><head><title>" << status << " " 
        << response.reason_phrase << "</title></head><body><h1>" 
        << status << " " << response.reason_phrase << "</h1></body></html>";
    response.body = oss.str();

    std::ostringstream content_length;
    content_length << response.body.size();
    response.headers["Content-Length"] = content_length.str();

    return response;
}

std::string HttpResponse::serialize() const {
    std::ostringstream oss;
    oss << "HTTP/1.1 " << status_code << " " << reason_phrase << "\r\n";
    
    for (std::map<std::string, std::string>::const_iterator it = headers.begin(); 
            it != headers.end(); ++it) {
        oss << it->first << ": " << it->second << "\r\n";
    }
    oss << "\r\n" << body;
    
    return oss.str();
}
