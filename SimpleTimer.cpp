//
// Created by mac on 19/04/17.
//

#include <chrono>
#include "SimpleTimer.h"

SimpleTimer::SimpleTimer(int milliseconds) {
    std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
    endTime = now + std::chrono::milliseconds(milliseconds);
}

bool SimpleTimer::CheckTime() {
    //Timer check every 1000 milliseconds
    std::clock_t newClock = std::clock();

    auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - endTime).count();
    if(diff > 0){
        return true;
    }
    return false;
}

void SimpleTimer::Reset(int milliseconds) {
    std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
    endTime = now + std::chrono::milliseconds(milliseconds);
}
