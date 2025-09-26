//
// Created by Marchesini Alessandro on 24/09/25.
//

#ifndef SNAKE_GAME_DATA_H
#define SNAKE_GAME_DATA_H

#include <time.h>

#include "entity.h"
#include "trophy.h"
#include "point.h"

struct game_data {
    entity snake;
    trophy apple;
    int move;
    clock_t time;
    point next_position;
} typedef game_data;

void set_game_data(game_data* game);
void upload_next_position(game_data* game);
bool is_entity_on_trophy(game_data game);
bool is_entity_crashed (game_data game);
bool are_all_points_filled (game_data game);
bool is_fps_time(game_data* game);

#endif //SNAKE_GAME_DATA_H