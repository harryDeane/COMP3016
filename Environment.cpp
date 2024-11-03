#include "Environment.h"
#include <cstdlib>  // for rand()

Environment::Environment() : night(false), badWeather(false) {}

bool Environment::isNight() const { return night; }
bool Environment::isBadWeather() const { return badWeather; }

void Environment::updateTime() {
    // Randomly switch between day and night
    night = rand() % 2;
}

void Environment::updateWeather() {
    // Randomly decide if the weather is bad
    badWeather = rand() % 2;
}
