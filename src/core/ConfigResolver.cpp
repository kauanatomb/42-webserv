#include "core/ConfigResolver.hpp"

RuntimeConfig ConfigResolver::resolve(const ConfigAST& ast) {
    RuntimeConfig runtime;
    // create RuntimeServer for each ServerNode
    // create RuntimeLocation for eacho location{}
    // apply inherance
    // sort locations
    // build RuntimeConfig
    for(std::vector<ServerNode>::const_iterator it = ast.servers.begin(); it != ast.servers.end(); ++it) {
        RuntimeServer server = buildServer(*it);
        const std::vector<SocketKey>& listens = server.getListens();
        for(std::vector<SocketKey>::const_iterator sk = listens.begin(); sk != listens.end(); ++sk) {
            runtime.servers[*sk].push_back(server);
        }
    }
    return runtime;
}

RuntimeServer ConfigResolver::buildServer(const ServerNode& node) {
    RuntimeServer server;
    applyServerDirectives(server, node.directives);
    for(std::vector<LocationNode>::const_iterator locNode = node.locations.begin();
        locNode != node.locations.end(); ++locNode) {
            RuntimeLocation loc = buildLocation(*locNode, server);
            server.addLocation(loc);
    }
    server.sortLocations();
    return server;
}

RuntimeLocation ConfigResolver::buildLocation(const LocationNode& node, const RuntimeServer& parent) {

}
