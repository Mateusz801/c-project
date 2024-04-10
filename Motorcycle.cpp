//
// Created by Mateusz on 03.01.2022.
//

#include "Motorcycle.h"

using namespace std;

Motorcycle::Motorcycle(Mvehicle::Makes mm) : Mvehicle(mm) {
    int type = rand() % 3;
    switch (type) {
        case 0: {
            motor_type = Motor_type::cross;
            break;
        }
        case 1: {
            motor_type = Motor_type::sport;
            break;
        }
        case 2: {
            motor_type = Motor_type::touristic;
            break;
        }
        default:
            break;
    }
}

string Motorcycle::print_special() {
    string temp = "Type: ";
    switch (motor_type) {
        case Motor_type::cross:
            temp += "cross";
            break;
        case Motor_type::sport:
            temp += "sport";
            break;
        case Motor_type::touristic:
            temp += "touristic";
            break;
    }
    return temp;
}

std::ostream &operator<<(std::ostream &os, const Motorcycle::Motor_type &mtp) {
    switch (mtp) {
        case Motorcycle::Motor_type::cross: {
            os << "cross";
            break;
        }
        case Motorcycle::Motor_type::sport: {
            os << "sport";
            break;
        }
        case Motorcycle::Motor_type::touristic: {
            os << "touristic";
            break;
        }
    }
    return os;
}

std::ostream &operator<<(std::ostream &os, const Motorcycle &motorcycle) {
    os << "Make: " << motorcycle.make << endl;
    os << "Engine: " << motorcycle.engine << endl;
    os << "Fuel type: " << motorcycle.fuel_type << endl;
    os << "Mileage: " << motorcycle.mileage << endl;
    os << "Fuel capacity: " << motorcycle.fuel_capacity << endl;
    os << "Fuel level: " << motorcycle.fuel_level << endl;
    os << "Km counter: " << motorcycle.km_counter << endl;
    os << "Color: " << motorcycle.color << endl;
    os << "Type: " << motorcycle.motor_type << endl;
    return os;
}