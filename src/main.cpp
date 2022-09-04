#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

#include "args.h"
#include "greedy.h"
#include "timer.h"

const std::vector<Arguments::ArgDefinition> args_list{
    {'i', Arguments::ArgDefinition::INT},
    {'t', Arguments::ArgDefinition::DOUBLE},
};

int main(int argc, char* argv[]) {
    Arguments args(args_list, argc, argv);

    const auto instance_arg = args.get<int>('i');
    const auto threshold_arg = args.get<double>('t');

    if (!instance_arg || !threshold_arg) {
        return 1;
    }

    const auto instance = instance_arg.value();
    const auto threshold = threshold_arg.value();

    ffmsp::greedy({"AATG", "CTGA", "AAAA", "AATA"}, instance);

    return 0;
}
