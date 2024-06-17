#include "Server.h"

std::string Server::info() {
    return name + "\t" + type_toString() + "\t" + std::to_string(currently) + "/" + std::to_string(capacity) + "\n";
}

void Server::ping_calc()
{
    if (currently >= capacity) {
        joinable = false;
    }
    else if (currently < capacity) {
        joinable = true;
    }
    ping = int(currently * currently / capacity) + 5;
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

void Server::addPlayer(Player* player) 
{
    current_players.emplace_back(player);
    currently++;
    ping_calc();
}

void Server::removePlayer(Player* player)
{
    current_players.remove(player);
    currently--;
    ping_calc();
}
