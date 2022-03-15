#include <iostream>
#include <fstream>

#include "include/filter_parser.h"
#include "include/converter.h"
#include "include/console_interactor.h"

int main(int argc, char** argv) {

    log_converter::console_interactor interactor(argc, (const char**)argv);

    interactor.run();

    return 0;
}
