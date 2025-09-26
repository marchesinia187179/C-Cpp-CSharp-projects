//
// Created by Marchesini Alessandro on 24/09/25.
//

#include "entity.h"

void setup(entity* entity) {
    entity->length = 3;
    for (int i = 0; i < 3; i++) {
        entity->position[i].row = 0;
        entity->position[i].column = i;
    }
}

void add_point (entity* entity, point* next_position, const point trophy_position) {
    int gap_row = next_position->row - entity->position[entity->length - 1].row;
    int gap_column = next_position->column - entity->position[entity->length - 1].column;

    entity->length += 1;
    entity->position[entity->length - 1].row = trophy_position.row;
    entity->position[entity->length - 1].column = trophy_position.column;

    next_position->row += gap_row;
    next_position->column += gap_column;
}

void move_entity (entity* entity, point* next_position) {
    for (int i = 0; i < entity->length - 1; i++) {
        entity->position[i].row = entity->position[i + 1].row;
        entity->position[i].column = entity->position[i + 1].column;
    }

    int gap_row = next_position->row - entity->position[entity->length - 1].row;
    int gap_column = next_position->column - entity->position[entity->length - 1].column;

    entity->position[entity->length - 1].row = next_position->row;
    entity->position[entity->length - 1].column = next_position->column;

    next_position->row += gap_row;
    next_position->column += gap_column;
}
