//
// Created by Dennis Concepción Martín on 18/10/22.
//

#include "handlers.h"

void error() {
    perror("Error: ");
    exit(EXIT_FAILURE);
}