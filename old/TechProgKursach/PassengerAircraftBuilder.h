//
// Created by metalleg on 24.03.18.
//

#ifndef TECHPROGKURSACH_PASSENGERPLANEBUILDER_H
#define TECHPROGKURSACH_PASSENGERPLANEBUILDER_H

#include "AircraftBuilder.h"

class PassengerAircraftBuilder:public AircraftBuilder{
    friend class Director;

    PassengerAircraftBuilder() = default;
    ~PassengerAircraftBuilder() = default;

    void create() override;
    void build_name() override;
    void build_military_civil() override;
    void build_type() override;
    void build_weight() override;
    void build_engines() override;
    void build_wings() override;
    void build_chassis() override;
    void build_speed() override;
    void build_takeoff_land() override;
    void build_control() override;
    void build_crew() override;
    void build_year() override;

public:
    PassengerAircraftBuilder(const PassengerAircraftBuilder& pas) = delete;
    PassengerAircraftBuilder(PassengerAircraftBuilder&& pas) = delete;
    PassengerAircraftBuilder&operator=(const PassengerAircraftBuilder& pas) = delete;
    PassengerAircraftBuilder&operator=(PassengerAircraftBuilder&& pas) = delete;

    static PassengerAircraftBuilder& build();
};
#endif //TECHPROGKURSACH_PASSENGERPLANEBUILDER_H
