#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

#include "args.h"
#include "greedy.h"
#include "timer.h"

#define STRING_COUNT 10

// Treat -th as -t -h (the threshold value will actually be contained in the -h
// argument)
const std::vector<Arguments::ArgDefinition> args_list{
    {'i', Arguments::ArgDefinition::STRING, false},
    {'t', Arguments::ArgDefinition::STRING, true},
    {'h', Arguments::ArgDefinition::DOUBLE, false},
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

    if (threshold > 1) {
        return 1;
    }

    const std::string instance_path = "../dataset/" + instance + ".txt";

    std::ifstream instance_file;
    instance_file.open(instance_path);

    if (!instance_file.is_open()) {
        return 1;
    }

    std::vector<std::string> strings;
    for (int i = 0; i < STRING_COUNT; i++) {
        std::string line;
        getline(instance_file, line);
        strings.push_back(line);
    }

    instance_file.close();

    const auto [det_str, det_metric] = ffmsp::greedy(strings, threshold);
    std::cout << det_metric << "\n";

    return 0;
}
