//
// Created by Mateusz on 26.11.2021.
//

#include "Factory.h"
#include "exceptions.h"

using namespace std;

Factory::Factory(vector<vector<Mvehicle *> > cc) : vehicles(std::move(cc)) {}

int Factory::check_capacity() {
    int number = enter_num();
    int cap = 0;
    for (int i = 0; i < vehicles.size(); ++i) {
        for (int j = 0; j < vehicles[j].size(); ++j) {
            cap += 1;
        }
    }
    if (number > cap) {
        throw Not_enough_space();
    } else {
        return number;
    }
}

std::string Factory::check_vehicle() {
    string name;
    cin >> name;

    if (name != "car" && name != "motorcycle") {
        throw No_such_vehicle();
    } else {
        return name;
    }
}

bool Factory::check_position(unsigned int &p_x, unsigned int &p_y) const {
    if (vehicles[p_x][p_y] == nullptr) {
        return false;
    } else {
        return true;
    }
}

void Factory::check_size(unsigned int &p_x, unsigned int &p_y) const {
    do {
        cout << "Choose a vehicle: \n"
                "Rows 0 - " << vehicles.size() - 1 << endl;
        p_x = enter_num();

        if (p_x >= vehicles.size()) {
            cout << "Wrong row number. Try again.\n";
        }
    } while (p_x >= vehicles.size());

    do {
        cout << "Columns 0 - " << vehicles[p_x].size() - 1 << endl;
        p_y = enter_num();

        if (p_y >= vehicles[p_x].size()) {
            cout << "Wrong column number. Try again.\n";
        }
    } while (p_y >= vehicles[p_x].size());
}

void Factory::place_vehicle(Mvehicle *mvehicle) {
    unsigned int x, y;

    do {
        cout << "Where should the car be placed in the factory?\n";
        cout << "Rows 0 - " << vehicles.size() - 1 << endl;

        do { //pętla sprawdzająca podany rozmiar fabryki
            x = enter_num();
            if (x >= vehicles.size()) {
                cout << "Your factory is not that big. Enter correct number.\n";
            }
        } while (x >= vehicles.size());

        cout << "Columns 0 - " << vehicles[x].size() - 1 << endl;

        y = enter_num();

        if (y >= vehicles[x].size()) {
            cout << "You wanted to place the car beyond factory's area.\n"
                    "Your car will be placed at the row number " << x << " at the position number "
                 << vehicles[x].size() << "\n";
            vehicles[x].push_back(mvehicle);
            break;
            //jeśli podana pozycja nie istnieje, to do określonego wiersza dodajemy element na jego końcu
        }
        else if (vehicles[x][y] != nullptr) {
            cout << "This place is already occupied. Choose a different one.\n";
        }
    } while (vehicles[x][y] != nullptr);

    vehicles[x][y] = mvehicle; //operator przypisania

    stock_level++;
}

Mvehicle *Factory::take_vehicle() {
    unsigned int x, y;
    do {
        check_size(x, y);
        if (!check_position(x, y))
            cout << "No vehicle at this position.\n";
    } while (!check_position(x, y));
    return vehicles[x][y];
}

void Factory::create() {
    string vehicle;
    int number;
    Mvehicle::Makes makes;

    cout << "Enter type of vehicle you'd like to create: (car or motorcycle)\n";
    try {
        vehicle = check_vehicle();
    }
    catch (No_such_vehicle &ex) {
        throw;
    }
    cout << "How many vehicles of this type you'd like to create? \n";

    try {
        number = check_capacity();
    }
    catch (Not_enough_space &ex) {
        throw;
    }
    if (vehicle == "car") {
        for (int i = 0; i < number; ++i) {

            cout << "Available makes are: Mercedes, BMW, Peugeot, Ferrari, Lamborghini, Fiat.\n"
                    "Choose of which make a new car shall be.\n";
            cin >> makes;
            Car *car;
            car = new Car(makes);
            place_vehicle(car);
        }
    } else if (vehicle == "motorcycle") {

        for (int i = 0; i < number; ++i) {
            cout << "Available makes are: Mercedes, BMW, Peugeot, Ferrari, Lamborghini, Fiat.\n"
                    "Choose of which make a new motorcycle shall be.\n";
            cin >> makes;

            Motorcycle *motorcycle;
            motorcycle = new Motorcycle(makes);
            place_vehicle(motorcycle);
        }
    }
}

void Factory::sell_vehicles() {
    for (unsigned int i = 0; i < vehicles.size(); ++i) {
        for (unsigned int j = 0; j < vehicles[i].size(); ++j) {
            if (vehicles[i][j] == nullptr) {
                continue;
            } else {
                salary += vehicles.at(i).at(j)->get_price();
            }
        }
    }
    vehicles.clear();
    stock_level = 0;
}

std::ostream &operator<<(ostream &os, const Factory &p_factory) {

    for (unsigned int i = 0; i < p_factory.vehicles.size(); ++i) {
        os << "Row number: " << i << endl << "|";

        for (unsigned int j = 0; j < p_factory.vehicles[i].size(); ++j) {
            if (p_factory.vehicles[i][j] == nullptr) {
                os << setw(16) << "|";
            } else {
                os << setw(15) << p_factory.vehicles.at(i).at(j)->get_name() << "|";
            }
            //setw ustawia odległość między | na 15
            //wygląda ładnie tylko, gdy w czcionce szerokość wszystkich znaków jest równa
        }
        os << endl;
    }
    return os;
}
