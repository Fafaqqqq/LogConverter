#include "../include/console_interactor.h"
#include "../include/converter.h"

#include <iostream>
#include <fstream>

using namespace log_converter;

console_interactor::console_interactor(int argc, const char **argv)
    : argc(argc), argv(argv) {}

void console_interactor::run() const {

    std::string logs_path;
    std::string bin_path;
    std::string filter_path;

    if (argc == 1) {
        std::cout << "This application was launched without arguments! Please add arguments or use \"--help\" for more info.\n";
        exit(1);
    }

    for (int i = 1; i < argc; i++) {
        if (std::string(argv[i]) == "--help") {
            print_info();
            exit(0);
        }
        else if (std::string(argv[i]) == "-f") {
            filter_path = argv[i + 1];
            i++;
        }
        else if (std::string(argv[i]) == "-o") {
            bin_path = argv[i + 1];
            i++;
        }
        else {
            logs_path = argv[i];
        }
    }

    std::ifstream logs(logs_path);
    std::ifstream filters(filter_path);
    std::ofstream out(bin_path);

    if (!logs) {
        std::cout << "Failed to open file! The file \"" + logs_path + "\"doesn`t exists.\n";
        exit(1);
    }

    if (!filters) {
        std::cout << "Failed to open file! The file \"" + filter_path + "\"doesn`t exists.\n";
        exit(1);
    }

    if (!out) {
        std::cout << "Failed to open file! The file \"" + bin_path + "\"doesn`t exists.\n";
        exit(1);
    }


    converter converter_entity(out, read_filters(filters));
    convert(logs, converter_entity);
}


void console_interactor::print_info() const {
    std::cout << "LogConverter [<log_file>] [-f <filter_file>] [-o <output_file>]\n\n";

    std::cout << "Arguments description:\n";
    std::cout << "\t <log_file>              path to source file with logs\n";
    std::cout << "\t -f <filter_file>        path to filters file\n";
    std::cout << "\t -o <output_file>        path to source file for GUI\n";
    std::cout << "\t --help                  print this message\n";
}

std::vector<filter> console_interactor::read_filters(std::ifstream &filter_stream) const {

    std::vector<filter> filters;
    filter_parser parser;

    while (!filter_stream.eof()) {
        std::string line;

        std::getline(filter_stream, line);

        try {
            filters.push_back(parser.parse_string(line));
        }
        catch (const std::exception& err) {
            std::cerr << err.what() << std::endl;
        }
    }

    return filters;
}

void console_interactor::convert(std::ifstream &logs_stream, converter converter_entity) const {

    while (!logs_stream.eof()) {
        std::string line;

        std::getline(logs_stream, line);
        converter_entity.convert_line(line);
    }
}


