//
// Created by metalleg on 24.03.18.
//

#include "HelicopterBuilder.h"

HelicopterBuilder& HelicopterBuilder::build() {
    static HelicopterBuilder hel;
    return hel;
}

void HelicopterBuilder::create() {
    aircraft = std::make_shared<Aircraft>();
}

void HelicopterBuilder::build_name() {
    std::cout << "Enter helicopter name: ";
    aircraft->set_name(Validator::set_string());
}

void HelicopterBuilder::build_military_civil() {
    std::cout << "Enter helicopter type: military or civil: ";
    aircraft->set_militaty_civil(Validator::set_string());
}

void HelicopterBuilder::build_type() {
    std::cout << "Enter helicopter type: ";
    aircraft->set_type(Validator::set_string());
}

void HelicopterBuilder::build_weight() {
    std::cout << "Enter takeoff weight: ";
    aircraft->set_takeoff_weight(Validator::set_int());
}

void HelicopterBuilder::build_engines() {
    std::cout << "Enter engines type: ";
    aircraft->set_engine_type(Validator::set_string());
    std::cout << "Enter number of engines: ";
    aircraft->set_engines(Validator::set_int());
}

void HelicopterBuilder::build_chassis() {
    std::cout << "Enter chassis type: ";
    aircraft->set_chassis_type(Validator::set_string());
}

void HelicopterBuilder::build_speed() {
    std::cout << "Enter flight speed: ";
    aircraft->set_flight_speed_(Validator::set_int());
}

void HelicopterBuilder::build_takeoff_land() {
    aircraft->set_takeoff_landing_type("Vertical take-off");
}

void HelicopterBuilder::build_control() {
    std::cout << "Enter control method: ";
    aircraft->set_control_method(Validator::set_string());
}

void HelicopterBuilder::build_crew() {
    std::cout << "Enter number of crew: ";
    aircraft->set_crew_(Validator::set_int());
}

void HelicopterBuilder::build_year() {
    std::cout << "Enter year of production: ";
    aircraft->set_year_of_product_(Validator::set_int());
}

void HelicopterBuilder::build_weapon() {
    std::cout << "Enter weapon type: ";
    aircraft->set_weapon_type(Validator::set_string());
}