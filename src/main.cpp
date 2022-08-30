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

    const int instance = args['i'];
    const int threshold = args['t'];

    ffmsp::greedy({"AATG", "CTGA", "AAAA", "AATA"}, args['i']);

    return 0;
}
