#include "args.h"

#include <getopt.h>

#include <algorithm>
#include <stdexcept>

std::string Arguments::gen_getopt() {
    std::string ret;

    for (const auto& arg : m_def) {
        ret.push_back(arg);
        ret.push_back(':');
    }

    return ret;
}

Arguments::Arguments(const std::vector<char>& args, int argc, char* argv[])
    : m_def(args) {
    const auto opts = gen_getopt();

    int c;
    while ((c = getopt(argc, argv, opts.c_str())) != -1) {
        if (c == '?') {
            exit(1);
        }

        char arg_name = static_cast<char>(c);
        m_args[arg_name] = std::atoi(optarg);
    }
}

std::optional<int> Arguments::get(char arg) const {
    if (m_args.count(arg) == 0) {
        return {};
    }

    return m_args.at(arg);
}
