#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

#include "args.h"
#include "greedy.h"
#include "timer.h"

const std::vector<Arguments::ArgDefinition> args_list{
    {'i', Arguments::ArgDefinition::STRING},
    {'t', Arguments::ArgDefinition::STRING},
    {'h',                                // Treat -th as -t -h
     Arguments::ArgDefinition::DOUBLE},  // (the threshold value will actually
                                         // be contained in the -h argument)
};

int main(int argc, char* argv[]) {
    Arguments args(args_list, argc, argv);

    const auto instance_arg = args.get<std::string>('i');
    const auto threshold_arg = args.get<double>('h');

    if (!instance_arg || !threshold_arg) {
        return 1;
    }

    const auto instance = instance_arg.value();
    const auto threshold = threshold_arg.value();

    ffmsp::greedy({"AATG", "CTGA", "AAAA", "AATA"}, threshold);

    return 0;
}
