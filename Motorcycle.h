//
// Created by Mateusz on 03.01.2022.
//

#ifndef ZYGMUNTMATEUSZ_ETAP2_MOTORCYCLE_H
#define ZYGMUNTMATEUSZ_ETAP2_MOTORCYCLE_H

#include "Mvehicle.h"

class Motorcycle : public Mvehicle {
public:
    enum class Motor_type {
        cross, sport, touristic
    };

private:
    Motor_type motor_type;

public:
    explicit Motorcycle(Mvehicle::Makes mm);

    ~Motorcycle() override = default;

    std::string print_special() override;
    //metoda użyta do zapisu typu (Motor_type) motocyklu do pliku

    friend std::ostream &operator<<(std::ostream &os, const Motorcycle::Motor_type &mtp);

    friend std::ostream &operator<<(std::ostream &os, const Motorcycle &motorcycle);
};


#endif //ZYGMUNTMATEUSZ_ETAP2_MOTORCYCLE_H
