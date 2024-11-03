#include "GameEngine.h"
#include "Player.h"
#include "Environment.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <iostream>
#include <sstream>
#include <fstream>

GameEngine::GameEngine()
    : window(nullptr), renderer(nullptr), font(nullptr), isRunning(true), environmentEffectApplied(false),
    backgroundTexture(nullptr), drinkIcon(nullptr), eatIcon(nullptr), tent(nullptr), shelterBuilt(false), highScore(0) {
    
    player = new Player();
    environment = new Environment();
    dynamicMessage = "Welcome to the Survival Game!";
    loadHighScore();
}

GameEngine::~GameEngine() {
    delete player;
    delete environment;
}

bool GameEngine::init(const char* title, int width, int height) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cout << "SDL Init Error: " << SDL_GetError() << std::endl;
        return false;
    }

    if (TTF_Init() == -1) {
        std::cout << "TTF Init Error: " << TTF_GetError() << std::endl;
        return false;
    }

    if (IMG_Init(IMG_INIT_PNG) == 0) {
        std::cout << "IMG Init Error: " << IMG_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cout << "Window Creation Error: " << SDL_GetError() << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cout << "Renderer Creation Error: " << SDL_GetError() << std::endl;
        return false;
    }

    font = TTF_OpenFont("assets/fonts/font.ttf", 24);
    if (!font) {
        std::cout << "Font Loading Error: " << TTF_GetError() << std::endl;
        return false;
    }

    backgroundTexture = loadTexture("assets/images/background.png");
    drinkIcon = loadTexture("assets/images/drink_icon.png");
    eatIcon = loadTexture("assets/images/eat_icon.png");
    tent = loadTexture("assets/images/tent.png");

    return backgroundTexture && drinkIcon && eatIcon && tent;
}

SDL_Texture* GameEngine::loadTexture(const std::string& filePath) {
    SDL_Texture* texture = IMG_LoadTexture(renderer, filePath.c_str());
    if (!texture) {
        std::cout << "Failed to load texture: " << filePath << " Error: " << IMG_GetError() << std::endl;
    }
    return texture;
}

void GameEngine::renderImage(SDL_Texture* texture, int x, int y, int width, int height) {
    SDL_Rect destRect = { x, y, width, height };
    SDL_RenderCopy(renderer, texture, nullptr, &destRect);
}

void GameEngine::renderText(const std::string& text, int x, int y) {
    SDL_Color color = { 255, 255, 255, 255 };
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (!surface) {
        std::cout << "Text Rendering Error: " << TTF_GetError() << std::endl;
        return;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect destRect = { x, y, surface->w, surface->h };

    SDL_FreeSurface(surface);
    SDL_RenderCopy(renderer, texture, nullptr, &destRect);
    SDL_DestroyTexture(texture);
}

void GameEngine::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            isRunning = false;
        }
        else if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
            case SDLK_1:
                handlePlayerAction("forage");
                break;
            case SDLK_2:
                handlePlayerAction("hunt");
                break;
            case SDLK_3:
                handlePlayerAction("rest");
                break;
            case SDLK_4:
                handlePlayerAction("build_shelter");
                break;
            case SDLK_5:
                handlePlayerAction("consume_food");
                break;
            case SDLK_6:
                handlePlayerAction("consume_water");
                break;
            case SDLK_7:
                showInventory();
                break;
            case SDLK_q:
                isRunning = false;
                break;
            }
        }
    }
}

void GameEngine::showInventory() {
    dynamicMessage = player->displayInventory(); // Call the inventory display method and update the dynamic message
}

void GameEngine::handlePlayerAction(const std::string& action) {
    if (action == "forage") {
        dynamicMessage = player->forage();
        player->incrementScore();
    }
    else if (action == "hunt") {
        dynamicMessage = player->hunt();
        player->incrementScore();
    }
    else if (action == "rest") {
        dynamicMessage = player->rest();
        player->incrementScore();
    }
    else if (action == "build_shelter") {
        dynamicMessage = player->buildShelter();
        shelterBuilt = player->hasShelter();
    }
    else if (action == "consume_food") {
        dynamicMessage = player->useResource("food");
    }
    else if (action == "consume_water") {
        dynamicMessage = player->useResource("water");
    }

    handleEnvironmentEffects(dynamicMessage);

    checkGameOver();
}

void GameEngine::handleEnvironmentEffects(std::string& eventMessage) {
    if (environment->isNight() && !environmentEffectApplied) {
        player->adjustEnergy(-10); 
        eventMessage += " It's night, and you're losing energy faster!";
    }

    if (environment->isBadWeather() && !player->hasShelter()) {
        player->adjustHealth(-10); 
        eventMessage += " The weather is harsh, and you're losing health without shelter!";
    }

    environmentEffectApplied = true;
}

void GameEngine::render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Render background image
    if (backgroundTexture) {
        renderImage(backgroundTexture, 0, 0, 800, 600);
    }

    // Display score
    std::string scoreText = "Score: " + std::to_string(player->getScore()); 
    renderText(scoreText, 10, 100); // Render score on the screen
    std::string highScoreText = "High Score: " + std::to_string(highScore);
    renderText(highScoreText, 10, 140);

    // Render player stats
    std::ostringstream stats;
    stats << "Health: " << player->getHealth() << " Hunger: " << player->getHunger()
        << " Thirst: " << player->getThirst() << " Energy: " << player->getEnergy();
    renderText(stats.str(), 10, 10);

    // Render dynamic message
    renderText(dynamicMessage, 10, 50);

    // Render action prompts
    std::string actionPrompt1 = "|Press 1: Forage | 2: Hunt | 3: Rest | 4: Build Shelter |";
    std::string actionPrompt2 = "| 5: Eat | 6: Drink | 7: Show Inventory | Q: Quit |";
    renderText(actionPrompt1, 10, 450);
    renderText(actionPrompt2, 10, 500);

    // Display food and drink icons if user consumed them
    if (dynamicMessage.find("consume_food") != std::string::npos) {
        renderImage(eatIcon, 200, 100, 100, 100); 
    }
    if (dynamicMessage.find("consume_water") != std::string::npos) {
        renderImage(drinkIcon, 200, 100, 100, 100);
    }

    // Render the tent image if shelter is built
    if (shelterBuilt) {
        renderImage(tent, 500, -50, 500, 500);
    }

    // Check if the game is over
    if (gameOver) {
        renderText(dynamicMessage, 10, 100); // Render the game-over message
    }

    SDL_RenderPresent(renderer);
}

void GameEngine::update() {
    environmentEffectApplied = false;
    
}

void GameEngine::clean() {
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyTexture(drinkIcon);
    SDL_DestroyTexture(eatIcon);
    SDL_DestroyTexture(tent);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

bool GameEngine::isGameOver() const {
    return player->getHealth() <= 0 || player->getHunger() <= 0 || player->getThirst() <= 0 || player->getEnergy() <= 0;
}

void GameEngine::checkGameOver() {
    if (isGameOver()) {
        dynamicMessage = "Game Over! Your final score is: " + std::to_string(player->getScore());
        saveScore(); // Save the score at the end of the game
    }
}

void GameEngine::loadHighScore() {
    std::ifstream inputFile("highscore.txt");
    if (inputFile.is_open()) {
        inputFile >> highScore;
        inputFile.close();
    }
    else {
        highScore = 0;  // Default if no file exists
    }
}

void GameEngine::saveScore() {
    if (player->getScore() > highScore) {
        highScore = player->getScore();
        std::ofstream outputFile("highscore.txt");
        if (outputFile.is_open()) {
            outputFile << highScore;
            outputFile.close();
        }
    }
}