#include "greedy.h"

#include <algorithm>
#include <iostream>
#include <map>
#include <stdexcept>

static void check_strings(const std::vector<std::string>& strings) {
    // Check if any of the strings is empty
    if (std::any_of(strings.begin(), strings.end(),
                    [](const std::string& str) { return str.empty(); })) {
        throw std::invalid_argument("strings cannot be empty");
    }

    // Check if any of the strings has a different size than the others
    std::size_t size_1st = strings.front().size();
    if (std::any_of(strings.begin(), strings.end(),
                    [size_1st](const std::string& str) {
                        return size_1st != str.size();
                    })) {
        throw std::invalid_argument("strings cannot be empty");
    }
}

void ffmsp::greedy(const std::vector<std::string>& strings, double threshold) {
    (void)threshold;

    check_strings(strings);

    std::size_t string_len = strings.front().size();
    std::vector<std::map<char, std::size_t>> V_j(string_len);

    for (std::size_t i = 0; i < strings.size(); ++i) {
        for (const auto& str : strings) {
            const auto cur_char = str[i];

            V_j[i][cur_char] += 1;
        }
    }
}

void ffmsp::random_greedy(const std::vector<std::string>& strings,
                          double threshold, double alpha) {
    (void)threshold;
    (void)alpha;

    check_strings(strings);
}
