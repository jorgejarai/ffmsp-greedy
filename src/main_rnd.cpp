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
    {'a', Arguments::ArgDefinition::DOUBLE, false},
};

int main(int argc, char* argv[]) {
    Arguments args(args_list, argc, argv);

    const auto instance_arg = args.get<std::string>('i');
    const auto threshold_arg = args.get<double>('h');
    const auto alpha_arg = args.get<double>('a');

    if (!instance_arg || !threshold_arg || !alpha_arg) {
        return 1;
    }

    const auto instance = instance_arg.value();
    const auto threshold = threshold_arg.value();
    const auto alpha = alpha_arg.value();

    if (threshold < 0 || threshold > 1 || alpha < 0 || alpha > 1) {
        return 1;
    }

    const std::string instance_path = "../dataset/" + instance + ".txt";

    std::ifstream instance_file;
    instance_file.open(instance_path);

    if (!instance_file.is_open()) {
        return 1;
    }

    std::vector<std::string> strings;
    while (!instance_file.eof()) {
        std::string line;
        getline(instance_file, line);

        if (line.empty()) {
            continue;
        }

        strings.push_back(line);
    }

    instance_file.close();

    double time;

    {
        Timer t(time);
        const auto [det_str, det_metric] =
            ffmsp::random_greedy(strings, threshold, alpha);
        std::cout << det_metric << ",";
    }

    std::cout << time << '\n';

    return 0;
}
