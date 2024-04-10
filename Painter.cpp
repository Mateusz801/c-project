//
// Created by Mateusz on 03.01.2022.
//

#include "Painter.h"

using namespace std;

void Painter::change_color(Vehicle &vehicle) {
    string choice;

    cout << "Current color: " << vehicle.color << endl;
    cout << "Available colors:\n";
    for (auto &color: Vehicle::colors) {
        cout << color << ", ";

    }

    int compare;
    do {

        cout << "What color do you choose?\n";
        cin >> choice;

        for (auto &color: Vehicle::colors) {
            compare = choice.compare(color);

            if (compare == 0) {
                vehicle.color = choice;
                salary += 500;
                break;
            }
        }
        if (compare != 0) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Wrong color / value. Try again.\n";
        }

    } while (compare != 0);

    vehicle.color = choice;
    cout << "New color is: " << vehicle.color << endl;
    salary += 500;
}
