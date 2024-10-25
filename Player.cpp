#include "Player.h"

Player::Player() : health(100), hunger(50), thirst(50), energy(50), shelterBuilt(false) {}

int Player::getHealth() const { return health; }
int Player::getHunger() const { return hunger; }
int Player::getThirst() const { return thirst; }
int Player::getEnergy() const { return energy; }

void Player::adjustHealth(int amount) {
    health += amount;
    if (health < 0) health = 0;
    if (health > 100) health = 100;
}

void Player::adjustEnergy(int amount) {
    energy += amount;
    if (energy < 0) energy = 0;
    if (energy > 100) energy = 100;
}

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
    addResource("food", 1);     // Find food
    addResource("water", 1);    // Find water

    // Random chance to find wood (e.g., 50% chance)
    if (rand() % 2 == 0) {
        addResource("wood", 1);  // Find wood
        std::cout << "You found some wood!\n";
    }
    else {
        std::cout << "No wood found this time.\n";
    }
}

void Player::hunt() {
    std::cout << "Hunting for food...\n";
    hunger -= 20;
    energy -= 25;

    // Simulate finding food after hunting
    addResource("food", 2);
}

void Player::rest() {
    std::cout << "Resting to regain energy...\n";
    energy += 30;
    if (energy > 100) energy = 100;  // Energy cannot exceed 100
    hunger -= 10;
    thirst -= 10;
}

void Player::buildShelter() {
    if (inventory["wood"] >= 2) {  // Requires 2 wood
        std::cout << "Building shelter...\n";
        energy -= 20;
        hunger -= 10;
        inventory["wood"] -= 2;  // Deduct 2 wood from inventory
        shelterBuilt = true;
        std::cout << "Shelter built successfully!\n";
    }
    else {
        std::cout << "You don't have enough wood to build a shelter. You need at least 2 wood.\n";
    }
}

void Player::displayStats() const {
    std::cout << "Player Stats: Health = " << health
        << ", Hunger = " << hunger
        << ", Thirst = " << thirst
        << ", Energy = " << energy << std::endl;
}
