cmake_minimum_required(VERSION 4.0)
project(snake C)

set(CMAKE_C_STANDARD 11)

add_executable(snake main.c
        Utils/terminalController.c
        Utils/terminalController.h
        Models/entity.c
        Models/entity.h
        Models/game_data.c
        Models/game_data.h
        Models/point.c
        Models/point.h
        Models/trophy.c
        Models/trophy.h)
