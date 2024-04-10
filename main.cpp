//
// Created by Mateusz on 20.12.2021.
//

#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>
#include <filesystem>
#include <cstring>
#include <fcntl.h>
#include <unistd.h>

#include "Dealer.h"
#include "Factory.h"
#include "Painter.h"
#include "Bike.h"
#include "exceptions.h"

using namespace std;

void check(int &x, int &y) {
    if (x <= 0 || y <= 0) {
        throw Non_positive_value();
    }
    if (x > 50 || y > 50) {
        throw Big_vector();
    }
}

template<typename T>
bool check_1Dvector(const vector<T> &vec) {

    if (vec.empty()) {
        return true;
    } else {
        return false;
    }
}

void save_to_file(const Dealer &dealer, const vector<Mvehicle *> &vec);

void save_to_file(const vector<Bike *> &vec);

void read_file();

void factory_dealer_actions();

void bike_actions();

bool is_open(const fstream &bp_file);

Bike *choose_bike(const vector<Bike *> &bikes);

int init_in(int argc, char *argv[]) {
    int fd;
    for (int i = 1; i < argc; ++i) { //pętla od 1, bo argv[0] to ścieżka do pliku
        if (strcmp("-i", argv[i]) == 0 && argc > i + 1) {
            //sprawdzamy, czy aktualnie analizowany element argv[i] jest równy ciągowi "-i"
            //jeśli tak, to sprawdzamy czy istnieje element za argv[i], którym musi być ścieżka do pliku lub znak "-"
            if (strcmp("-", argv[++i]) == 0) //jeśli znak to "-", nic nie robimy i przechodzimy dalej
                continue;
            fd = open(argv[i], O_RDONLY); //próba otwarcia pliku podanego zaraz za "-i" w trybie do odczytu
            if (fd < 0) //open() zwraca < 0 w przypadku niepowodzenia
                return -1;
            if (dup2(fd, 0) != 0)
                //jeśli funkcja dup2 zakończy się powodzeniem, standardowe wejście będzie czytane z podanego pliku
                return -2;
            close(fd);
        }
    }
    return 0;
}

int main(int argc, char *argv[]) {

    if (init_in(argc, argv) < 0) {
        cerr << "Nie można zainicjalizować wejścia/wyjścia...\n";
        return 1;
    }

    srand(time(nullptr));


    int choice;
    do {
        cout << "\n\t$-*-*-*- MAIN MENU -*-*-*-$ \n"
                "\t1. Factory & dealer options.\n"
                "\t2. Bike options.\n"
                "\t3. Read data from file.\n"
                "\t4. Exit.\n\n";

        choice = enter_num();

        switch (choice) {
            case 1:
                factory_dealer_actions();
                break;
            case 2:
                bike_actions();
                break;
            case 3:
                read_file();
                break;
            case 4:
                break;
            default:
                cout << "Wrong value.\n";
        }
    } while (choice != 4);

    return 0;
}

void save_to_file(const Dealer &dealer, const vector<Mvehicle *> &vec) {
    fstream file;
    file.open("dealer_data.txt", ios::out | ios::trunc);
    //jeśli plik już istnieje, to kasujemy poprzednią zawartość


    if (is_open(file)) {
        file << "Dealer data:\n";
        file << dealer << endl;
        file << "Ownerships of sold vehicles:\n\n";
        for (const auto &invoice: dealer.get_ownerships())
            file << invoice << endl;

        file << "\nDealer's budget at the end was " << dealer.get_budget() << endl;
        file << "\nVehicles in the garage:\n";
        for (const auto &vehicle: vec) {
            file << vehicle->get_name() << "\t\t" << vehicle->print_special() << endl;
        }
    } else {
        cout << "Error when opening the file.\n";
    }
    file.close();
}

void save_to_file(const vector<Bike *> &vec) {
    fstream file;
    file.open("bike_data.txt", ios::out | ios::trunc);

    if (is_open(file)) {
        file << "Bikes:\n";
        for (const auto &bike: vec)
            file << *bike << endl;
    } else {
        cout << "Error when opening the file.\n";
    }
    file.close();
}

