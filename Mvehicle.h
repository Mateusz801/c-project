//
// Created by Mateusz on 20.12.2021.
//

#ifndef ZYGMUNTMATEUSZ_ETAP2_MVEHICLE_H
#define ZYGMUNTMATEUSZ_ETAP2_MVEHICLE_H

#include "Vehicle.h"
#include "Engine.h"

class Mvehicle : public Vehicle {
public:
    enum class Makes {
        Mercedes, BMW, Peugeot, Ferrari, Lamborghini, Fiat
    };
    enum class Fuel_type {
        petrol, diesel, gas, electric
    };

private:

    float calc_price(); //oblicza cenę pojazdu zależną od typu silnika, typu paliwa pojemności baku oraz marki

    float calc_cap(); //pojemność zależna od marki

    float fuel_price(); //określa cenę za l paliwa w zależności od rodzaju paliwa

    float calc_mileage(); //oblicza spalanie - spalanie silnika + spalanie paliwa

    float calc_fcap(); //pojemność paliwa zależna od typu paliwa i marki

    static Fuel_type set_fuel_type();

protected:

    Makes make;
    Engine engine;
    Fuel_type fuel_type;
    float fuel_capacity;
    float mileage{};
    float fuel_level = 5;

public:

    Mvehicle() = default;

    explicit Mvehicle(Makes mm);

    ~Mvehicle() override = default;

    Mvehicle(const Mvehicle &mvehicle);

    virtual std::string print_special() = 0;

    void fill_up();
    //pozwala zatankować pojazd, ale nie ponad pojemność baku

    void drive() override;
    //pozwala przejechać dystans zależny od aktualnego poziomu paliwa

    std::string get_name() const;

    float get_price() const { return price; }

    float get_counter() const { return km_counter; }

    friend std::ostream &operator<<(std::ostream &os, const Mvehicle::Fuel_type &p_ft);

    friend std::ostream &operator<<(std::ostream &os, Makes makes);

    friend std::istream &operator>>(std::istream &is, Makes &p_type); //przeładowanie >> dla enum (wprowadzanie)

    friend std::ostream &operator<<(std::ostream &os, const Mvehicle &mvehicle);
};


#endif //ZYGMUNTMATEUSZ_ETAP2_MVEHICLE_H
