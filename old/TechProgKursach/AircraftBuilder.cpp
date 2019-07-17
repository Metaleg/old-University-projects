//
// Created by metalleg on 24.03.18.
//

#include "AircraftBuilder.h"

std::shared_ptr<Aircraft>AircraftBuilder::get() noexcept {
    return aircraft;
}
