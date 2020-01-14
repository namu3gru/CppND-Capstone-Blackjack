#ifndef RENDERER_H
#define RENDERER_H

#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <vector>
#include <SDL2/SDL_ttf.h>

#include "DeckOfCards.h"
#include "Card.h"

const static std::size_t CARD_WIDTH  = 100;
const static std::size_t CARD_HEIGHT = 150;

const static SDL_Color col_bkgrd = {0x00, 0x00, 0x00, 0x00};
const static SDL_Color col_card  = {0xFF, 0xFF, 0xFF, 0xFF};
const static SDL_Color col_badge = {0x00, 0xBF, 0xFF, 0xFF};

const static SDL_Rect box_dealer = {20,  20, 175, 50};
const static SDL_Rect box_player = {20, 360, 175, 50};
const static SDL_Rect choice_one = {135, 600, 175, 50};
const static SDL_Rect choice_two = {330, 600, 175, 50};
const static SDL_Rect p_score_tenth = {380, 350, 30, 50};
const static SDL_Rect p_score_oneth = {415, 350, 30, 50};
const static SDL_Rect p_score_board = {220, 360, 150, 50};
const static SDL_Rect d_score_tenth = {380, 20, 30, 50};
const static SDL_Rect d_score_oneth = {415, 20, 30, 50};
const static SDL_Rect d_score_board = {220, 20, 150, 50};
const static SDL_Rect game_result_image = {220, 280, 150, 50};
const static SDL_Rect game_result = {370, 280, 170, 50};

class Renderer {
public:
    Renderer(const std::size_t window_width, const std::size_t window_height);
    ~Renderer();

    void RenderTable(std::vector<int> dealer, std::vector<int> player, DeckOfCards deck, bool show, uint playerScore);
    bool RendererValid();
    std::string GetResourcePath(const std::string &subDir = "");
    SDL_Texture* LoadTexture(const std::string &file);

    SDL_Renderer *renderer;
    SDL_Window *window;

private:

    const std::size_t window_width;
    const std::size_t window_height;

    // Card positions
    const SDL_Rect d_pos[5] = {
        {.x =  20, .y = 90, .w = CARD_WIDTH, .h = CARD_HEIGHT},
        {.x = 140, .y = 90, .w = CARD_WIDTH, .h = CARD_HEIGHT},
        {.x = 260, .y = 90, .w = CARD_WIDTH, .h = CARD_HEIGHT},
        {.x = 380, .y = 90, .w = CARD_WIDTH, .h = CARD_HEIGHT},
        {.x = 500, .y = 90, .w = CARD_WIDTH, .h = CARD_HEIGHT}
    };

    const SDL_Rect p_pos[5] = {
        {.x =  20, .y = 430, .w = CARD_WIDTH, .h = CARD_HEIGHT},
        {.x = 140, .y = 430, .w = CARD_WIDTH, .h = CARD_HEIGHT},
        {.x = 260, .y = 430, .w = CARD_WIDTH, .h = CARD_HEIGHT},
        {.x = 380, .y = 430, .w = CARD_WIDTH, .h = CARD_HEIGHT},
        {.x = 500, .y = 430, .w = CARD_WIDTH, .h = CARD_HEIGHT}
    };
};

#endif /* RENDERER_H */

