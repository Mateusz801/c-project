//
// Created by Mateusz on 26.11.2021.
//

#ifndef PROJEKT_FACTORY_H
#define PROJEKT_FACTORY_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

#include "Mvehicle.h"
#include "Engine.h"
#include "Motorcycle.h"
#include "Car.h"
#include "enter_num.h"

class Factory {
    int stock_level = 0;
    float salary = 0;
    std::vector<std::vector<Mvehicle *> > vehicles; //"magazyn" fabryki

    int check_capacity();
    //sprawdza, czy podana liczba pojazdów do utworzenia nie przekracza pojemności fabryki
    //jeśli przekracza, to rzuca wyjątek Not_enough_space

    std::string check_vehicle();
    //sprawdza podany typ pojazdu; jeśli podano zły, to rzuca wyjątek No_such_vehicle

    bool check_position(unsigned int &p_x, unsigned int &p_y) const;

    void check_size(unsigned int &p_x, unsigned int &p_y) const;

    void place_vehicle(Mvehicle *mvehicle);
    //metoda umieszczająca przekazany jako wskaźnik pojazd w fabryce

public:
    explicit Factory(std::vector<std::vector<Mvehicle *> > cc);

    Mvehicle *take_vehicle();

    void create();
    //tworzy pojazd i - pośrednio - wstawia do "magazynu"

    void sell_vehicles();
    //sprawdza, czy na danej pozycji jest wskaźnik do pojazdu; jeśli nie, to przechodzi dalej
    //jeśli tak, to do zarobków fabryki dodawana jest cena pojazdu
    //składowa - wektor vehicles jest czyszczona, a stan fabryki ustawiany na 0

    int get_sl() const { return stock_level; }

    float get_salary() const { return salary; }

    std::vector<std::vector<Mvehicle *>> get_vehicles() { return vehicles; }

    friend std::ostream &operator<<(std::ostream &os, const Factory &p_factory);
};


#endif //PROJEKT_FACTORY_H