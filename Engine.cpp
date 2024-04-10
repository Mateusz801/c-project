//
// Created by Mateusz on 26.11.2021.
//

#include "Engine.h"

using namespace std;

Engine::Engine() = default;

Engine::Engine(int ww, int pp, float mm, int pr, Engine::Type tt) : weight(ww), power(pp), mileage(mm), price(pr),
                                                                    type(tt) {}


Engine Engine::create_engine() {
    Type p_type = static_cast<Type>(rand() % 4);

    switch (p_type) { //typy silników mają predefiniowane składowe, niezależne od użytkownika
        case Type::V6: {
            return {120, 200, 6.8, 15000, p_type};
        }
        case Type::V8: {
            return {160, 400, 7.4, 25000, p_type};
        }
        case Type::V10: {
            return {180, 500, 8.4, 40000, p_type};
        }
        case Type::V12: {
            return {200, 600, 9.5, 70000, p_type};
        }
        default:
            return {0, 0, 0, 0, Type::V6};
    }
}

ostream &operator<<(ostream &os, const Engine &p_engine) {
    os << "Engine of type " << p_engine.type << " which weights " << p_engine.weight << "kg and has power of "
       << p_engine.power << "KM.";
    return os;
}

ostream &operator<<(ostream &os, const Engine::Type &p_type) {
    switch (p_type) {
        case Engine::Type::V6: {
            os << "V6";
            break;
        }
        case Engine::Type::V8: {
            os << "V8";
            break;
        }
        case Engine::Type::V10: {
            os << "V10";
            break;
        }
        case Engine::Type::V12: {
            os << "V12";
            break;
        }
    }
    return os;
}


