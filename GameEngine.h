#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class Player;
class Environment;

class GameEngine {
public:
    GameEngine();
    ~GameEngine();

    bool init(const char* title, int width, int height);
    void handleEvents();
    void handlePlayerAction(const std::string& action);
    void handleEnvironmentEffects(std::string& eventMessage);
    void update();
    void render();
    void clean();
    bool isGameRunning() const { return isRunning; }

private:
    // SDL elements
    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* font;

    // Game elements
    Player* player;
    Environment* environment;
    std::string dynamicMessage;
    bool isRunning;
    bool environmentEffectApplied;
    bool shelterBuilt;

    // Textures
    SDL_Texture* backgroundTexture;
    SDL_Texture* drinkIcon;
    SDL_Texture* eatIcon;
    SDL_Texture* tent;

    // Helper functions
    void renderText(const std::string& text, int x, int y);
    SDL_Texture* loadTexture(const std::string& filePath);
    void renderImage(SDL_Texture* texture, int x, int y, int width, int height);
};

#endif // GAMEENGINE_H
