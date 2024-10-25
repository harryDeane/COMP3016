#include "GameEngine.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <limits>

// Constructor
GameEngine::GameEngine() : player(new Player()), window(nullptr), renderer(nullptr) {}

// Initialize SDL, create window and renderer
bool GameEngine::init(const char* title, int width, int height) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Create window
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Create renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Initialize TTF
    if (TTF_Init() == -1) {
        std::cout << "TTF could not initialize! TTF_Error: " << TTF_GetError() << std::endl;
        return false;
    }

    return true;
}

// Clean up SDL resources
void GameEngine::clean() {
    SDL_DestroyRenderer(renderer);  // Destroy the renderer
    SDL_DestroyWindow(window);      // Destroy the window
    TTF_Quit();                     // Quit TTF subsystems
    SDL_Quit();                     // Quit SDL subsystems
}

// Handle events such as user input
void GameEngine::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            // Handle quit event
            clean();
            exit(0);
        }
    }
}

// Render text to the screen
void GameEngine::renderText(const std::string& message, int x, int y) {
    TTF_Font* font = TTF_OpenFont("assets/fonts/font.ttf", 24);  // Load a font
    if (!font) {
        std::cout << "Failed to load font! TTF_Error: " << TTF_GetError() << std::endl;
        return;
    }

    SDL_Color color = { 255, 255, 255 }; // White color
    SDL_Surface* surface = TTF_RenderText_Solid(font, message.c_str(), color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    int textWidth = surface->w;
    int textHeight = surface->h;

    SDL_Rect dstrect = { x, y, textWidth, textHeight };
    SDL_RenderCopy(renderer, texture, NULL, &dstrect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);
}

// Render the game
void GameEngine::render() {
    // Clear screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black color
    SDL_RenderClear(renderer);

    // Display player stats
    displayStats();

    // Render any additional dynamic messages or events here
    renderText(dynamicMessage, 10, 50); // Example position

    // Present the back buffer
    SDL_RenderPresent(renderer);
}

// Display player stats at the top of the screen
void GameEngine::displayStats() {
    std::string stats = "Health: " + std::to_string(player->getHealth()) +
        ", Hunger: " + std::to_string(player->getHunger()) +
        ", Thirst: " + std::to_string(player->getThirst()) +
        ", Energy: " + std::to_string(player->getEnergy());
    renderText(stats, 10, 10); // Render stats at position (10, 10)
}

// Process player actions and random events
void GameEngine::processAction(const std::string& action) {
    if (action == "forage") {
        player->forage();
        randomEvent(); // Check for random events
    }
    else if (action == "sleep") {
        if (player->hasShelter()) {
            player->rest();
        }
        else {
            dynamicMessage = "You need to build a shelter to sleep!";
        }
    }
    else if (action == "build shelter") {
        player->buildShelter();
    }
    else if (action == "hunt") {
        player->hunt();
        randomEvent(); // Check for random events
    }
    else if (action == "consume food" || action == "consume water") {
        player->useResource(action == "consume food" ? "food" : "water");
    }
    else {
        dynamicMessage = "Invalid action! Please choose a valid option.";
    }
}

// Generate random events during gameplay
void GameEngine::randomEvent() {
    int eventChance = rand() % 100;
    if (eventChance < 20) { // 20% chance for an event
        dynamicMessage = "A wild animal appears!";
        // Implement logic for the player to encounter the animal
        // Example: decrease health or energy based on encounter
        player->adjustHealth(-10); // Adjust health as an example
    }
    else {
        dynamicMessage = "Nothing special happened.";
    }
}

// Main game loop
void GameEngine::update() {
    std::string action;
    std::cout << "Enter your action (forage, sleep, build shelter, hunt, consume food, consume water): ";
    std::getline(std::cin, action);
    processAction(action);
}

// Main function to run the game
int main(int argc, char* argv[]) {
    GameEngine game;
    if (!game.init("Survival Game", 800, 600)) {
        return -1; // Initialization failed
    }

    // Main game loop
    while (true) {
        game.handleEvents();
        game.update();
        game.render();
    }

    game.clean();
    return 0;
}
