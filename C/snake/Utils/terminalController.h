//
// Created by Marchesini Alessandro on 24/09/25.
//

#ifndef SNAKE_TERMINALCONTROLLER_H
#define SNAKE_TERMINALCONTROLLER_H

#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include <time.h>

#include "../Models/game_data.h"

int read_without_blocking(void);
void print_game(game_data game);
void print_welcome(void);
void print_title(void);
void print_result(bool win);
void print_exit_from_welcome(void);
void print_exit_from_game(game_data game);

#endif //SNAKE_TERMINALCONTROLLER_H