cmake_minimum_required(VERSION 3.12)
project(fusion)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(fusion
        main.cpp
        fusion/core/application.cpp
        fusion/core/event.cpp fusion/core/plugin.cpp fusion/core/module.cpp fusion/modules/logger.cpp fusion/modules/thread_pool.cpp)
