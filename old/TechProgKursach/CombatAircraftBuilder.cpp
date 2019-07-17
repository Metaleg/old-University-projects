//
// Created by metalleg on 24.03.18.
//

#include "CombatAircraftBuilder.h"

CombatAircraftBuilder& CombatAircraftBuilder::build() {
    static CombatAircraftBuilder war;
    return war;
}

void CombatAircraftBuilder::create() {
    aircraft = std::make_shared<Aircraft>();
}

void CombatAircraftBuilder::build_name() {
    std::cout << "Enter aircraft name: ";
    aircraft->set_name(Validator::set_string());
}

void CombatAircraftBuilder::build_military_civil() {
    aircraft->set_militaty_civil("Military");
}

void CombatAircraftBuilder::build_type() {
    std::cout << "Enter aircraft type: ";
    aircraft->set_type(Validator::set_string());
}

void CombatAircraftBuilder::build_weight() {
    std::cout << "Enter takeoff weight: ";
    aircraft->set_takeoff_weight(Validator::set_int());
}

void CombatAircraftBuilder::build_engines() {
    std::cout << "Enter engines type: ";
    aircraft->set_engine_type(Validator::set_string());
    std::cout << "Enter number of engines: ";
    aircraft->set_engines(Validator::set_int());
}

void CombatAircraftBuilder::build_wings() {
    std::cout << "Enter wings location: ";
    aircraft->set_wings_location(Validator::set_string());
    std::cout << "Enter number of wings: ";
    aircraft->set_wings(Validator::set_int());
}

void CombatAircraftBuilder::build_chassis() {
    std::cout << "Enter chassis type: ";
    aircraft->set_chassis_type(Validator::set_string());
}

void CombatAircraftBuilder::build_speed() {
    std::cout << "Enter flight speed: ";
    aircraft->set_flight_speed_(Validator::set_int());
}

void CombatAircraftBuilder::build_takeoff_land() {
    std::cout << "Enter takeoff landing type: ";
    aircraft->set_takeoff_landing_type(Validator::set_string());
}

void CombatAircraftBuilder::build_control() {
    std::cout << "Enter control method: ";
    aircraft->set_control_method(Validator::set_string());
}

void CombatAircraftBuilder::build_crew() {
    std::cout << "Enter number of crew: ";
    aircraft->set_crew_(Validator::set_int());
}

void CombatAircraftBuilder::build_year() {
    std::cout << "Enter year of production: ";
    aircraft->set_year_of_product_(Validator::set_int());
}

void CombatAircraftBuilder::build_weapon() {
    std::cout << "Enter weapon type: ";
    aircraft->set_weapon_type(Validator::set_string());
}