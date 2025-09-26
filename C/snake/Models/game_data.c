//
// Created by Marchesini Alessandro on 24/09/25.
//

#include "game_data.h"

void set_game_data(game_data* game) {
    setup(&game->snake);
    set_new_trophy(&game->apple, game->snake.position, game->snake.length);
    game->time = clock();
    game->next_position.row = game->snake.position[game->snake.length - 1].row;
    game->next_position.column = game->snake.position[game->snake.length - 1].column + 1;
}

void upload_next_position(game_data* game) {
    switch (game->move) {
        case 'w':   //up
            if (game->next_position.column != game->snake.position[game->snake.length - 1].column) {
                game->next_position.row = game->snake.position[game->snake.length - 1].row - 1;
                game->next_position.column = game->snake.position[game->snake.length - 1].column;
            }
            break;
        case 's':   //down
            if (game->next_position.column != game->snake.position[game->snake.length - 1].column) {
                game->next_position.row = game->snake.position[game->snake.length - 1].row + 1;
                game->next_position.column = game->snake.position[game->snake.length - 1].column;
            }
            break;
        case 'd':   //right
            if (game->next_position.row != game->snake.position[game->snake.length - 1].row) {
                game->next_position.row = game->snake.position[game->snake.length - 1].row;
                game->next_position.column = game->snake.position[game->snake.length - 1].column + 1;
            }
            break;
        case 'a':   //left
            if (game->next_position.row != game->snake.position[game->snake.length - 1].row) {
                game->next_position.row = game->snake.position[game->snake.length - 1].row;
                game->next_position.column = game->snake.position[game->snake.length - 1].column - 1;
            }
            break;
        default: break;
    }
}

bool is_entity_on_trophy(game_data game) {
    return game.next_position.row == game.apple.position.row
    && game.next_position.column == game.apple.position.column;
}

bool is_entity_crashed (game_data game) {
    //check if the entity is out of bounds
    if (game.snake.position[game.snake.length - 1].row == 10
        || game.snake.position[game.snake.length - 1].column == 10) {
        return true;
        }

    if (game.snake.position[game.snake.length - 1].row < 0
        || game.snake.position[game.snake.length - 1].column < 0) {
        return true;
        }

    //check if the entity crashed with itself
    for (int i = 0; i < game.snake.length; i++) {
        for (int j = i+1; j < game.snake.length; j++) {
            if (game.snake.position[i].row == game.snake.position[j].row
                && game.snake.position[i].column == game.snake.position[j].column) {
                return true;
                }
        }
    }

    return false;
}

bool are_all_points_filled (game_data game) {
    bool is_empty_point_present = false;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            for (int k = 0; k < game.snake.length; k++) {
                if (game.snake.position[k].row != i && game.snake.position[k].column != j) {
                    is_empty_point_present = true;
                }
            }
        }
    }
    return !is_empty_point_present;
}

bool is_fps_time(game_data* game) {
    if ((double) (clock() - game->time) / CLOCKS_PER_SEC * 1000.0 >= 400) {
        game->time = clock();
        return true;
    }

    return false;
}