#include "greedy.h"

#include <algorithm>
#include <iostream>
#include <map>
#include <stdexcept>

#include "rng.h"

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

static char least_common_char(const std::map<char, std::size_t>& column) {
    auto max_it = std::min_element(column.begin(), column.end());
    std::size_t least_common_count = max_it->second;

    std::vector<char>
        least_common_chars;  // vemos y agregamos las letras menos repetidas
    for (const auto& pair : column) {
        if (pair.second == least_common_count) {
            least_common_chars.push_back(pair.first);
        }
    }

    if (least_common_chars.size() == 1) {
        return least_common_chars[0];
    }

    auto next_char_index =  // si hay mas de uno iguales se escoge al azar
        RNG::get_instance().rand_int(0, least_common_chars.size() - 1);

    return least_common_chars[next_char_index];
}

static std::size_t d(const std::string& str1, const std::string& str2) {
    std::size_t distance = 0;
    for (std::size_t i = 0; i < str1.size(); ++i) {
        if (str1[i] != str2[i]) {
            ++distance;
        }
    }

    return distance;
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

    std::string word;
    word.push_back(least_common_char(V_j[0]));

    for (std::size_t i = 1; i < string_len; ++i) {
        // TODO: meter distancia de Hamming y lo demás
        word.push_back(least_common_char(V_j[i]));
    }

    std::cout << word << std::endl;
}

void ffmsp::random_greedy(const std::vector<std::string>& strings,
                          double threshold, double alpha) {
    (void)threshold;
    (void)alpha;

    check_strings(strings);
}
