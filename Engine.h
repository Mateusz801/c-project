//
// Created by Mateusz on 26.11.2021.
//

#ifndef PROJEKT_ENGINE_H
#define PROJEKT_ENGINE_H

#include <iostream>

class Engine {
public:
    enum class Type {
        V6, V8, V10, V12
    };

private:
    Type type;
    int weight;
    int power; //konie mechaniczne
    float mileage;
    int price;

public:
    //Konstrutkory
    Engine();

    Engine(int ww, int pp, float mm, int pr, Type tt);

    static Engine create_engine(); //funkcja musi być dostępna nawet, gdy żaden obiekt typu Engine nie istnieje

    float get_mileage() const { return mileage; }

    int get_price() const { return price; }

    friend std::ostream &operator<<(std::ostream &os, const Engine &p_engine);

    friend std::ostream &operator<<(std::ostream &os, const Type &p_type); //przeciążenie >> dla enum (wypisywanie)


};


#endif //PROJEKT_ENGINE_H
