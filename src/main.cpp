#include <chrono>
#include <iostream>
#include <thread>
#include <vector>
#include <fstream>
#include <string>

#include "args.h"
#include "greedy.h"
#include "timer.h"

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
    std::ifstream myfile;
    std::string directory;
    

    if (!instance_arg || !threshold_arg) {
        return 1;
    }

    const auto instance = instance_arg.value();
    const auto threshold = threshold_arg.value();

    if (threshold > 1) {
        return 1;
    }
    std::string line;
    
    directory = "FFMS_all_instances/" + instance + ".txt";
    myfile.open(directory);
    std::vector<std::string> strings;
    if (myfile.is_open())
    {
        for (int i = 0; i < 10; i++)
        {
            getline(myfile, line);
            strings.push_back(line);
        }
        myfile.close();
    }
    
    for (size_t i = 0; i < strings.size(); i++)
    {
        std::cout << strings.at(i) << std::endl;
    }
    
    /*
    const auto [det_str, det_metric] =
        ffmsp::greedy({"AATG", "CTGA", "AAAA", "AATA"}, threshold);
    const auto [rnd_str, rnd_metric] =
        ffmsp::greedy({"AATG", "CTGA", "AAAA", "AATA"}, threshold);

    std::cout << det_str << " (" << det_metric << ")\n";

    std::cout << rnd_str << " (" << rnd_metric << ")\n";
    */
    return 0;
}
