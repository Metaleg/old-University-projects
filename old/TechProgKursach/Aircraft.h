//
// Created by metalleg on 24.03.18.
//

#ifndef TECHPROGKURSACH_AIRCRAFT_H
#define TECHPROGKURSACH_AIRCRAFT_H

#include "Validator.h"
#include <iostream>
#include <iomanip>

class Aircraft{
    std::string name_;
    std::string military_civil_;
    std::string type_;
    int takeoff_weight_;
    int engines_;
    std::string engine_type_;
    int wings_;
    std::string wings_location_;
    std::string chassis_type_;
    int flight_speed_;
    std::string takeoff_landing_type_;
    std::string control_method_;
    int crew_;
    int year_of_product_;
    std::string weapon_type_;

public:
    Aircraft() noexcept;
    explicit Aircraft(std::string &name) noexcept;
    Aircraft(const Aircraft &aircraft) noexcept;
    Aircraft(Aircraft &&plane) noexcept;
    Aircraft&operator=(const Aircraft &plane) = default;
    Aircraft&operator=(Aircraft &&plane) noexcept;
    ~Aircraft() = default;

    void set_name(const std::string &name);
    void set_militaty_civil(const std::string &military_civil);
    void set_type(const std::string &type);
    void set_takeoff_weight(int takeoff_weight);
    void set_engines(int engines);
    void set_engine_type(const std::string &engine_type);
    void set_wings(int wings);
    void set_wings_location(const std::string &wings_location);
    void set_chassis_type(const std::string &chassis_type);
    void set_flight_speed_(int flight_speed);
    void set_takeoff_landing_type(const std::string &takeoff_landing_type);
    void set_control_method(const std::string &control_method);
    void set_crew_(int crew);
    void set_year_of_product_(int year_of_product);
    void set_weapon_type(const std::string &weapon_type);

    const std::string &get_name() const;
    const std::string &get_military_civil() const;
    const std::string &get_type() const;
    int get_takeoff_weight() const;
    int get_engines() const;
    const std::string &get_engine_type() const;
    int get_wings() const;
    const std::string &get_wings_location() const;
    const std::string &get_chassis_type() const;
    int get_flight_speed() const;
    const std::string &get_takeoff_landing_type() const;
    const std::string &get_control_method() const;
    int get_crew() const;
    int get_year_of_product() const;
    const std::string &get_weapon_type() const;

    friend std::ostream &operator<<(std::ostream &os, const Aircraft &plane);
    bool operator<(const Aircraft &rhs) const;
    bool operator>(const Aircraft &rhs) const;
    bool operator==(const Aircraft &rhs) const;
    bool operator!=(const Aircraft &rhs) const;
};

#endif //TECHPROGKURSACH_AIRCRAFT_H