#include "./Utils/terminalController.h"
#include "./Models/entity.h"
#include "./Models/game_data.h"
#include "./Models/trophy.h"

int main(int argc, char *argv[]) {
    game_data game;
    set_game_data(&game);

    print_welcome();
    while (true) {
        int ch = read_without_blocking();
        if (ch == 'q') {
            print_exit_from_welcome();
            return 0;
        }

        if (ch == 's') {
            break;
        }
    }

    while (true) {
        game.move = read_without_blocking();
        if (game.move != EOF) {
            if (game.move == 'q') {
                print_exit_from_game(game);
                return 0;
            }

            upload_next_position(&game);
        }

        if (is_fps_time(&game)) {
            if (is_entity_on_trophy(game)) {
                add_point(&game.snake, &game.next_position, game.apple.position);
                set_new_trophy(&game.apple, game.snake.position, game.snake.length);
            } else {
                move_entity(&game.snake, &game.next_position);
            }

            if (is_entity_crashed(game)) {
                break;
            }

            print_game(game);
        }
    }

    print_result(are_all_points_filled(game));
    return 0;
}