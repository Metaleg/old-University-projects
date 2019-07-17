//
// Created by metalleg on 24.03.18.
//

#ifndef TECHPROGKURSACH_AIRCRAFTBUILDER_H
#define TECHPROGKURSACH_AIRCRAFTBUILDER_H

#include "Aircraft.h"
#include <memory>

class AircraftBuilder{
protected:
    std::shared_ptr<Aircraft> aircraft;
public:
    virtual void create() = 0;
    virtual void build_name() = 0;
    virtual void build_military_civil() = 0;
    virtual void build_type() = 0;
    virtual void build_weight() = 0;
    virtual void build_engines() = 0;
    virtual void build_wings(){};
    virtual void build_chassis(){};
    virtual void build_speed() = 0;
    virtual void build_takeoff_land() = 0;
    virtual void build_control() = 0;
    virtual void build_crew(){};
    virtual void build_year() = 0;
    virtual void build_weapon(){};
    virtual std::shared_ptr<Aircraft> get() noexcept;
};

#endif //TECHPROGKURSACH_AIRCRAFTBUILDER_H