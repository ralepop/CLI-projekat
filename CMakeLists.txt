cmake_minimum_required(VERSION 3.29)
project(CLI_projekat)

set(CMAKE_CXX_STANDARD 14)

include_directories(Funkc)
include_directories(Komande)

add_executable(CLI_projekat
    Funkc/command.h
    Funkc/command.cpp
    Funkc/commandFactory.cpp
    Funkc/commandFactory.h
    Funkc/commandInterpreter.cpp
    Funkc/commandInterpreter.h
    Funkc/functionsBase.h
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
    main.cpp)
