#pragma once
#include <string>
#include <unordered_map>
#include <iostream>

class Player {
public:
    Player();
    int getHealth() const;
    int getHunger() const;
    int getThirst() const;
    int getEnergy() const;
    void adjustHealth(int amount);
    void adjustEnergy(int amount);
    void addResource(const std::string& resource, int quantity);
    void useResource(const std::string& resource);
    void displayInventory() const;
    void forage();
    void hunt();
    void rest();
    void buildShelter();
    void displayStats() const;
    bool hasShelter() const { return shelterBuilt; }

private:
    int health;
    int hunger;
    int thirst;
    int energy;
    bool shelterBuilt;
    std::unordered_map<std::string, int> inventory;
};
