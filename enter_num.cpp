//
// Created by Mateusz on 03.01.2022.
//
#include "enter_num.h"

using namespace std;

int enter_num() {
    int num;

    cin >> num;
    while (cin.fail()) { //sprawdzenie, czy wczytano liczbę; jeśli nie, to:
        cin.clear(); //czyszczenie strumienia z niepoprawnych danych
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); //ignorowanie pozostawionego znaku nowej linii
        cout << "Wrong value.\n";
        cin >> num;
    }
    return num;
}

