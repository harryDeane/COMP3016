#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include "Player.h" // Ensure to include your Player class

class GameEngine {
public:
    GameEngine();  // Constructor
    bool init(const char* title, int width, int height); // Initialize SDL
    void clean(); // Clean up resources
    void handleEvents(); // Handle user input
    void render(); // Render game
    void update(); // Update game logic
    void processAction(const std::string& action); // Process player actions
    void randomEvent(); // Handle random events
    void displayStats(); // Display player stats

private:
    SDL_Window* window; // SDL Window
    SDL_Renderer* renderer; // SDL Renderer
    Player* player; // Player instance
    std::string dynamicMessage; // Message to display in-game

    void renderText(const std::string& message, int x, int y); // Render text function
};

#endif // GAME_ENGINE_H
