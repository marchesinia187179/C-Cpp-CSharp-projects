#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define GRID_COLS 25
#define GRID_ROWS 25
#define GRID_CELLS (GRID_ROWS * GRID_COLS)
#define ALIVE '*'
#define DEAD '.'
#define CLEAR_TERMINAL "\x1b[3J\x1b[H\x1b[2J"

int cell_to_index(int x, int y) {
    if (x < 0) {
        x = (-x) % GRID_COLS;
        x = GRID_COLS - x;
    }

    if (y < 0) {
        y = (-y) % GRID_ROWS;
        y = GRID_ROWS - y;
    }

    if (x >= GRID_COLS) x = x % GRID_COLS;
    if (y >= GRID_ROWS) y = y % GRID_ROWS;
    return y * GRID_COLS + x;
}

void set_cell(char *grid, int x, int y, char state) {
    grid[cell_to_index(x, y)] = state;
}

char get_cell(char *grid, int x, int y) {
    return grid[cell_to_index(x, y)];
}

int count_living_neighbors(char *grid, int x, int y) {
    int alive = 0;
    for (int y0 = -1; y0 <= 1; y0++) {
        for (int x0 = -1; x0 <= 1; x0++) {
            if (x0 == 0 && y0 == 0) continue;
            if (get_cell(grid, x+x0, y+y0) == ALIVE) alive++;
        }
    }
    return alive;
}

void compute_new_state(char *old, char *new) {
    for (int y = 0; y < GRID_ROWS; y++) {
        for (int x = 0; x < GRID_COLS; x++) {
            int n_alive = count_living_neighbors(old, x, y);
            char new_state = DEAD;
            if (get_cell(old, x, y) == ALIVE) {
                if (n_alive == 2 || n_alive == 3) new_state = ALIVE;
            } else {
                if (n_alive == 3) new_state = ALIVE;
            }
            set_cell(new, x, y, new_state);
        }
    }
}

void set_grid(char *grid) {
    for (int y = 0; y < GRID_ROWS; y++) {
        for (int x = 0; x < GRID_COLS; x++) {
            set_cell(grid, x, y, DEAD);
        }
    }

    int x, y;
    char answer[] = "", coordinate[] = "";
    while (1) {
        printf("Do you want to add an ALIVE cell? ('y' = yes; 'n' = no) ");
        scanf("%s", &answer[0]);
        if (strcmp(answer, "n") == 0) break;

        if (strcmp(answer, "y") != 0) {
            printf("Invalid input! Please insert 'y' or 'n' to continue.\n");
            continue;
        }

        printf("If you don't insert a valid coordinate, it will be interpreted as 0!\n");

        printf("Insert x: ");
        scanf("%s", &coordinate[0]);
        x = (int)strtol(coordinate, NULL, 10);

        printf("Insert y: ");
        scanf("%s", &coordinate[0]);
        y = (int)strtol(coordinate, NULL, 10);

        set_cell(grid, x, y, ALIVE);
    }
}

int count_population(char *grid) {
    int population = 0;
    for (int y = 0; y < GRID_ROWS; y++) {
        for (int x = 0; x < GRID_COLS; x++) {
            if (get_cell(grid, x, y) == ALIVE) {
                population++;
            }
        }
    }
    return population;
}

void print_grid(char *grid, int *generation) {
    printf(CLEAR_TERMINAL);
    for (int y = 0; y < GRID_ROWS; y++) {
        for (int x = 0; x < GRID_COLS; x++) {
            printf("%c", get_cell(grid, x, y));
        }
        printf("\n");
    }
    (*generation)++;
    printf("Generation: %d\n", *generation);
    printf("Population: %d\n", count_population(grid));
}

void print_homepage() {
    printf(CLEAR_TERMINAL);
    printf("GAME OF LIFE!\n");
    printf("----------\n");
    printf("RULES:\n");
    printf("- Any live cell with fewer than two live neighbours dies, as if by underpopulation.\n");
    printf("- Any live cell with two or three live neighbours lives on to the next generation.\n");
    printf("- Any live cell with more than three live neighbours dies, as if by overpopulation.\n");
    printf("- Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.\n");
    printf("----------\n");
}

int main(void) {
    print_homepage();
    int generation = 0;
    char old_grid[GRID_CELLS];
    char new_grid[GRID_CELLS];
    set_grid(old_grid);

    while (1) {
        compute_new_state(old_grid, new_grid);
        print_grid(new_grid, &generation);
        usleep(100000);

        compute_new_state(new_grid, old_grid);
        print_grid(old_grid, &generation);
        usleep(100000);
    }

    return 0;
}
