//
// Created by Mateusz on 28.12.2021.
//

#include "Car.h"

using namespace std;

Car::Car(Mvehicle::Makes mm) : Mvehicle(mm) {
    if (rand() % 2 == 0) {
        door_count = 3;
    }
    door_count = 5;
}

string Car::print_special() {
    string temp = "Number of doors: ";
    temp += to_string(door_count); //konwersja inta na string
    return temp;
}

std::ostream &operator<<(std::ostream &os, const Car &car) {
    os << "Make: " << car.make << endl;
    os << "Engine: " << car.engine << endl;
    os << "Fuel type: " << car.fuel_type << endl;
    os << "Mileage: " << car.mileage << endl;
    os << "Fuel capacity: " << car.fuel_capacity << endl;
    os << "Fuel level: " << car.fuel_level << endl;
    os << "Km counter: " << car.km_counter << endl;
    os << "Color: " << car.color << endl;
    os << "Number of doors: " << car.door_count << endl;
    return os;
}

