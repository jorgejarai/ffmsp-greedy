#ifndef GREEDY_H
#define GREEDY_H

#include <string>
#include <vector>

namespace ffmsp {

struct result {
    std::string str;
    std::size_t metric;
};

result greedy(const std::vector<std::string>& strings, double threshold);
result random_greedy(const std::vector<std::string>& strings, double threshold,
                     double alpha);

};  // namespace ffmsp

#endif  // GREEDY_H
