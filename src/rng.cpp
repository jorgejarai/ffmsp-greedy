#include "rng.h"

#include <random>

RNG::RNG() : m_gen(m_seed) {
}

int RNG::rand_int(int a, int b) {
    std::uniform_int_distribution<int> dist(a, b);

    return dist(m_gen);
}

double RNG::rand_real(double a, double b) {
    std::uniform_real_distribution<double> dist(a, b);

    return dist(m_gen);
}

bool RNG::rand_bool() {
    std::uniform_int_distribution<int> dist(0, 1);

    return dist(m_gen) != 0;
}
