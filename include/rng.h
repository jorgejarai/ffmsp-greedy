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

    template <typename T>
    typename T::value_type rand_choose(const T& options) {
        if (options.size() == 1) {
            return options[0];
        }

        auto next_candidate_index = rand_int(0, options.size() - 1);

        return options[next_candidate_index];
    }
};

#endif  // RNG_H
