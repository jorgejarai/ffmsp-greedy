#include "args.h"

#include <getopt.h>

#include <algorithm>
#include <stdexcept>
#include <string>

std::string Arguments::gen_getopt() {
    std::string ret;

    for (const auto& arg : m_def) {
        ret.push_back(arg.symbol);
        ret.push_back(':');
    }

    return ret;
}

Arguments::Arguments(const std::vector<ArgDefinition>& args, int argc,
                     char* argv[])
    : m_def(args) {
    const auto opts = gen_getopt();

    int c;
    while ((c = getopt(argc, argv, opts.c_str())) != -1) {
        if (c == '?') {
            exit(1);
        }

        char arg_name = static_cast<char>(c);
        auto arg_def = std::find_if(m_def.begin(), m_def.end(),
                                    [arg_name](const ArgDefinition& def) {
                                        return def.symbol == arg_name;
                                    });

        if (arg_def == m_def.end()) {
            exit(1);
        }

        switch (arg_def->type) {
        case ArgDefinition::INT:
            m_args[arg_name] = std::stoi(optarg);
            break;
        case ArgDefinition::DOUBLE:
            m_args[arg_name] = std::stod(optarg);
            break;
        case ArgDefinition::STRING:
            m_args[arg_name] = std::string(optarg);
            break;
        default:
            m_args[arg_name] = std::stoi(optarg);
            break;
        }
    }
}
