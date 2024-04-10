//
// Created by Mateusz on 20.12.2021.
//

#ifndef ZYGMUNTMATEUSZ_ETAP2_DEALER_H
#define ZYGMUNTMATEUSZ_ETAP2_DEALER_H

#include <iostream>
#include <vector>
#include <limits>
#include <iomanip>
#include "Mvehicle.h"
#include "enter_num.h"

class Dealer {
    float budget;
    std::vector<std::vector<Mvehicle *>> place; //przechowalnia pojazdów
    std::vector<std::string> ownerships; //"segregator" na "akty własności" sprzedanych pojazdów


    bool check_position(unsigned int &p_x, unsigned int &p_y) const;
    //jeśli nie ma pojazdu na danej pozycji, zwraca fałsz

    void check_size(unsigned int &p_x, unsigned int &p_y) const;
    //kontroluje, czy użytkownik wybiera indeksy w zakresie wektora

    static void modify_price(Mvehicle *mvehicle);
    //modyfikuje cenę na podstawie aktualnego stanu licznika km

    static void modify_counter(Mvehicle *mvehicle);
    //modyfikuje licznik km jeśli pojazd jest marki BMW, Fiat lub Peugeot

    static std::string frame(std::string p_up, std::string p_low);
    //tworzy "akt własności" opatrzony ramką. Ramka tworzona jest na podstawie marki pojazdu oraz danych nabywcy
    //nie musi być wywoływana na obiekcie "Factory"

public:

    explicit Dealer(std::vector<std::vector<Mvehicle *> > pp, float bb);

    Mvehicle *take_vehicle();
    //prosi o wybranie pozycji dopóki na określonej pozycji nie znajduje się wskaźnik do pojazdu s., po wybraniu zwraca go

    Mvehicle *sell();
    //sprzedaje użytkownikowi pojazd, zwracając wskaźnik do niego. Modyfikuje budżet komisu, wystawia akt włąsności oraz
    //usuwa wskaźnik z miejsca, gdzie stał pojazd (wskaźnik). W procesie sprzedaży modyfikuje licznik pojazdu oraz cenę

    void buy(Mvehicle *mvehicle);
    //kupuje pojazd od użytkownika, modyfikuje budżet komisu. Kupowany pojazd przyjmowany jest w argumencie metody przez
    //wskaźnik

    void specifics();
    //pokazuje szczegółowe informacje dla wybranego pojazdu

    std::vector<std::string> get_ownerships() const { return ownerships; }

    float get_budget() const { return budget; }

    friend std::ostream &operator<<(std::ostream &os, const Dealer &dealer);
};


#endif //ZYGMUNTMATEUSZ_ETAP2_DEALER_H
