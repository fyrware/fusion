cmake_minimum_required(VERSION 3.12)
project(fusion)

set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS -pthread)

include_directories(.)

add_executable(
        fusion
        main.cpp
        fusion/system/application.cpp
        fusion/system/module.cpp
        fusion/system/plugin.cpp
        fusion/modules/logger.cpp
        fusion/core/emitter.cpp
        fusion/core/observable.cpp
        fusion/core/thread_pool.cpp
        fusion/core/event.cpp)
