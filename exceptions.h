//
// Created by Mateusz on 08.01.2022.
//

#ifndef ZYGMUNTMATEUSZ_ETAP2_EXCEPTIONS_H
#define ZYGMUNTMATEUSZ_ETAP2_EXCEPTIONS_H

struct Vector_allocation_error : public std::exception {
    const char *what() const noexcept override { return "Allocation error."; }

    explicit Vector_allocation_error() = default;
};

struct Non_positive_value : public Vector_allocation_error {
    const char *what() const noexcept override { return "Forbidden non positive value detected."; }

    explicit Non_positive_value() = default;
};

struct Big_vector : public Vector_allocation_error {
    const char *what() const noexcept override { return "Vector too big."; }

    explicit Big_vector() = default;
};

struct No_such_vehicle : public std::exception {
    No_such_vehicle() = default;

    const char *what() const noexcept override { return "No vehicle of this name."; }
};

struct Not_enough_space : public std::exception {

    Not_enough_space() = default;

    const char *what() const noexcept override { return "Given number is bigger than factory's capacity."; }
};




#endif //ZYGMUNTMATEUSZ_ETAP2_EXCEPTIONS_H
