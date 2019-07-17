//
// Created by metalleg on 24.03.18.
//

#include "Director.h"

Director& Director::direct() {
        static Director dir;
        return dir;
}

std::shared_ptr<Aircraft> Director::construct(AircraftBuilder& aircraftBuilder) {
        aircraftBuilder.create();
        aircraftBuilder.build_name();
        aircraftBuilder.build_military_civil();
        aircraftBuilder.build_type();
        aircraftBuilder.build_weight();
        aircraftBuilder.build_engines();
        aircraftBuilder.build_wings();
        aircraftBuilder.build_chassis();
        aircraftBuilder.build_speed();
        aircraftBuilder.build_takeoff_land();
        aircraftBuilder.build_control();
        aircraftBuilder.build_crew();
        aircraftBuilder.build_year();
        aircraftBuilder.build_weapon();

        return aircraftBuilder.get();
}
