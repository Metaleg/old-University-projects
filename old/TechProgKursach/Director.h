//
// Created by metalleg on 24.03.18.
//

#ifndef TECHPROGKURSACH_DIRECTOR_H
#define TECHPROGKURSACH_DIRECTOR_H

#include "AircraftBuilder.h"

class Director{
    Director() = default;
    ~Director() = default;
public:
    Director(const Director& dir) = delete;
    Director(Director&& dir) = delete;
    Director&operator=(const Director& dir) = delete;
    Director&operator=(Director&& dir) = delete;

    static Director& direct();
    std::shared_ptr<Aircraft> construct(AircraftBuilder& aircraftBuilder);
};

#endif //TECHPROGKURSACH_DIRECTOR_H