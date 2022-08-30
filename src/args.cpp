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
    m_args.clear();

    const auto opts = gen_getopt();

    int c;
    while ((c = getopt(argc, argv, opts.c_str())) != -1) {
        if (c == '?') {
            exit(-1);
        }

        char arg_name = static_cast<char>(c);
        m_args[arg_name] = std::atoi(optarg);
    }
}

int Arguments::operator[](char arg) const {
    return get(arg);
}

int Arguments::get(char arg) const {
    // TODO: check if value does not exist
    return m_args.at(arg);
}
