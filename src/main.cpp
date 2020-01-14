#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "Renderer.h"
#include "DeckOfCards.h"
#include "Controller.h"

const std::size_t WINDOW_WIDTH = 700;
const std::size_t WINDOW_HEIGHT = 700;

int main(int, char**) 
{
    /// - SDL Start
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) == 0) {
        Renderer renderer(WINDOW_WIDTH, WINDOW_HEIGHT);
        Controller game;
        if (renderer.RendererValid()) {
            game.GameLoop(&renderer);
        }
        return 0;
    }
}
