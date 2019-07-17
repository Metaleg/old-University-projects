//
// Created by metalleg on 11.04.18.
//

#include "Validator.h"

int Validator::set_int() {
    int arg;
    std::cin >> arg;
    std::cin.ignore(10, '\n');
    if(!(std::cin.good()))
        throw Validator();
    else
        return arg;
}

std::string Validator::set_string() {
    std::string arg;
    std::cin >> arg;
    std::cin.ignore(20, '\n');
    if(!(std::cin.good()))
        throw Validator();
    else
        return arg;
}

char Validator::set_char() {
    char arg;
    std::cin >> arg;
    std::cin.ignore(1, '\n');
    if(!(std::cin.good()))
        throw Validator();
    return arg;
}