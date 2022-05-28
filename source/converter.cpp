#include <sstream>
#include <cstring>
#include "../include/converter.h"

using namespace log_converter;

converter::converter(std::ostream &os, const std::vector<filter>& filters)
    : _out(os), _filters(filters) {}


void log_converter::converter::convert_line(const std::string &input) {


    auto filter = find_matches(input);
    auto str = remove_substings(input, filter);
    std::istringstream str_stream(str);

    int num_args = filter.args.size();

    int num_bytes = strlen(filter.signal_name.c_str());

    write_data(&num_bytes, sizeof(int));
    write_data(filter.signal_name.c_str(), num_bytes);

    num_bytes = sizeof(int);
    write_data(&num_bytes, sizeof(int));
    write_data(&num_args, num_bytes);

    for (auto arg : filter.args) {

        if (arg == "%t") {
            float time;
            str_stream >> time;

            num_bytes = strlen(DATA_TYPES[TYPES_POSITION::FLOAT]);
            write_data(&num_bytes, sizeof(num_bytes));
            write_data(DATA_TYPES[TYPES_POSITION::FLOAT], num_bytes);

            num_bytes = sizeof(time);
            write_data(&num_bytes, sizeof(num_bytes));
            write_data(&time, num_bytes);
        }
        else if (arg == "%s") {
            std::string s;
            str_stream >> s;
        }
        else if (arg == "%d") {
            int num;
            str_stream >> num;

            num_bytes = strlen(DATA_TYPES[TYPES_POSITION::INT]);
            write_data(&num_bytes, sizeof(num_bytes));
            write_data(DATA_TYPES[TYPES_POSITION::INT], num_bytes);

            num_bytes = sizeof(num);
            write_data(&num_bytes, sizeof(num_bytes));
            write_data(&num, num_bytes);
        }
        else if (arg == "%c") {
            std::string s;

            str_stream >> s;

            num_bytes = strlen(DATA_TYPES[TYPES_POSITION::STRING]);
            write_data(&num_bytes, sizeof(num_bytes));
            write_data(DATA_TYPES[TYPES_POSITION::STRING], num_bytes);

            num_bytes = s.size();
            write_data(&num_bytes, sizeof(num_bytes));
            write_data(s.c_str(), num_bytes);
        }
    }

    char new_line = '\n';
    num_bytes = sizeof(new_line);
    write_data(&num_bytes, sizeof(num_bytes));
    write_data(&new_line, sizeof(new_line));
}

log_converter::filter converter::find_matches(const std::string &src) {

    for (auto& _filter : _filters) {
        bool is_matched = true;

        for (int j = 0; j < _filter.strings.size() && is_matched; j++) {
            if (src.find(_filter.strings[j]) == std::string::npos) {
                is_matched = false;
            }
        }

        if (is_matched) {
            return _filter;
        }
    }

    return {};
}

std::string converter::remove_substings(const std::string &src, const filter& filter) {

    std::string str = src;

    for (auto item : filter.strings) {
        str.erase(str.find(item) + 1, item.size() - 1);
    }

    return str;
}

template<class T>
void converter::write_data(const T* data, int size) {
    _out.write((const char*)data, size);
}


