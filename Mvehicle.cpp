//
// Created by Mateusz on 20.12.2021.
//

#include "Mvehicle.h"

using namespace std;

Mvehicle::Mvehicle(Makes mm) : Vehicle(), make(mm) {
    engine = Engine::create_engine();
    fuel_type = set_fuel_type();
    fuel_capacity = calc_fcap();
    price = calc_price();
    capacity = calc_cap();
    mileage = calc_mileage();
}

Mvehicle::Mvehicle(const Mvehicle &mvehicle) = default;

float Mvehicle::calc_price() {
    float p_make, p_eng, p_fuel, p_cap;

    switch (make) {
        case Makes::Mercedes:
            p_make = 10000;
            break;
        case Makes::BMW:
            p_make = 8000;
            break;
        case Makes::Peugeot:
            p_make = 5000;
            break;
        case Makes::Ferrari:
            p_make = 20000;
            break;
        case Makes::Lamborghini:
            p_make = 30000;
            break;
        case Makes::Fiat:
            p_make = 3000;
            break;
    }

    p_eng = engine.get_price();

    switch (fuel_type) {
        case Fuel_type::petrol:
            p_fuel = 2000;
            break;
        case Fuel_type::diesel:
            p_fuel = 3000;
            break;
        case Fuel_type::gas:
            p_fuel = 1000;
            break;
        case Fuel_type::electric:
            p_fuel = 5000;
            break;
        default:
            p_fuel = 0;
            break;
    }

    if (fuel_capacity < 20) {
        p_cap = 200;
    } else if (fuel_capacity >= 20 && fuel_capacity <= 50) {
        p_cap = 400;
    } else {
        p_cap = 700;
    }

    return (p_make + p_eng + p_fuel + p_cap);
}

float Mvehicle::calc_cap() {
    float cap;
    switch (make) {
        case Makes::Mercedes:
            cap = 100;
            break;
        case Makes::BMW:
            cap = 60;
            break;
        case Makes::Peugeot:
            cap = 30;
            break;
        case Makes::Ferrari:
            cap = 10;
            break;
        case Makes::Lamborghini:
            cap = 5;
            break;
        case Makes::Fiat:
            cap = 60;
            break;
        default:
            cap = -1;
    }
    return cap;
}

float Mvehicle::fuel_price() {
    switch (fuel_type) {
        case Fuel_type::petrol:
            return 6.1;
        case Fuel_type::diesel:
            return 5.82;
        case Fuel_type::gas:
            return 3.5;
        case Fuel_type::electric:
            return 2.2;
        default:
            return -1;
    }
}

float Mvehicle::calc_mileage() {
    switch (fuel_type) {
        case Fuel_type::petrol:
            return engine.get_mileage() + 3;
        case Fuel_type::diesel:
            return engine.get_mileage() + 5;
        case Fuel_type::gas:
            return engine.get_mileage() + 2;
        case Fuel_type::electric:
            return engine.get_mileage() + 1;
        default:
            return -1;
    }
}

float Mvehicle::calc_fcap() {
    float b_fuel_type, b_make; //b = based

    switch (fuel_type) {
        case Fuel_type::petrol:
            b_fuel_type = 45;
            break;
        case Fuel_type::diesel:
            b_fuel_type = 50;
            break;
        case Fuel_type::gas:
            b_fuel_type = 40;
            break;
        case Fuel_type::electric:
            b_fuel_type = 35;
            break;
    }

    switch (make) {
        case Makes::Mercedes:
            b_make = 15;
            break;
        case Makes::BMW:
            b_make = 20;
            break;
        case Makes::Peugeot:
            b_make = 10;
            break;
        case Makes::Ferrari:
            b_make = 8;
            break;
        case Makes::Lamborghini:
            b_make = 7;
            break;
        case Makes::Fiat:
            b_make = 19;
            break;
    }

    return (b_fuel_type + b_make);
}

Mvehicle::Fuel_type Mvehicle::set_fuel_type() {
    return static_cast<Fuel_type>(rand() % 4);
}

