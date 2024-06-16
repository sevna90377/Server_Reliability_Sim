#include "Server.h"

std::string Server::info() {
    return name + "\t" + type_toString() + "\t" + std::to_string(currently) + "/" + std::to_string(capacity) + "\n";
}

std::string Server::type_toString() {
    switch (type) {
    case PvP:
        return "PvP";

    case PvE:
        return "PvE";

    case RP:
        return "RP ";
    }
    return "undefined";
}

void Server::addPlayer(Player* player) {
    current_players.emplace_back(player);
    currently++;
    //ping_calc();
}