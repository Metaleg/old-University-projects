//
// Created by metalleg on 24.03.18.
//

#ifndef TECHPROGKURSACH_HELICOPTERBUILDER_H
#define TECHPROGKURSACH_HELICOPTERBUILDER_H

#include "AircraftBuilder.h"

class HelicopterBuilder:public AircraftBuilder{
    friend class Director;

    HelicopterBuilder() = default;
    ~HelicopterBuilder() = default;

    void create() override;
    void build_name() override;
    void build_military_civil() override;
    void build_type() override;
    void build_weight() override;
    void build_engines() override;
    void build_chassis() override;
    void build_speed() override;
    void build_takeoff_land() override;
    void build_control() override;
    void build_crew() override;
    void build_year() override;
    void build_weapon() override;

public:
    HelicopterBuilder(const HelicopterBuilder& pas) = delete;
    HelicopterBuilder(HelicopterBuilder&& pas) = delete;
    HelicopterBuilder&operator=(const HelicopterBuilder& pas) = delete;
    HelicopterBuilder&operator=(HelicopterBuilder&& pas) = delete;

    static HelicopterBuilder& build();
};


#endif //TECHPROGKURSACH_HELICOPTERBUILDER_H
