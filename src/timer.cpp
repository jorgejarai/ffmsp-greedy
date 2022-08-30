#include "timer.h"

Timer::Timer(double& output)
    : m_start(std::chrono::high_resolution_clock::now()), m_output(output) {
}

Timer::~Timer() {
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> diff = end - m_start;

    m_output = diff.count();
}
