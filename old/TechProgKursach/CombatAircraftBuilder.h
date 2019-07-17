//
// Created by metalleg on 24.03.18.
//

#ifndef TECHPROGKURSACH_COMBATAIRCRAFTBUILDER_H
#define TECHPROGKURSACH_COMBATAIRCRAFTBUILDER_H

#include "AircraftBuilder.h"
class CombatAircraftBuilder:public AircraftBuilder{
    friend class Director;

    CombatAircraftBuilder() = default;
    ~CombatAircraftBuilder() = default;

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
    void build_weapon() override;

public:
    CombatAircraftBuilder(const CombatAircraftBuilder& pas) = delete;
    CombatAircraftBuilder(CombatAircraftBuilder&& pas) = delete;
    CombatAircraftBuilder&operator=(const CombatAircraftBuilder& pas) = delete;
    CombatAircraftBuilder&operator=(CombatAircraftBuilder&& pas) = delete;

    static CombatAircraftBuilder&build();
};

#endif //TECHPROGKURSACH_COMBATAIRCRAFTBUILDER_H
