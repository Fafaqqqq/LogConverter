//
// Created by fafaq on 06.03.2022.
//

#ifndef LOGCONVERTER_FILTER_PARSER_H
#define LOGCONVERTER_FILTER_PARSER_H

#include <vector>
#include <string>
#include <memory>

namespace log_converter {

    struct filter {
        std::string signal_name;
        std::vector<std::string> args;
        std::vector<std::string> strings;
    };

    class filter_parser {
    public:
        std::unique_ptr<filter> parse_string(const std::string& input);
    };
}


#endif //LOGCONVERTER_FILTER_PARSER_H
