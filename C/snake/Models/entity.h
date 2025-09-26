//
// Created by Marchesini Alessandro on 24/09/25.
//

#ifndef SNAKE_ENTITY_H
#define SNAKE_ENTITY_H

#include <stdbool.h>

#include "point.h"

struct entity {
    point position[100];
    int length;
} typedef entity;

void setup(entity* entity);
void add_point (entity* entity, point* next_position, point trophy_position);
void move_entity (entity* entity, point* next_position);

#endif //SNAKE_ENTITY_H
