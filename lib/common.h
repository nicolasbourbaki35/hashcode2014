#ifndef COMMON_H
#define COMMON_H

#include <vector>
#include <string>

using Table = std::vector< std::vector<bool> >;

struct Point {
    int x;
    int y;
};

struct Output {
    unsigned int NbInstructions;
    std::vector<std::string> instructions;
};

#endif
