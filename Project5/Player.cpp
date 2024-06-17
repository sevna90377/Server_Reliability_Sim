#include "Player.h"
#include "Server_system.h"
#include "Normal_distribution_RNG.h"

void Player::tick() {
    if (ticks_left <= 0) {
        if (!playing) {
            join_server();
        }
        else {
            quit_server(false);
        }
    }
    calc_satisfaction();
    ticks_left--;
}

void Player::join_server() {
    std::lock_guard<std::mutex> lock(subsequent_join);
    current_server = server_system->join_server(this, closest_server);
    ticks_left = static_cast<int>(RNG::getNormal() * 10);
    if (current_server != nullptr) {
        playing = true;
    }
}

void Player::quit_server(bool forced)
{
    std::lock_guard<std::mutex> lock(subsequent_join);
    current_server->removePlayer(this);
    current_server = nullptr;
    srand(time(0));
    ticks_left = static_cast<int>(RNG::getNormal() * 10);
    playing = false;
    if (forced) {
        satisfaction = satisfaction - 0.3;
    }
}

void Player::calc_satisfaction()
{
    if (playing) {
        int ping = current_server->ping; //+ server_distance
        if (ping > ping_tolerance) {
            satisfaction = satisfaction - (ping - ping_tolerance) * 0.1;
        }
        if (satisfaction < 0.1) {
            stop();
        }
        std::cout << player_id << "\t: " << ping << "/" << ping_tolerance << "\t: " << satisfaction  << std::endl;
    }
}


void Player::start() {
    alive = true;
    closest_server = server_system->random_server();
    internet = RNG::getNormal() * 4 + 1;
    satisfaction = RNG::getNormal();
    ping_tolerance = int(RNG::getNormal() * 100 + 30);
    player_thread = std::thread(&Player::live, this);
}

void Player::stop() {
    {
        std::lock_guard<std::mutex> lock(mtx);
        alive = false;
    }
    cv.notify_all();
    if (player_thread.joinable()) {
        player_thread.join();
    }
}

void Player::live() {
    std::unique_lock<std::mutex> lock(mtx);
    while (alive) {
        cv.wait(lock, [this] {return tick_ready || !alive; });

        tick();

        tick_done = true;
        tick_ready = false;
        cv.notify_all();
    }
}

void Player::synchronise() {
    tick_ready = true;
    cv.notify_all();
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [this] {return tick_done; });
    tick_done = false;
}