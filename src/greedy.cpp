#include "greedy.h"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <optional>
#include <set>
#include <stdexcept>

#include "rng.h"

static const std::vector<char> ALPHABET{'A', 'C', 'G', 'T'};

// For all s ∈ src, it inserts f(s) into sink if f(s) contains a value
template <typename Src, typename Sink, typename F>
static void transform_if(Src&& src, Sink&& sink, F&& f) {
    for (auto&& x : std::forward<Src>(src)) {
        if (auto&& e = f(decltype(x)(x))) {
            *sink++ = *decltype(e)(e);
        }
    }
}

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
    // If not all the characters in the alphabet were used
    if (column.size() < ALPHABET.size()) {
        std::vector<char> used_chars;

        // Get all the used characters in the column
        std::transform(column.begin(), column.end(),
                       std::back_inserter(used_chars),
                       [](const auto& p) { return p.first; });

        // Subtract used_chars from the alphabet to get the unused characters
        std::vector<char> unused_chars;
        std::set_difference(ALPHABET.begin(), ALPHABET.end(),
                            used_chars.begin(), used_chars.end(),
                            std::back_inserter(unused_chars));

        return RNG::get_instance().rand_choose(unused_chars);
    }

    // If all the characters were used, return the least used one

    auto min_it = std::min_element(column.begin(), column.end());
    std::size_t least_common_count = min_it->second;

    std::vector<char> least_common_chars;
    transform_if(column, std::back_inserter(least_common_chars),
                 [least_common_count](const auto& pair) -> std::optional<char> {
                     return pair.second == least_common_count
                                ? std::make_optional(pair.first)
                                : std::nullopt;
                 });

    return RNG::get_instance().rand_choose(least_common_chars);
}

// Hamming distance between str1 and str2
static std::size_t d(const std::string& str1, const std::string& str2) {
    const std::size_t min_size = std::min(str1.size(), str2.size());

    std::size_t distance = 0;
    for (std::size_t i = 0; i < min_size; ++i) {
        if (str1[i] != str2[i]) {
            ++distance;
        }
    }

    return distance;
}

std::size_t calculate_metric(const std::vector<std::string>& strings,
                             const std::string& candidate,
                             std::size_t threshold_count) {
    std::size_t metric = 0;

    for (const auto& str : strings) {
        if (d(str, candidate) >= threshold_count) {
            ++metric;
        }
    }

    return metric;
}

ffmsp::result ffmsp::greedy(const std::vector<std::string>& strings,
                            double threshold) {
    return ffmsp::random_greedy(strings, threshold, 1.0);
}

ffmsp::result ffmsp::random_greedy(const std::vector<std::string>& strings,
                                   double threshold, double alpha) {
    check_strings(strings);

    std::size_t string_len = strings.front().size();
    std::vector<std::map<char, std::size_t>> V_j(string_len);

    // Build the frequency map for every character in every column
    for (std::size_t i = 0; i < strings.size(); ++i) {
        for (const auto& str : strings) {
            const auto cur_char = str[i];

            V_j[i][cur_char] += 1;
        }
    }

    std::string word;
    const std::size_t threshold_count = threshold * string_len;

    // Randomly construct the string until the threshold is reached
    for (std::size_t i = 0; i < threshold_count; ++i) {
        word.push_back(least_common_char(V_j[i]));
    }

    for (std::size_t i = threshold_count; i < string_len; ++i) {
        if (alpha != 1.0 && RNG::get_instance().rand_real(0, 1) > alpha) {
            word += RNG::get_instance().rand_choose(ALPHABET);
            continue;
        }

        // Para cada carácter c en  Σ:
        //    Generar un candidato concatenando c
        //    Calculamos cuántos strings ≥ métrica para el candidato
        //    Escogemos el candidato con mayor cantidad
        //    De no haberlo, se escoge al azar entre los empatados
        //    Como fallback, escogemos de V_j

        std::map<char, std::size_t> strings_over_threshold;

        // Calculate the metric for every possible candidate
        for (const auto& c : ALPHABET) {
            const std::string candidate = word + c;

            for (const auto& str : strings) {
                const std::size_t distance = d(candidate, str);

                if (distance >= threshold_count) {
                    strings_over_threshold[c]++;
                }
            }
        }

        // If there aren't any viable candidates, construct one with one of the
        // least used characters
        if (std::all_of(strings_over_threshold.begin(),
                        strings_over_threshold.end(),
                        [](const auto& p) { return p.second == 0; })) {
            word.push_back(least_common_char(V_j[i]));
            continue;
        }

        // Select the most used candidate (or choose one randomly if there
        // are more)
        const auto max_it = std::max_element(
            strings_over_threshold.begin(), strings_over_threshold.end(),
            [](const auto& p1, const auto& p2) {
                return p1.second < p2.second;
            });
        std::size_t most_common_count = max_it->second;

        std::vector<char> most_common_candidates;
        transform_if(
            strings_over_threshold, std::back_inserter(most_common_candidates),
            [most_common_count](const auto& pair) -> std::optional<char> {
                return pair.second == most_common_count
                           ? std::make_optional(pair.first)
                           : std::nullopt;
            });

        word.push_back(RNG::get_instance().rand_choose(most_common_candidates));
    }

    const auto metric = calculate_metric(strings, word, threshold_count);

    return {word, metric};
}
