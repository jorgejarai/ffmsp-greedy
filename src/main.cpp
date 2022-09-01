#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

#include "args.h"
#include "greedy.h"
#include "timer.h"

const std::vector<char> args_list{'i', 't'};

int main(int argc, char* argv[]) {
    Arguments args(args_list, argc, argv);

    const auto instance = args.get('i');
    const auto threshold = args.get('t');

    if (!instance || !threshold) {
        return 1;
    }

    if (instance == 0) {
        return 1;
    }

    ffmsp::greedy({"AATG", "CTGA", "AAAA", "AATA"}, *instance);

    return 0;
}
