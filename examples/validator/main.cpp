#include <iostream>
#include "Validator.h"

int main(int argc, char* argv[])
{
    Table table;

    Validator::loadInput(argv[1], table);
    Validator::exportToTga("export.tga", table);

    return 0;
}

