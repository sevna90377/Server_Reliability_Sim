#pragma once


#include <iostream>
#include <mutex>
#include <condition_variable>
#include <thread>

class Player
{
public:
    explicit Player(int i) : player_id(i) {
        alive = false;
        tick_ready = false;
        tick_done = false;
    }
    ~Player() {
        this->stop();
    }

    void start();
    void stop();
    void synchronise();

private:
    int player_id;

    void live();
    void tick();

    bool alive;

    //synchronizacja z symulacj¹
    std::thread player_thread;
    std::mutex mtx;
    std::condition_variable cv;
    bool tick_done;
    bool tick_ready;
};

