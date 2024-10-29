#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <unordered_map>

class Player {
public:
    Player();

    int getHealth() const;
    int getHunger() const;
    int getThirst() const;
    int getEnergy() const;

    void addResource(const std::string& resource, int quantity);
    void useResource(const std::string& resource);

    void displayInventory() const;
    void forage();
    void hunt();
    void rest();
    void buildShelter();
    void displayStats() const;

    bool hasShelter() const { return shelterBuilt; }
    void adjustHealth(int amount) { health += amount; }
    void adjustEnergy(int amount) { energy += amount; }

private:
    int health;
    int hunger;
    int thirst;
    int energy;
    bool shelterBuilt;
    std::unordered_map<std::string, int> inventory;
};

#endif // PLAYER_H
