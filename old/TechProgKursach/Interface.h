//
// Created by metalleg on 11.04.18.
//

#ifndef TECHPROGKURSACH_INTERFACE_H
#define TECHPROGKURSACH_INTERFACE_H

#include "Director.h"
#include "PassengerAircraftBuilder.h"
#include "CombatAircraftBuilder.h"
#include "HelicopterBuilder.h"
#include "QuadcopterBuilder.h"
#include "Aircraft.h"
#include "LoadSave.h"
#include <algorithm>
#include <set>
#include <iterator>

class Interface{
    std::set<Aircraft, std::less<>> aircraft;
    std::string filename;
    char sel{};

    Interface() = default;
    ~Interface() = default;

public:
    Interface(const Interface &ls) = delete;
    Interface(Interface &&ls) = delete;
    Interface&operator=(const Interface &ls) = delete;
    Interface&operator=(Interface &&ls) = delete;

    static Interface &interface();

    void aircraft_conveyor();
    bool load();
    void create();
    void print_by_name();
    void show();
};

#endif //TECHPROGKURSACH_INTERFACE_H
