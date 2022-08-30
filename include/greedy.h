#ifndef GREEDY_H
#define GREEDY_H

#include <string>
#include <vector>

namespace ffmsp {

void greedy(const std::vector<std::string>& strings, int threshold);
void random_greedy(const std::vector<std::string>& strings, int threshold,
                   double alpha);

};  // namespace ffmsp

#endif  // GREEDY_H
