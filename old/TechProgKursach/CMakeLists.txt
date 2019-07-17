cmake_minimum_required(VERSION 3.9)
project(TechProgKursach)

set(CMAKE_CXX_STANDARD 14)

add_executable(TechProgKursach main.cpp AircraftBuilder.h Aircraft.cpp Aircraft.h PassengerAircraftBuilder.cpp PassengerAircraftBuilder.h Director.cpp Director.h CombatAircraftBuilder.cpp CombatAircraftBuilder.h AircraftBuilder.cpp HelicopterBuilder.cpp HelicopterBuilder.h QuadcopterBuilder.cpp QuadcopterBuilder.h LoadSave.cpp LoadSave.h Interface.cpp Interface.h Validator.cpp Validator.h)