//
// Created by Mateusz on 20.12.2021.
//

#ifndef ZYGMUNTMATEUSZ_ETAP2_VEHICLE_H
#define ZYGMUNTMATEUSZ_ETAP2_VEHICLE_H

#include <iostream>
#include <string>

class Vehicle {
protected:
    float price = 0;
    float capacity = 0;
    std::string color;
    float km_counter = 0;

public:
    Vehicle();

    virtual ~Vehicle() = default;

    virtual void drive() = 0;

private:
    friend class Painter;
    //udostępnienie składników klasie Painter

    friend class Dealer;
    //analogicznie

    static std::string colors[10];

    static std::string what_color();
    //losowanie koloru
};

#endif //ZYGMUNTMATEUSZ_ETAP2_VEHICLE_H
