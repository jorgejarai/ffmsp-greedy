#ifndef TIMER_H
#define TIMER_H

#include <chrono>

class Timer {
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_start;

    double& m_output;

public:
    explicit Timer(double& output);
    ~Timer();
};

#endif  // TIMER_H
