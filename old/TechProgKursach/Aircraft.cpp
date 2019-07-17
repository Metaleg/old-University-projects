//
// Created by metalleg on 24.03.18.
//

#include "Aircraft.h"

Aircraft::Aircraft() noexcept {
    name_ = "";
    military_civil_ = "";
    type_ = "";
    takeoff_weight_ = 0;
    engines_ = 0;
    engine_type_ = "";
    wings_ = 0;
    wings_location_ = "none";
    chassis_type_ = "none";
    flight_speed_ = 0;
    takeoff_landing_type_ = "";
    control_method_ = "";
    crew_ = 0;
    year_of_product_ = 0;
    weapon_type_ = "none";
}

Aircraft::Aircraft(std::string &name) noexcept {
    name_ = std::move(name);
    military_civil_ = "";
    type_ = "";
    takeoff_weight_ = 0;
    engines_ = 0;
    engine_type_ = "";
    wings_ = 0;
    wings_location_ = "none";
    chassis_type_ = "none";
    flight_speed_ = 0;
    takeoff_landing_type_ = "";
    control_method_ = "";
    crew_ = 0;
    year_of_product_ = 0;
    weapon_type_ = "none";
}

Aircraft::Aircraft(const Aircraft &aircraft) noexcept {
    name_ = aircraft.name_;
    military_civil_ = aircraft.military_civil_;
    type_ = aircraft.type_;
    takeoff_weight_ = aircraft.takeoff_weight_;
    engines_ = aircraft.engines_;
    engine_type_ = aircraft.engine_type_;
    wings_ = aircraft.wings_;
    wings_location_ = aircraft.wings_location_;
    chassis_type_ = aircraft.chassis_type_;
    flight_speed_ = aircraft.flight_speed_;
    takeoff_landing_type_ = aircraft.takeoff_landing_type_;
    control_method_ = aircraft.control_method_;
    crew_ = aircraft.crew_;
    year_of_product_ = aircraft.year_of_product_;
    weapon_type_=  aircraft.weapon_type_;
}

Aircraft::Aircraft(Aircraft &&plane) noexcept {
    *this = std::move(plane);
}

Aircraft &Aircraft::operator=(Aircraft&& plane) noexcept {
    name_ = plane.name_;
    military_civil_ = plane.military_civil_;
    type_ = plane.type_;
    takeoff_weight_ = plane.takeoff_weight_;
    engines_ = plane.engines_;
    engine_type_ = plane.engine_type_;
    wings_ = plane.wings_;
    wings_location_ = plane.wings_location_;
    chassis_type_ = plane.chassis_type_;
    flight_speed_ = plane.flight_speed_;
    takeoff_landing_type_ = plane.takeoff_landing_type_;
    control_method_ = plane.control_method_;
    crew_ = plane.crew_;
    year_of_product_ = plane.year_of_product_;
    weapon_type_=  plane.weapon_type_;

    plane.name_ = "";
    plane.military_civil_ = "";
    plane.type_ = "";
    plane.takeoff_weight_ = 0;
    plane.engines_ = 0;
    plane.engine_type_ = "";
    plane.wings_ = 0;
    plane.wings_location_ = "none";
    plane.chassis_type_ = "none";
    plane.flight_speed_ = 0;
    plane.takeoff_landing_type_ = "";
    plane.control_method_ = "";
    plane.crew_ = 0;
    plane.year_of_product_ = 0;
    plane.weapon_type_ = "none";

    return *this;
}

std::ostream &operator<<(std::ostream &os, const Aircraft &plane) {
    os << std::endl << plane.name_ << ", " << plane.military_civil_ <<", " << "type " << plane.type_ <<std::endl
       << "takeoff weight: " << plane.takeoff_weight_ << " kilograms" << std::endl
       << plane.engines_ << " engines, " << "type " << plane.engine_type_ << std::endl
       << plane.wings_ << " wings, " << "locating in " << plane.wings_location_ << std::endl
       << "type of chassis: " << plane.chassis_type_ << std::endl
       << "flight speed: " << plane.flight_speed_ << " km/h" << std::endl
       << "type of takeoff landing: " << plane.takeoff_landing_type_ << std::endl
       << "method of control: " << plane.control_method_ << std::endl
       << "crew of " << plane.crew_ << " people" << std::endl
       << plane.year_of_product_ << " year of production" << std::endl
       << "type of weapon: " << plane.weapon_type_ << std::endl;
    return os;
}

bool Aircraft::operator==(const Aircraft &rhs) const {
    return  name_ == rhs.name_ ;
}

bool Aircraft::operator!=(const Aircraft &rhs) const {
    return !(rhs == *this);
}

bool Aircraft::operator<(const Aircraft &rhs) const {
    return this->name_ < rhs.name_;
}

bool Aircraft::operator>(const Aircraft &rhs) const {
    return this->name_ > rhs.name_;
}

void Aircraft::set_name(const std::string &name) {
    name_ = name;
}

void Aircraft::set_militaty_civil(const std::string &military_civil) {
    military_civil_ = military_civil;
}

void Aircraft::set_type(const std::string &type) {
    type_ = type;
}

void Aircraft::set_takeoff_weight(int takeoff_weight) {
    Aircraft::takeoff_weight_ = takeoff_weight;
}

void Aircraft::set_engines(int engines) {
    Aircraft::engines_ = engines;
}

void Aircraft::set_engine_type(const std::string &engine_type) {
    engine_type_ = engine_type;
}

void Aircraft::set_wings(int wings) {
    Aircraft::wings_ = wings;
}

void Aircraft::set_wings_location(const std::string &wings_location) {
    wings_location_ = wings_location;
}

void Aircraft::set_chassis_type(const std::string &chassis_type) {
    chassis_type_ = chassis_type;
}

void Aircraft::set_flight_speed_(int flight_speed) {
    Aircraft::flight_speed_ = flight_speed;
}

void Aircraft::set_takeoff_landing_type(const std::string &takeoff_landing_type) {
    takeoff_landing_type_ = takeoff_landing_type;
}

void Aircraft::set_control_method(const std::string &control_method) {
    control_method_ = control_method;
}

void Aircraft::set_crew_(int crew) {
    Aircraft::crew_ = crew;
}

void Aircraft::set_year_of_product_(int year_of_product) {
    Aircraft::year_of_product_ = year_of_product;
}

void Aircraft::set_weapon_type(const std::string &weapon_type) {
    weapon_type_ = weapon_type;
}

const std::string &Aircraft::get_name() const {
    return name_;
}

const std::string &Aircraft::get_military_civil() const {
    return military_civil_;
}

const std::string &Aircraft::get_type() const {
    return type_;
}

int Aircraft::get_takeoff_weight() const {
    return takeoff_weight_;
}

int Aircraft::get_engines() const {
    return engines_;
}

const std::string &Aircraft::get_engine_type() const {
    return engine_type_;
}

int Aircraft::get_wings() const {
    return wings_;
}

const std::string &Aircraft::get_wings_location() const {
    return wings_location_;
}

const std::string &Aircraft::get_chassis_type() const {
    return chassis_type_;
}

int Aircraft::get_flight_speed() const {
    return flight_speed_;
}

const std::string &Aircraft::get_takeoff_landing_type() const {
    return takeoff_landing_type_;
}

const std::string &Aircraft::get_control_method() const {
    return control_method_;
}

int Aircraft::get_crew() const {
    return crew_;
}

int Aircraft::get_year_of_product() const {
    return year_of_product_;
}

const std::string &Aircraft::get_weapon_type() const {
    return weapon_type_;
}
