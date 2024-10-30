#define SDL_MAIN_HANDLED
#include "GameEngine.h"
#include <SDL.h>

int main(int argc, char* argv[]) {
    GameEngine game;
    if (game.init("Survival Adventure", 800, 600)) {
        while (game.isGameRunning()) {
            game.handleEvents();
            game.update();

            if (game.isGameOver()) {  // Check for game over
                game.render(); // Render the final game state including the game over message
                SDL_Delay(3000); // Wait for 3 seconds to display the message
                break; // Exit the loop after the delay
            }

            game.render(); // Render the game state during normal gameplay
        }
    }
    game.clean();
    return 0;
}
