//
// Created by Marchesini Alessandro on 24/09/25.
//

#include "terminalController.h"

int read_without_blocking(void) {
    struct termios original_termios, modified_termios;

    // Get terminal settings
    tcgetattr(STDIN_FILENO, &original_termios);
    modified_termios = original_termios;
    modified_termios.c_lflag &= ~(ICANON | ECHO);  // Disable canonical mode & echo
    tcsetattr(STDIN_FILENO, TCSANOW, &modified_termios);

    // Set non-blocking read
    int original_flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, original_flags | O_NONBLOCK);

    int input_char = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &original_termios);       // Restore terminal
    fcntl(STDIN_FILENO, F_SETFL, original_flags);            // Restore blocking

    return input_char;
}

void print_game(game_data game) {
    system("clear");
    print_title();
    printf("\n       Press 'w', 'a', 's', 'd' to move or 'q' to quit\n\n");
    printf("                     ");
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            bool isEntityPresent = false;
            bool isTrophyPresent = false;
            for (int k = 0; k < game.snake.length; k++) {
                if (i == game.snake.position[k].row && j == game.snake.position[k].column) {
                    printf("\u25A0");
                    isEntityPresent = true;
                }
            }

            if (i == game.apple.position.row && j == game.apple.position.column) {
                printf("*");
                isTrophyPresent = true;
            }

            if (!isEntityPresent && !isTrophyPresent) {
                printf("\u25A1");
            }

            printf(" ");
        }

        printf("\n                     ");
    }
}

void print_welcome(void) {
    system("clear");
    print_title();
    printf("\n         Press 's' to start or 'q' to quit the game\n\n");
}

void print_title(void) {
    printf("\n ________  ________   ________  ___  __    _______      \n"
       "|\\   ____\\|\\   ___  \\|\\   __  \\|\\  \\|\\  \\ |\\  ___ \\     \n"
       "\\ \\  \\___|\\ \\  \\\\ \\  \\ \\  \\|\\  \\ \\  \\/  /|\\ \\   __/|    \n"
       " \\ \\_____  \\ \\  \\\\ \\  \\ \\   __  \\ \\   ___  \\ \\  \\_|/__  \n"
       "  \\|____|\\  \\ \\  \\\\ \\  \\ \\  \\ \\  \\ \\  \\\\ \\  \\ \\  \\_|\\ \\ \n"
       "    ____\\_\\  \\ \\__\\\\ \\__\\ \\__\\ \\__\\ \\__\\\\ \\__\\ \\_______\\\n"
       "   |\\_________\\|__| \\|__|\\|__|\\|__|\\|__| \\|__|\\|_______|\n"
       "    \\|_________|                                          \n");
}

void print_result(bool win) {
    if (win) {
        printf("\n                     YOU WON THE GAME !\n\n");
    } else {
        printf("\n                     YOU LOST THE GAME !\n\n");
    }
}

void print_exit_from_welcome(void) {
    print_welcome();
    printf("\n                     YOU LEFT THE GAME !\n\n");
}

void print_exit_from_game(game_data game) {
    print_game(game);
    printf("\n                     YOU LEFT THE GAME !\n\n");
}