//
// Created by Mateusz on 20.12.2021.
//

#include "Dealer.h"

using namespace std;

Dealer::Dealer(vector<vector<Mvehicle *> > pp, float bb) : place(std::move(pp)), budget(500000 - bb) {}


bool Dealer::check_position(unsigned int &p_x, unsigned int &p_y) const {
    if (place[p_x][p_y] == nullptr) {
        return false;
    } else {
        return true;
    }
}

void Dealer::check_size(unsigned int &p_x, unsigned int &p_y) const {
    do {
        cout << "Choose a vehicle: \n"
                "Rows 0 - " << place.size() - 1 << endl;
        p_x = enter_num();

        if (p_x >= place.size()) {
            cout << "Wrong row number. Try again.\n";
        }
    } while (p_x >= place.size());

    do {
        cout << "Columns 0 - " << place[p_x].size() - 1 << endl;
        p_y = enter_num();

        if (p_y >= place[p_x].size()) {
            cout << "Wrong column number. Try again.\n";
        }
    } while (p_y >= place[p_x].size());
}

void Dealer::modify_price(Mvehicle *mvehicle) {
    float add_price, counter;

    counter = mvehicle->get_counter();
    //przedziały zaniżone dla wygody testowania
    if (counter < 100) {
        if (counter == 0) {
            add_price = 1000;
        } else {
            add_price = counter * 50;
        }
    } else if (counter >= 100 && counter <= 500) {
        add_price = counter * 25;
    } else {
        add_price = counter * 10;
    }
    mvehicle->price += add_price;
}

void Dealer::modify_counter(Mvehicle *mvehicle) {
    string make = mvehicle->get_name();
    if (make == "BMW" || make == "Fiat" || make == "Peugeot") {
        if (mvehicle->km_counter != 0) { //zabezpieczenie przed dzieleniem zerowego licznika
            mvehicle->km_counter = mvehicle->km_counter / 2;
        }
    }
}

string Dealer::frame(string p_up, string p_low) {
    int up_leng, low_leng, line_diff, frame_length;
    string fill, frame, ownership;

    up_leng = p_up.length();
    low_leng = p_low.length();
    line_diff = abs(up_leng - low_leng); //jaka jest różnica między długościami linijek

    for (int i = 0; i < line_diff; i++) {
        fill += " "; //string ze spacjami
    }

    //dodanie odpowiedniej ilości spacji do krótszej linijki
    if (up_leng > low_leng) {
        p_low += fill;
    } else {
        p_up += fill;
    }

    frame_length = max(up_leng, low_leng); //znalezienie dłuższej linijki

    //string o długości dłuższej linijki + 1, składający się z #
    for (int i = 0; i <= frame_length + 1; i++) {
        frame += "#";
    }

    //dodanie enterów i końców ramki
    frame += "\n";
    p_up += " $\n";
    p_low += " $\n";

    //łączenie stringów
    ownership.append(frame);
    ownership.append(p_up);
    ownership.append(p_low);
    ownership.append(frame);

    return ownership;
}


Mvehicle *Dealer::take_vehicle() {
    unsigned int x, y;
    do {
        check_size(x, y);
        if (!check_position(x, y))
            cout << "No vehicle at this position.\n";
    } while (!check_position(x, y));
    return place[x][y];
}

Mvehicle *Dealer::sell() {
    unsigned int x, y;
    int choice;
    Mvehicle *temp = nullptr;

    cout << "Which vehicle would you like to buy?\n";
    check_size(x, y);

    if (check_position(x, y)) {
        float margin;

        margin = place[x][y]->price * 15 / 100; //marża 15%

        cout << "This vehicle costs " << place[x][y]->price << " zlotych with additional 15% margin .\n";
        cout << "If you sure you want to buy it, press 1. If not, press 0.\n";

        choice = enter_num();

        if (choice == 1) {
            string name, up_line, low_line, ownership;

            modify_price(place[x][y]);
            modify_counter(place[x][y]);
            //licznik i cenę modyfikujemy dopiero po podaniu ceny, gdy kupujący podejmie decyzję

            budget += (place[x][y]->get_price() + margin);

            cout << "What name should be put in the ownership?\n";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, name);

            up_line = "$ Make: ";
            up_line.append(place[x][y]->get_name()); //dodanie do stringa innego stringa
            low_line = "$ Owner: ";
            low_line.append(name);

            ownership = frame(up_line, low_line);
            cout << ownership;
            ownerships.push_back(ownership); //dodanie "aktu własności" do "segregatora"

            temp = place[x][y];
            place[x].erase(place[x].begin() + y);
            //usunięcie samochodu z komisu z pozycji (początek + wskazana pozycja) i zmniejszenie wektora

            return temp;

        } else if (choice == 0) {
            cout << "You're welcome to return after having second thoughts.\n";
        } else {
            cout << "Wrong symbol. Cancelling transaction...\n";
        }
    } else {
        cout << "No vehicle at this position.\n";
    }
    return temp;
}

void Dealer::buy(Mvehicle *mvehicle) {
    unsigned int x, y;

    do {
        cout << "Where should the car be placed in the dealer's place?\n";
        cout << *this << endl; //wyświetlenie obecnego stanu
        cout << "Rows 0 - " << place.size() - 1 << endl;

        do { //pętla sprawdzająca podany rozmiar fabryki
            x = enter_num();
            if (x >= place.size()) {
                cout << "The dealer's place is not that big. Enter correct number.\n";
            }
        } while (x >= place.size());

        cout << "Columns 0 - " << place[x].size() - 1 << endl;

        y = enter_num();

        if (y >= place[x].size()) {
            cout << "You wanted to place the car beyond dealer's place area.\n"
                    "Your car will be placed at the row number " << x << " at the position number "
                 << place[x].size() << "\n";
            place[x].push_back(mvehicle);
            break;
            //jeśli podana pozycja nie istnieje, to do określonego wiersza dodajemy element na jego końcu i przerywamy pętlę
        } else if (place[x][y] != nullptr) {
            cout << "This place is already occupied. Choose a different one.\n";
        }
    } while (place[x][y] != nullptr);

    place[x][y] = mvehicle; //operator przypisania

    budget -= mvehicle->price;
}

void Dealer::specifics() {
    unsigned x, y;

    cout << "Which vehicle's specifics would you like to see?\n";
    check_size(x, y);
    if (check_position(x, y)) {
        cout << *place[x][y] << place[x][y]->print_special() << endl;
    }
}

std::ostream &operator<<(ostream &os, const Dealer &dealer) {

    for (unsigned int i = 0; i < dealer.place.size(); ++i) {
        os << "Row number: " << i << endl << "|";

        for (unsigned int j = 0; j < dealer.place[i].size(); ++j) {
            if (dealer.place[i][j] == nullptr) {
                os << setw(16) << "|";
            } else {
                os << setw(15) << dealer.place.at(i).at(j)->get_name() << "|";
            }
            //setw ustawia odległość między | na 15
            //wygląda ładnie tylko, gdy w czcionce szerokość wszystkich znaków jest równa
        }
        os << endl;
    }
    return os;
}
