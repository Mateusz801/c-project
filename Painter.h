//
// Created by Mateusz on 03.01.2022.
//

#ifndef ZYGMUNTMATEUSZ_ETAP2_PAINTER_H
#define ZYGMUNTMATEUSZ_ETAP2_PAINTER_H

#include "Vehicle.h"
#include <limits>

class Painter {
    int salary = 0;

public:
    Painter() = default;

    void change_color(Vehicle &vehicle); //zmienia kolor przekazanego pojazdu

    int get_salary() const { return salary; }
};


#endif //ZYGMUNTMATEUSZ_ETAP2_PAINTER_H
