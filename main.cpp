#include <iostream>
#include "include/filter_parser.h"
#include <fstream>

int main() {

    log_converter::filter_parser parser;

    auto filt = parser.parse_string("thread switch=%t \" | sys | thread switch hndl \" %s \" addr \" %s \" pri \" %d");

    return 0;
}
