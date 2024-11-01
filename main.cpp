#define SDL_MAIN_HANDLED
#include "GameEngine.h"
#include <SDL.h>
#include <SDL_mixer.h> 
#include <iostream>

int main(int argc, char* argv[]) {
    GameEngine game;

    // Initialize SDL and SDL_mixer
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) { // Add SDL_INIT_AUDIO
        std::cout << "SDL Init Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1) { // Initialize SDL_mixer
        std::cout << "Mix_OpenAudio Error: " << Mix_GetError() << std::endl;
        return -1;
    }

    // Load the background music
    Mix_Music* backgroundMusic = Mix_LoadMUS("assets/sounds/background.mp3");
    if (!backgroundMusic) {
        std::cout << "Failed to load background music: " << Mix_GetError() << std::endl;
        return -1;
    }

    // Play the music on loop
    Mix_PlayMusic(backgroundMusic, -1); // -1 for infinite looping

    if (game.init("Survival Adventure", 800, 600)) {
        while (game.isGameRunning()) {
            game.handleEvents();
            game.update();

            if (game.isGameOver()) {
                game.render(); // Render final game state including game over message
                SDL_Delay(3000); // Wait to display game over message
                break; // Exit loop after delay
            }

            game.render(); // Render game state during normal gameplay
        }
    }

    // Cleanup music and SDL_mixer
    Mix_FreeMusic(backgroundMusic); // Free the music
    Mix_CloseAudio(); // Close the audio
    game.clean();
    SDL_Quit(); // Quit SDL

    return 0;
}
