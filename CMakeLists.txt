cmake_minimum_required(VERSION 3.21)
project(LogConverter)

set(CMAKE_CXX_STANDARD 14)


add_executable(LogConverter main.cpp
                            source/filter_parser.cpp
                            include/filter_parser.h
                            source/converter.cpp
                            include/converter.h
                            source/console_interactor.cpp
                            include/console_interactor.h)
