#pragma once


#include <iostream>
#include <mutex>
#include <condition_variable>
#include <thread>
#include "Normal_distribution_RNG.h"

class Server_system;
class Server;

class Player
{
public:
    Player(int i, Server_system* server_system) : player_id(i), server_system(server_system) {
        alive = false;
        playing = false;
        tick_ready = false;
        tick_done = false;
        ticks_left = 1;
        current_server = nullptr;
        closest_server = nullptr;
        server_distance = 1;
        internet = 0;
        satisfaction = NULL;
        ping_tolerance = 0;
        PVP_preference = 0.5;
        PVE_preference = 0.5;
        RP_preference = 0.5;
    }
    ~Player() {
        this->stop();
    }

    //metody dla symulacji
    void start();
    void stop();
    void synchronise();

private:
    Server_system* server_system;
    Server* current_server;
    Server* closest_server;
    std::mutex subsequent_join;

    bool playing;
    int ticks_left;

    int player_id;
    double ping_tolerance;
    double satisfaction;
    double internet;
    int server_distance;
    double PVP_preference;
    double PVE_preference;
    double RP_preference;

    void live();    //g³ówny w¹tek
    void tick();
    void join_server();
    void quit_server(bool forced);
    void calc_satisfaction();

    bool alive;

    //synchronizacja z symulacj¹
    std::thread player_thread;
    std::mutex mtx;
    std::condition_variable cv;
    bool tick_done;
    bool tick_ready;
};

