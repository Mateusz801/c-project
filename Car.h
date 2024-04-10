//
// Created by Mateusz on 28.12.2021.
//

#ifndef ZYGMUNTMATEUSZ_ETAP2_CAR_H
#define ZYGMUNTMATEUSZ_ETAP2_CAR_H

#include "Mvehicle.h"

class Car : public Mvehicle {
    int door_count;
public:
    explicit Car(Mvehicle::Makes mm);

    ~Car() override = default;

    std::string print_special() override;
    //metoda użyta do zapisu liczby drzwi danego auta do pliku

    friend std::ostream &operator<<(std::ostream &os, const Car &car);
};


#endif //ZYGMUNTMATEUSZ_ETAP2_CAR_H
