#ifndef LOGCONVERTER_CONSOLE_INTERACTOR_H
#define LOGCONVERTER_CONSOLE_INTERACTOR_H

#include "filter_parser.h"
#include "converter.h"

namespace log_converter {

    class console_interactor {
    public:
        console_interactor(int argc, const char **argv);

        void run() const;
    private:
        void print_info() const;
        std::vector<filter> read_filters(std::ifstream& filter_stream) const;
        void convert(std::ifstream& logs_stream, converter converter_entity) const;

        const int argc;
        const char **argv;
    };
}


#endif //LOGCONVERTER_CONSOLE_INTERACTOR_H