void read_file() {
    int choice;
    do {
        cout << "\n$-*-*-*- READING FILES OPTIONS -*-*-*-$\n"
                "\t1. Factory & dealer data.\n"
                "\t2. Bikes data.\n"
                "\t0. Return.\n"
                "Which data would you like to load?\n";

        choice = enter_num();

        switch (choice) {
            case 0:
                break;
            case 1: {
                fstream file;
                file.open("dealer_data.txt", ios::in);
                if (is_open(file)) {
                    vector<string> lines;
                    string text;

                    cout << "Factory & dealer data: \n\n";
                    while (getline(file, text)) {
                        lines.push_back(text);
                        //zapisujemy kolejne linie na kolejnych miejscach w wektorze za pomocą zmiennej pomocniczej 'text'
                    }
                    for (const auto &line: lines)
                        cout << line << endl; //wypisywanie kolejnych linii
                } else {
                    cout << "Error when opening the file.\n";
                }
                file.close();
                break;
            }
            case 2: {
                fstream file;
                file.open("bike_data.txt", ios::in);
                if (is_open(file)) {
                    vector<string> lines;
                    string text;

                    while (getline(file, text)) {
                        lines.push_back(text);
                        //zapisujemy kolejne linie na kolejnych miejscach w wektorze za pomocą zmiennej pomocniczej 'text'
                    }
                    for (const auto &line: lines)
                        cout << line << endl; //wypisywanie kolejnych linii
                } else {
                    cout << "Error when opening the file.\n";
                }
                file.close();
                break;
            }
            default:
                cout << "Wrong value\n";
                break;
        }
    } while (choice != 0);
}

bool is_open(const fstream &bp_file) {
    if (!bp_file.good()) {
        return false;
    }
    return true;
}

void factory_dealer_actions() {
    fstream file;
    int x, y, choice;
    vector<Mvehicle *> garage; //garaż dla kupionych od komisu pojazdów
    vector<vector<Mvehicle *> > best;

    cout << "Specify size of the factory please (2 positive numbers).\n";
    try {
        x = enter_num();
        y = enter_num();
        check(x, y);
    }
    catch (Non_positive_value &ex) {
        throw;
    }
    catch (Big_vector &ex) {
        throw;
    }

    best.resize(x);                        // napompowanie pionowe
    for (unsigned int rz = 0; rz < x; ++rz) {
        best[rz].resize(y);                // napompowanie konkretnego rzędu
    }

    Factory factory(best);

    do {
        cout << "\n$-*-*-*- FACTORY PROGRAM OPTIONS -*-*-*-$ \n"
                "\t1. Create vehicle(s).\n" //tworzy pojazd i wstawia je w określone miejsce w fabryce
                "\t2. Show the magazine.\n" //pokazuje zawartość fabryki
                "\t3. Fill up a vehicle.\n" //tankuje pojazd i pokazuje cenę do zapłaty
                "\t4. Drive.\n" //nabija km na licznik, modyfikuje stan paliwa i wyświetla koszt podróży
                "\t5. Change color of a vehicle.\n"
                "\t6. Dealer options.\n"
                "\t7. Exit.\n"
                "Choose what you'd like to do.\n";

        choice = enter_num();

        switch (choice) {
            case 1:
                factory.create();
                break;
            case 2:
                if (factory.get_sl() == 0) { //jeśli nie ma aut, wypisujemy komunikat, ale nie pokazujemy
                    cout << "No vehicles in the factory.\n";
                } else if (factory.get_sl() == 1) {
                    cout << "There is 1 vehicle available:\n";
                    cout << factory << endl;
                } else {
                    cout << "There are " << factory.get_sl() << " vehicles available:\n";
                    cout << factory << endl;
                }
                break;
            case 3:
                if (factory.get_sl() == 0) {
                    cout << "No vehicles in the factory. Create a vehicle first.\n";
                } else {
                    factory.take_vehicle()->fill_up();
                }
                break;
            case 4:
                if (factory.get_sl() == 0) {
                    cout << "No vehicles in the factory. Create a vehicle first.\n";
                } else {
                    factory.take_vehicle()->drive();
                }
                break;
            case 5:
                if (factory.get_sl() == 0) {
                    cout << "No vehicles in the factory. Create a vehicle first.\n";
                } else {
                    Painter painter;
                    painter.change_color(*factory.take_vehicle());
                }
            case 6:
                if (factory.get_sl() == 0) {
                    cout << "No vehicles in the factory. Create a vehicle first.\n";
                    choice = 0;
                }
                break;
            case 7:
                cout << "Thank you for using the program.\n";
                exit(0);
            default:
                cout << "Wrong number.\n";
                break;
        }
    } while (choice != 6);

    best = factory.get_vehicles();
    factory.sell_vehicles();
    cout << "Thank you for visiting our factory.\n"
            "In this session it earned " << factory.get_salary() << " zlotych.\n";

    Dealer dealer(best, factory.get_salary());

    do {
        cout << "\n$-*-*-*- DEALER PROGRAM OPTIONS -*-*-*-$ \n"
                "\t1. Show available vehicles.\n" //pokazuje zawartość komisu
                "\t2. Show specifics of a vehicle.\n" //pokazuje szczegółowe dane pojazdu
                "\t3. Buy a vehicle from the dealer.\n" //komis sprzedaje pojazd
                "\t4. Sell a vehicle to the dealer.\n" //komis kupuje pojazd
                "\t5. Fill up a vehicle.\n"
                "\t6. Drive.\n"
                "\t7. Save data.\n"
                "\t8. Return to main menu.\n"
                "Choose what you'd like to do.\n";

        unsigned int a;
        choice = enter_num();

        switch (choice) {
            case 1:
                cout << dealer << endl;
                break;
            case 2:
                dealer.specifics();
                break;
            case 3: {
                Mvehicle *mvehicle = dealer.sell();
                if (mvehicle != nullptr) {
                    garage.push_back(mvehicle);
                }
                break;
            }
            case 4:
                if (check_1Dvector(garage)) {
                    cout << "No vehicles to sell to the dealer.\n";
                    continue;
                }
                cout << "Which vehicle would you like to sell?\n";
                for (int i = 0; i < garage.size(); ++i) {
                    cout << i << ". " << garage[i]->get_name() << endl;
                }
                cout << "Enter number: ";
                a = enter_num();
                dealer.buy(garage[a]);
                garage.erase(garage.begin() + a);
                break;
            case 5:
                dealer.take_vehicle()->fill_up();
                break;
            case 6:
                dealer.take_vehicle()->drive();
                break;
            case 7:
                save_to_file(dealer, garage);
                break;
            case 8:
                break;
            default:
                cout << "Wrong number.\n";
                break;
        }

    } while (choice != 8);

    cout << "Dealer's budget is now: " << dealer.get_budget() << endl;

}

