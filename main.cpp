#include <iostream>
#include <sstream>
#include <cstring>
#include <fstream>
#include "include/filter_parser.h"
#include "include/converter.h"

int main() {

    log_converter::filter_parser parser;


    auto filt = parser.parse_string("thread switch=%t \" | sys | thread switch hndl \" %s \" addr \" %s \" pri \" %d");
    auto filt1 = parser.parse_string("write=%t \" | pextgt | write \" %c");

    std::vector<log_converter::filter> v;
    v.push_back(std::move(filt));
    v.push_back(std::move(filt1));

    std::ofstream out("../debug.bin", std::ios::binary);

    log_converter::converter con(out, v);



    con.convert_line("00316.943596 | pextgt | write --");

    out.close();

    std::ifstream in("../debug.bin", std::ios::binary);

    int num_bytes;

    in.read((char*)&num_bytes, sizeof(int));

    char* buf = new char[num_bytes];
    in.read(buf, num_bytes);

    std::string s(buf);
    int num_args;

    in.read((char*)&num_bytes, sizeof(int));
    in.read((char*)&num_args, num_bytes);

    float time;
    in.read((char*)&num_bytes, sizeof(int));
    in.read((char*)&time, num_bytes);

    return 0;
}
