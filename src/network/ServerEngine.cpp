#include "network/ServerEngine.hpp"
#include "network/RuntimeError.hpp"
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <arpa/inet.h>

ServerEngine::ServerEngine(const RuntimeConfig& config) : _config(config) {}

void ServerEngine::start() {
    createListeningSockets();
    for (size_t i = 0; i < _listeningSockets.size(); ++i) {
        pollfd pfd;
        pfd.fd = _listeningSockets[i].fd;
        pfd.events = POLLIN;
        pfd.revents = 0;
        _pollfds.push_back(pfd);
    }
    eventLoop();
}

void ServerEngine::createListeningSockets() {
    const std::map<SocketKey, std::vector<RuntimeServer> >& servers = _config.getServers();

    for (std::map<SocketKey, std::vector<RuntimeServer> >::const_iterator it = servers.begin();
            it != servers.end(); ++it) {
        setupSocket(it->first);
    }
}

void ServerEngine::setupSocket(const SocketKey& key) {
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0)
        throw RuntimeError("socket() failed");
    
    int opt = 1;
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
        throw RuntimeError("setsockopt() failed");
    
    struct sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(key.ip);
    addr.sin_port = htons(key.port);

    if (bind(fd, reinterpret_cast<struct sockaddr*>(&addr), sizeof(addr)) < 0)
        throw RuntimeError("bind() failed");
    if (listen(fd, SOMAXCONN) < 0)
        throw RuntimeError("listen() failed");
    if (fcntl(fd, F_SETFL, O_NONBLOCK) < 0)
        throw RuntimeError("fcntl O_NONBLOCK failed");

    ListeningSocket ls;
    ls.key = key;
    ls.fd = fd;
    _listeningSockets.push_back(ls);

}

void ServerEngine::eventLoop() {
    while (true) {
        int ready = poll(&_pollfds[0], _pollfds.size(), -1);
        if (ready <= 0)
            continue;
        for (size_t i = 0; i < _pollfds.size(); ++i) {
            if (_pollfds[i].revents != 0)
                handlePollEvent(i);
        }
    }
}

void ServerEngine::handlePollEvent(size_t index) {

}

void ServerEngine::acceptConnection(int serverFd) {

}

void ServerEngine::readFromConnection(int clientFd) {

}

void ServerEngine::writeToConnection(int clientFd) {

}

void ServerEngine::closeConnection(int clientFd) {

}
        

        