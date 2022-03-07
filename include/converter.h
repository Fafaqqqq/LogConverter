#ifndef LOGCONVERTER_CONVERTER_H
#define LOGCONVERTER_CONVERTER_H

#include "filter_parser.h"

#include <string>
#include <ostream>
#include <vector>
#include <iostream>

namespace log_converter {
    class converter {
    public: // public methods
        converter() = default;
        converter(std::ostream& os, const std::vector<log_converter::filter>& filters);

        void convert_line(const std::string& input);

    private: // private methods

        filter find_matches(const std::string& src);
        std::string remove_substings(const std::string& src, const filter& filter);

        template<class T>
        void write_data(const T* date, int size);

    private: // private members
        std::ostream& _out = std::cout;
        std::vector<filter> _filters;
    };
}


#endif //LOGCONVERTER_CONVERTER_H
