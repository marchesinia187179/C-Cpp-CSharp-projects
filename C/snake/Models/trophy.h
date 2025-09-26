//
// Created by Marchesini Alessandro on 24/09/25.
//

#ifndef SNAKE_TROPHY_H
#define SNAKE_TROPHY_H

#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "point.h"

struct trophy {
    point position;
} typedef trophy;

void set_new_trophy (trophy* trophy, point entity_position[400], int entity_length);

#endif //SNAKE_TROPHY_H