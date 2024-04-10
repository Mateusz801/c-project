//
// Created by Mateusz on 20.12.2021.
//

#ifndef ZYGMUNTMATEUSZ_ETAP2_BIKE_H
#define ZYGMUNTMATEUSZ_ETAP2_BIKE_H

#include "Vehicle.h"
#include <iostream>
#include "enter_num.h"

class Bike : public Vehicle {
public:
    enum class Type {
        BMX, mountain, road, touring,
    };
private:
    Type type;

    float calc_price(); //obliczanie ceny na podstawie typu i posiadania koszyka

    Type set_type(); //losowanie typu

    static bool with_basket(); //wybór, czy rower ma mieć koszyk

public:
    explicit Bike();

    ~Bike() override = default;

    float get_price() { return price; }

    Type get_type() { return type; }

    void drive() override;
    //wyświetlany jest komunikat zależny od dystansu oraz spalone kalorie, metoda modyfikuje licznik km

    friend std::ostream &operator<<(std::ostream &os, const Bike::Type &p_t);

    friend std::ostream &operator<<(std::ostream &os, const Bike &bike);
};

#endif //ZYGMUNTMATEUSZ_ETAP2_BIKE_H
