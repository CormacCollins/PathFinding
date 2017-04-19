//
// Created by mac on 19/04/17.
//

#ifndef PATHFINDING_SIMPLETIMER_H
#define PATHFINDING_SIMPLETIMER_H


//Simple synchronous timer instantiated with time length
//Can be checked if timer has elapsed through CheckTime function
class SimpleTimer {
private:
    std::chrono::time_point<std::chrono::system_clock> endTime;
public:
    SimpleTimer(int milliseconds);
    void Reset(int milliseconds);
    bool CheckTime();
};


#endif //PATHFINDING_SIMPLETIMER_H
