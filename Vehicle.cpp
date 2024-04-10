//
// Created by Mateusz on 20.12.2021.
//

#include "Vehicle.h"

std::string Vehicle::colors[10] = {"black", "red", "blue", "purple", "orange", "green", "magenta", "pink", "white", "grey"};

Vehicle::Vehicle() {
    color = what_color();
}

std::string Vehicle::what_color() {
    return colors[rand() % 10];
}