#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <vector>
#include <SDL2/SDL_ttf.h>

#include "Renderer.h"
#include "DeckOfCards.h"

class Controller {
public:
    Controller();
    virtual ~Controller();

    void GameLoop(Renderer *renderer);


private:
    DeckOfCards deck;

    struct Hand {
        std::vector<int> hand;
        uint score;
        bool faceup;
    } dealer, player;

    void DealHands(Renderer *renderer);
    void PlayPlayerHand(Renderer *renderer);
    void PlayDealerHand(Renderer *renderer);
    void ClearHands();
    void WhoWon(Renderer *renderer);
    void CenterTexture(SDL_Texture *image, Renderer *renderer);
    void PrintPlayerScore(Renderer *renderer);
    void PrintDealerScore(Renderer *renderer);
    bool isBlackJack = false;
};

#endif /* CONTROLLER_H */

