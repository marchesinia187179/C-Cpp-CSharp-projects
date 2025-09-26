//
// Created by Marchesini Alessandro on 24/09/25.
//

#include "trophy.h"

void set_new_trophy (trophy* trophy, point entity_position[400], const int entity_length) {
    while (true) {
        srand(time(NULL));
        trophy->position.row = rand() % 10;
        trophy->position.column = rand() % 10;

        bool isNewTrophyValid = true;
        for (int i = 0; i < entity_length; i++) {
            if (trophy->position.row == entity_position[i].row
                && trophy->position.column == entity_position[i].column) {
                isNewTrophyValid = false;
            }
        }

        if (isNewTrophyValid) {
            break;
        }
    }
}

