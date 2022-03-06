#include <stdexcept>
#include "../include/filter_parser.h"

std::unique_ptr<log_converter::filter> log_converter::filter_parser::parse_string(const std::string& input) {

    auto flt = std::make_unique<filter>();

    int equal_index = -1;

    for (int i = 0; i < input.size() && equal_index == -1; i++) {

        if (input[i] == '=') {
            equal_index = i;
        }
    }

    if (equal_index == -1) {
        throw std::runtime_error("Bad string: not found equal sign!");
    }

    flt->signal_name = input.substr(0, equal_index);

    auto begin = std::string::npos;
    auto end = std::string::npos;

    for (int i = equal_index; i < input.size(); i++) {

        if (input[i] == '%') {
            flt->args.push_back(input.substr(i, 2));
        }

        if (begin != std::string::npos && end != std::string::npos) {
            flt->strings.push_back(input.substr(begin + 1, end - begin - 1));
            begin = std::string::npos;
            end = std::string::npos;
        }

        if (input[i] == '\"' && begin == std::string::npos) {
            begin = i;
        }
        else if (input[i] == '\"' && end == std::string::npos) {
            end = i;
        }
    }

    return flt;
}
