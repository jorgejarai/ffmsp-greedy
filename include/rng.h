#ifndef RNG_H
#define RNG_H

#include <random>

class RNG {
public:
    static RNG& get_instance() {
        static RNG instance;

        return instance;
    }

private:
    std::random_device m_rd;
    std::mt19937 m_gen;

    RNG();

public:
    RNG(RNG const&) = delete;
    void operator=(RNG const&) = delete;

    int rand_int(int a, int b);
    double rand_real(double a, double b);
    bool rand_bool();
};

#endif  // RNG_H
