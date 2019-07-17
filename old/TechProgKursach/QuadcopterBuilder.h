//
// Created by metalleg on 24.03.18.
//

#ifndef TECHPROGKURSACH_QUADCOPTERBUILDER_H
#define TECHPROGKURSACH_QUADCOPTERBUILDER_H

#include "AircraftBuilder.h"

class QuadcopterBuilder:public AircraftBuilder{
    friend class Director;

    QuadcopterBuilder() = default;
    ~QuadcopterBuilder() = default;

    void create() override;
    void build_name() override;
    void build_military_civil() override;
    void build_type() override;
    void build_weight() override;
    void build_engines() override;
    void build_speed() override;
    void build_takeoff_land() override;
    void build_control() override;
    void build_year() override;
    void build_weapon() override;

public:
    QuadcopterBuilder(const QuadcopterBuilder& pas) = delete;
    QuadcopterBuilder(QuadcopterBuilder&& pas) = delete;
    QuadcopterBuilder&operator=(const QuadcopterBuilder& pas) = delete;
    QuadcopterBuilder&operator=(QuadcopterBuilder&& pas) = delete;

    static QuadcopterBuilder& build();
};


#endif //TECHPROGKURSACH_QUADCOPTERBUILDER_H
