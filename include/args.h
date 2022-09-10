#ifndef ARGS_H
#define ARGS_H

#include <iostream>
#include <map>
#include <optional>
#include <string>
#include <type_traits>
#include <variant>
#include <vector>

class Arguments {
public:
    struct ArgDefinition {
        char symbol;
        enum { INT, DOUBLE, STRING } type;
        bool optional;
    };

private:
    std::vector<ArgDefinition> m_def;
    std::map<char, std::variant<int, double, std::string>> m_args;

    std::string gen_getopt();

public:
    Arguments(const std::vector<ArgDefinition>& args, int argc, char* argv[]);

    template <typename T,
              typename std::enable_if<!std::is_arithmetic<T>::value ||
                                          !std::is_same<T, std::string>::value,
                                      int>::type = 0>
    std::optional<T> get(char arg) const {
        if (m_args.count(arg) == 0) {
            return {};
        }

        return std::get<T>(m_args.at(arg));
    }
};

#endif  // ARGS_H
