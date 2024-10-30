#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <map>
#include <sstream>

class Player {
public:
    Player();

    int getHealth() const;
    int getHunger() const;
    int getThirst() const;
    int getEnergy() const;
    int getScore() const;

    void addResource(const std::string& resource, int quantity);
    std::string useResource(const std::string& resource);
    std::string forage();
    std::string hunt();
    std::string rest();
    std::string buildShelter();
    std::string displayInventory() const;

    bool hasShelter() const;

    // Methods to adjust health and energy
    void adjustEnergy(int amount);
    void adjustHealth(int amount);

    //Method for score
    void incrementScore();

private:
    int health;
    int hunger;
    int thirst;
    int energy;
    int score;
    bool shelterBuilt;
    std::map<std::string, int> inventory;
};

#endif // PLAYER_H
