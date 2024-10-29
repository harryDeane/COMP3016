#include "Player.h"
#include <iostream>

Player::Player() : health(100), hunger(50), thirst(50), energy(50), shelterBuilt(false) {}

int Player::getHealth() const { return health; }
int Player::getHunger() const { return hunger; }
int Player::getThirst() const { return thirst; }
int Player::getEnergy() const { return energy; }

void Player::addResource(const std::string& resource, int quantity) {
    inventory[resource] += quantity;  // Add resource to inventory
    std::cout << "Collected " << quantity << " " << resource << "(s).\n";
}

void Player::useResource(const std::string& resource) {
    if (inventory[resource] > 0) {
        inventory[resource]--;
        std::cout << "Used 1 " << resource << ".\n";

        // Effects of using resources (example logic)
        if (resource == "food") hunger += 20;
        else if (resource == "water") thirst += 20;
    }
    else {
        std::cout << "You don't have any " << resource << " left.\n";
    }
}

void Player::displayInventory() const {
    std::cout << "Inventory:\n";
    for (const auto& item : inventory) {
        std::cout << item.first << ": " << item.second << std::endl;
    }
}

void Player::forage() {
    std::cout << "Foraging for food, water, and wood...\n";
    hunger -= 10;  // Foraging reduces hunger
    thirst -= 5;   // Foraging reduces thirst
    energy -= 15;  // Foraging reduces energy

    // Simulate finding resources
    addResource("food", rand() % 3 + 1);
    addResource("water", rand() % 3 + 1);
    addResource("wood", rand() % 2 + 1);
}

void Player::hunt() {
    std::cout << "Hunting for food...\n";
    hunger -= 15;  // Hunting reduces hunger
    thirst -= 10;  // Hunting reduces thirst
    energy -= 20;  // Hunting reduces energy

    // Simulate successful hunt
    addResource("food", rand() % 5 + 2);
}

void Player::rest() {
    std::cout << "Resting to regain energy...\n";
    if (shelterBuilt) {
        energy += 30;  // Resting in shelter regains more energy
        hunger -= 5;   // Resting reduces hunger
        thirst -= 5;   // Resting reduces thirst
    }
    else {
        energy += 10;  // Resting without shelter regains less energy
        hunger -= 10;  // Resting reduces hunger more without shelter
        thirst -= 10;  // Resting reduces thirst more without shelter
    }
}

void Player::buildShelter() {
    if (inventory["wood"] >= 2) {
        std::cout << "Building a shelter...\n";
        inventory["wood"] -= 2;  // Use 2 wood to build shelter
        shelterBuilt = true;     // Set shelter built flag
        energy -= 20;            // Building shelter reduces energy
    }
    else {
        std::cout << "Not enough wood to build a shelter.\n";
    }
}
