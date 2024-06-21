cmake_minimum_required(VERSION 3.5)

project(shell LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(shell
    varlib.h
    smsh.h
    execute.cpp
    process.cpp
    splitline.cpp
    varlib.cpp
    controlflow.cpp
    builtin.cpp
    main.cpp
)

install(TARGETS shell
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
