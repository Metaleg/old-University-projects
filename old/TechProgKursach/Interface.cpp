//
// Created by metalleg on 11.04.18.
//

#include "Interface.h"

Interface &Interface::interface() {
    static Interface inter;
    return inter;
}

void Interface::aircraft_conveyor(){
    std::cout << "-----------Aircraft conveyor-----------\n";

    while(sel != 'e'){
        std::cout << "\nChoose: c - create one or few aircraft;\n"
                  << "        s - show all aircrafts by type;\n"
                  << "        p - print by name;\n"
                  << "        e - exit;\n";
        std::cout << "Your choice: ";   sel = Validator::set_char();

        switch(sel){
            case 'c':
                create();
                break;
            case 's':
                show();
                break;
            case 'p':
                print_by_name();
                break;
            case 'e':
                std::cout << "Exit\n";
                break;
            default:
                std::cerr << "Error! Please, enter correct command!\n";
                break;
        }
    }
}

bool Interface::load(){
    LoadSave &ls = LoadSave::loadsave();

    std::cout << "Enter type of aircrafts: p - passenger aircraft\n"
              << "                         c - combat aircraft\n"
              << "                         h - helicopter\n"
              << "                         q - quadcopter\n";
    std::cout << "Your choice: ";   sel = Validator::set_char();

    switch (sel){
        case 'p':
            filename = "passenger_aircraft.xml";
            break;
        case 'c':
            filename = "combat_aircraft.xml";
            break;
        case 'h':
            filename = "helicopter.xml";
            break;
        case 'q':
            filename = "quadcopter.xml";
            break;
        default:
            std::cerr << "Error! Invalid type!\n";
            return false;
    }
    return ls.load(aircraft, filename);
}

void Interface::create(){
    PassengerAircraftBuilder &pas = PassengerAircraftBuilder::build();
    CombatAircraftBuilder &comb = CombatAircraftBuilder::build();
    HelicopterBuilder &hel = HelicopterBuilder::build();
    QuadcopterBuilder &quad = QuadcopterBuilder::build();
    Director &dir = Director::direct();
    LoadSave &ls = LoadSave::loadsave();
    std::shared_ptr<Aircraft> pl;
    Aircraft p;

    int qnt = 0;
    load();
    std::cout << "Enter quantity of aircrafts: "; qnt = Validator::set_int();
    switch (sel){
        case 'p':
            for (int i = 0; i < qnt; ++i){
                std::cout << 'N' << i + 1 << std::endl;
                pl = dir.construct(pas);
                p = *pl;
                aircraft.emplace(p);
            }
            break;

        case 'c':
            for (int i = 0; i < qnt; ++i){
                std::cout << 'N' << i + 1 << std::endl;
                pl = dir.construct(comb);
                p = *pl;
                aircraft.emplace(p);
            }
            break;
        case 'h':
            for (int i = 0; i < qnt; ++i){
                std::cout << 'N' << i + 1 << std::endl;
                pl = dir.construct(hel);
                p = *pl;
                aircraft.emplace(p);
            }
            break;
        case 'q':
            for (int i = 0; i < qnt; ++i){
                std::cout << 'N' << i + 1 << std::endl;
                pl = dir.construct(quad);
                p = *pl;
                aircraft.emplace(p);
            }
            break;
        default:
            std::cerr << "Error! Invalid type!\n";
            return;
    }
    ls.save(aircraft, filename);
    aircraft.clear();
}

void Interface::print_by_name(){
    if (!load())
        return;

    std::set<Aircraft, std::less<>>::const_iterator iter;

    std::string search_name;
    std::cout << "Enter search name: "; search_name = Validator::set_string();
    Aircraft search(search_name);
    iter = aircraft.lower_bound(search);
    while (iter != aircraft.upper_bound(search))
        std::cout << *iter++ << std::endl;
    aircraft.clear();
    std::cout << "\nPrint is successful\n";
}

void Interface::show(){
    if (!load())
        return;

    for(auto &it : aircraft)
        std::cout << it;
    aircraft.clear();
    std::cout << "\nShow is successful\n";
}