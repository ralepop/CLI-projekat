cmake_minimum_required(VERSION 3.29)
project(CLI_projekat)

set(CMAKE_CXX_STANDARD 20)

include_directories(Funkc)
include_directories(Komande)

add_executable(CLI_projekat
        Funkc/command.cpp
        Funkc/command.h
        Funkc/commandFactory.cpp
        Funkc/commandFactory.h
        Funkc/commandInterpreter.cpp
        Funkc/commandInterpreter.h
        Komande/dateCommand.cpp
        Komande/dateCommand.h
        Komande/echoCommand.cpp
        Komande/echoCommand.h
        Komande/timeCommand.cpp
        Komande/timeCommand.h
        Komande/touchCommand.cpp
        Komande/touchCommand.h
        Komande/wcCommand.cpp
        Komande/wcCommand.h
        Komande/promptCommand.cpp
        Komande/promptCommand.h
        Komande/truncateCommand.cpp
        Komande/truncateCommand.h
        Komande/rmCommand.cpp
        Komande/rmCommand.h
        Komande/trCommand.cpp
        Komande/trCommand.h
        main.cpp)