void bike_actions() {
    int choice, number;
    vector<Bike *> bikes;
    do {
        cout << "\n$-*-*-*- BIKE PROGRAM OPTIONS -*-*-*-$ \n"
                "\t1. Create bike(s).\n" //tworzy pojazd i wstawia je w określone miejsce w fabryce
                "\t2. Show types of available bikes.\n" //pokazuje zawartość fabryki
                "\t3. Show specifics of chosen bike.\n" //tankuje pojazd i pokazuje cenę do zapłaty
                "\t4. Ride a bike.\n"
                "\t5. Change color.\n" //nabija km na licznik, modyfikuje stan paliwa i wyświetla koszt podróży
                "\t6. Save data.\n"
                "\t7. Return to main menu.\n"
                "Choose what you'd like to do.\n";

        choice = enter_num();

        switch (choice) {
            case 1:
                cout << "How many bikes would you like to create?\n";
                number = enter_num();

                for (int i = 0; i < number; ++i) {
                    Bike *bike = new Bike;
                    bikes.push_back(bike);
                }
                break;
            case 2:
                if (check_1Dvector(bikes)) {
                    cout << "No bikes were created.\n";
                } else {
                    for (int i = 0; i < bikes.size(); ++i) {
                        cout << i << ". " << bikes[i]->get_type() << endl;
                    }
                }
                break;
            case 3:
                if (check_1Dvector(bikes)) {
                    cout << "No bikes were created.\n";
                } else {
                    cout << *choose_bike(bikes) << endl;
                }
                break;
            case 4:
                if (check_1Dvector(bikes)) {
                    cout << "No bikes were created.\n";
                } else {
                    choose_bike(bikes)->drive();
                }
                break;
            case 5: {
                if (check_1Dvector(bikes)) {
                    cout << "No bikes were created.\n";
                } else {
                    Painter painter;
                    painter.change_color(*choose_bike(bikes));
                }
                break;
            }
            case 6:
                save_to_file(bikes);
                break;
            case 7:
                break;
            default:
                cout << "Wrong number.\n";
                break;
        }
    } while (choice != 7);
}

Bike *choose_bike(const vector<Bike *> &bikes) {
    int a;
    cout << "Choose a bike: 0 - " << bikes.size() - 1 << endl;
    do {
        a = enter_num();
        if (a >= bikes.size()) {
            cout << "Wrong index.\n";
        }
    } while (a >= bikes.size());
    return bikes[a];
}