void Mvehicle::fill_up() {
    float filling;
    bool check;

    do {
        cout << "How much fuel would you like to fill up?\n";
        cin >> filling;
        check = (fuel_capacity < (fuel_level + filling));
        //prawda, jeśli pojemność mniejsza niż obecny poziom + chęć zatankowania

        if (check) {
            cout << "You can not fill up over max capacity.\nThe max amount of fuel you can fill up now is "
                 << (fuel_capacity - fuel_level) << " litres.\n";
        } else {
            fuel_level += filling;
            cout << "Fuel level is now " << fuel_level << " out of max " << fuel_capacity << "l.\n";
            cout << "You need to pay " << fuel_price() * filling << " zlotych.\n";
        }
    } while (check); //pętla będzie się wykonywać do poprawnego tankowania (nie ponad pojemność)
}

void Mvehicle::drive() {
    float distance, burnt;

    do {
        cout << "How far are we going? ";
        cin >> distance;

        burnt = (distance / 100) * mileage; //ile spalimy

        if (burnt > fuel_level) {
            cout << "You can not go that for without additional filling up. Choose a closer destination.\n";
        } else {
            km_counter += distance;
            cout << "The drive cost is " << burnt * fuel_price() << " zlotych.\n";
        }
    } while (burnt > fuel_level);
    fuel_level -= burnt;
}

std::string Mvehicle::get_name() const {
    if (make == Makes::Mercedes) {
        return "Mercedes";
    } else if (make == Makes::Peugeot) {
        return "Peugeot";
    } else if (make == Makes::Lamborghini) {
        return "Lamborghini";
    } else if (make == Makes::Fiat) {
        return "Fiat";
    } else if (make == Makes::Ferrari) {
        return "Ferrari";
    } else if (make == Makes::BMW) {
        return "BMW";
    } else
        return "";
}

std::ostream &operator<<(ostream &os, const Mvehicle::Fuel_type &p_ft) {
    switch (p_ft) {
        case Mvehicle::Fuel_type::petrol: {
            os << "petrol";
            break;
        }
        case Mvehicle::Fuel_type::diesel: {
            os << " diesel";
            break;
        }
        case Mvehicle::Fuel_type::gas: {
            os << "gas";
            break;
        }
        case Mvehicle::Fuel_type::electric: {
            os << "electric";
            break;
        }
    }
    return os;
}

std::ostream &operator<<(ostream &os, const Mvehicle::Makes makes) {
    switch (makes) {
        case Mvehicle::Makes::Mercedes: {
            os << "Mercedes";
            break;
        }
        case Mvehicle::Makes::BMW: {
            os << "BMW";
            break;
        }
        case Mvehicle::Makes::Peugeot: {
            os << "Peugeot";
            break;
        }
        case Mvehicle::Makes::Ferrari: {
            os << "Ferrari";
            break;
        }
        case Mvehicle::Makes::Lamborghini: {
            os << "Lamborghini";
            break;
        }
        case Mvehicle::Makes::Fiat: {
            os << "Fiat";
            break;
        }
    }
    return os;
}

std::istream &operator>>(istream &is, Mvehicle::Makes &makes) {
    string name;
    is >> name;

    if (name == "BMW")
        makes = Mvehicle::Makes::BMW;
    else if (name == "Ferrari")
        makes = Mvehicle::Makes::Ferrari;
    else if (name == "Fiat")
        makes = Mvehicle::Makes::Fiat;
    else if (name == "Lamborghini")
        makes = Mvehicle::Makes::Lamborghini;
    else if (name == "Mercedes")
        makes = Mvehicle::Makes::Mercedes;
    else if (name == "Peugeot")
        makes = Mvehicle::Makes::Peugeot;
    else
        throw out_of_range("Invalid value for type 'Makes'");
    return is;
}

std::ostream &operator<<(ostream &os, const Mvehicle &mvehicle) {
    os << "Make: " << mvehicle.make << endl;
    os << "Engine: " << mvehicle.engine << endl;
    os << "Fuel type: " << mvehicle.fuel_type << endl;
    os << "Mileage: " << mvehicle.mileage << endl;
    os << "Fuel capacity: " << mvehicle.fuel_capacity << endl;
    os << "Fuel level: " << mvehicle.fuel_level << endl;
    os << "Km counter: " << mvehicle.km_counter << endl;
    os << "Color: " << mvehicle.color << endl;
    return os;
}
