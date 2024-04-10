//
// Created by Mateusz on 20.12.2021.
//

#include "Bike.h"

using namespace std;

Bike::Bike() : Vehicle() {
    type = set_type();
    price = calc_price();
    if (with_basket()) {
        capacity = 10;
    } else {
        capacity = 1;
    }
}

float Bike::calc_price() {
    float p_type, p_cap;

    switch (type) {
        case Type::road: {
            p_type = 200;
            break;
        }
        case Type::mountain: {
            p_type = 100;
            break;
        }
        case Type::touring: {
            p_type = 300;
            break;
        }
        case Type::BMX: {
            p_type = 500;
            break;
        }
        default: {
            p_type = 0;
            break;
        }
    }

    if (capacity == 1) {//nie ma koszyka
        p_cap = 0;
    } else {
        p_cap = 100;
    }

    return (p_type + p_cap);
}

Bike::Type Bike::set_type() {
    return static_cast<Type>(rand() % 4);
}

bool Bike::with_basket() {
    int choice;
    cout << "Do you want this bike to have a basket?\n"
            "0 - no\n"
            "1 - yes\n";
    choice = enter_num();
    if (choice == 0) {
        return false;
    } else {
        return true;
    }
}

void Bike::drive() {
    int distance;

    cout << "How far would you like to cycle?\n";
    distance = enter_num();

    if (distance <= 10) {
        cout << "Work on your condition :)\n";
    } else if (distance > 10 && distance <= 50) {
        cout << "Nice distance to cover.\n";
    } else {
        cout << "You're awesome... Or insane.\n";
    }
    cout << "You've burnt more or less " << distance * 30 << "kcal - depending on your speed.\n";
    km_counter += distance;
}

std::ostream &operator<<(ostream &os, const Bike::Type &p_t) {
    switch (p_t) {
        case Bike::Type::road: {
            os << "road";
            break;
        }
        case Bike::Type::mountain: {
            os << "mountain";
            break;
        }
        case Bike::Type::touring: {
            os << "touring";
            break;
        }
        case Bike::Type::BMX: {
            os << "BMX";
            break;
        }
    }
    return os;
}

std::ostream &operator<<(ostream &os, const Bike &bike) {
    os << "Type: " << bike.type << endl;
    os << "Capacity: " << bike.capacity << endl;
    os << "Color: " << bike.color << endl;
    os << "Price: " << bike.price << endl;
    os << "Distance covered: " << bike.km_counter << endl;
    return os;
}
