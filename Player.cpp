#include "Player.h"
#include <iostream>
#include <sstream>

Player::Player() : health(100), hunger(50), thirst(50), energy(50), shelterBuilt(false) {}

int Player::getHealth() const { return health; }
int Player::getHunger() const { return hunger; }
int Player::getThirst() const { return thirst; }
int Player::getEnergy() const { return energy; }
int Player::getScore() const { return score; }

void Player::addResource(const std::string& resource, int quantity) {
    inventory[resource] += quantity;
}

std::string Player::useResource(const std::string& resource) {
    if (inventory[resource] > 0) {
        inventory[resource]--;

        if (resource == "food") hunger += 20;
        else if (resource == "water") thirst += 20;

        return "Used 1 " + resource + ".";
    }
    else {
        return "You don't have any " + resource + " left.";
    }
}

std::string Player::forage() {
    hunger -= 10;
    thirst -= 5;
    energy -= 15;

    // Randomly gather between 0 and 1 of each resource
    addResource("food", rand() % 2);  // 0 or 1 food
    addResource("water", rand() % 2); // 0 or 1 water
    addResource("wood", rand() % 2);  // 0 or 1 wood

    return "Foraged for resources, reducing hunger, thirst, and energy.";
}

std::string Player::hunt() {
    hunger -= 15;
    thirst -= 10;
    energy -= 20;

    // Simulating the chance of an animal attack (e.g., 30% chance)
    int attackChance = rand() % 100; // Generate a random number between 0 and 99
    if (attackChance < 30) { // 30% chance to be attacked
        adjustHealth(-20); // Reduce health by 20 on attack
        return "Went hunting and obtained food, but an animal attacked!";
    }

    addResource("food", rand() % 5 + 2);
    return "Went hunting and obtained food.";
}


std::string Player::rest() {
    if (shelterBuilt) {
        energy += 30;
        hunger -= 5;
        thirst -= 5;
        return "Rested in shelter, regaining energy.";
    }
    else {
        energy += 10;
        hunger -= 10;
        thirst -= 10;
        return "Rested without shelter, regained some energy.";
    }
}

std::string Player::buildShelter() {
    if (inventory["wood"] >= 2) {
        inventory["wood"] -= 2;
        shelterBuilt = true;
        energy -= 20;
        return "Built a shelter using 2 wood. Shelter provides better rest.";
    }
    else {
        return "Not enough wood to build a shelter.";
    }
}

void Player::incrementScore() {
    score++;  // Increment score by 1
}

std::string Player::displayInventory() const {
    std::ostringstream inventoryList;
    inventoryList << "Inventory:\n";
    for (const auto& item : inventory) {
        inventoryList << item.first << ": " << item.second << std::endl;
    }
    return inventoryList.str();
}


bool Player::hasShelter() const {
    return shelterBuilt;
}

// Implementing the new methods
void Player::adjustEnergy(int amount) {
    energy += amount;
    if (energy < 0) energy = 0; // Ensure energy doesn't drop below 0
}

void Player::adjustHealth(int amount) {
    health += amount;
    if (health < 0) health = 0; // Ensure health doesn't drop below 0
}
