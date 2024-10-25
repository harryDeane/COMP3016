#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

class Environment {
public:
    Environment();
    bool isNight() const;
    bool isBadWeather() const;

    void updateTime();
    void updateWeather();

private:
    bool night;
    bool badWeather;
};

#endif
