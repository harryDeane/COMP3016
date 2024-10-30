#define SDL_MAIN_HANDLED
#include "GameEngine.h"
#include <SDL.h>

int main(int argc, char* argv[]) {
    GameEngine game;
    if (game.init("Survival Adventure", 800, 600)) {
        while (game.isGameRunning()) {
            game.handleEvents();
            game.update();
            game.render();
        }
    }
    game.clean();
    return 0;
}
