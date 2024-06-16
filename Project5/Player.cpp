#include "Player.h"

void Player::tick() {
    /*
     * What can the player do every tick?
     * - join server - if not already playing
     * - quit server
     * - gain satisfaction
     */
}

void Player::start() {
    alive = true;
    player_thread = std::thread(&Player::live, this);
}

void Player::stop() {
    {
        std::lock_guard<std::mutex> lock(mtx);
        alive = false;
        cv.notify_all();
    }
    player_thread.join();
}

void Player::live() {
    std::unique_lock<std::mutex> lock(mtx);
    while (alive) {
        cv.wait(lock, [this] {return tick_ready; });
        if (!alive) break;

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