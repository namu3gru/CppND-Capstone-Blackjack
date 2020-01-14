#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <string>
#include <SDL2/SDL.h>

class Card {
public:
    Card();
    Card(std::string rank_file, std::string suit_file, int val);
    virtual ~Card();

    int GetValue();
    SDL_Surface* GetRank();
    SDL_Surface* GetSuit();

private:
    int value;
    SDL_Surface *rank;
    SDL_Surface *suit;

    std::string GetResourcePath(const std::string &subDir = "");
};

#endif /* CARD_H */

