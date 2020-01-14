#ifndef DECKOFCARDS_H
#define DECKOFCARDS_H

#include<random>
#include<array>

#include "Card.h"

const static std::array<int, 13> values = {11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10};
const static int cards_in_deck = 52;

const static std::string suits[4] = {"spade.bmp", "club.bmp",
        "diamond.bmp", "heart.bmp"};

const static std::string blacks[13] = {"black-A.bmp", "black-2.bmp",
        "black-3.bmp", "black-4.bmp", "black-5.bmp",
        "black-6.bmp", "black-7.bmp", "black-8.bmp",
        "black-9.bmp", "black-10.bmp", "black-J.bmp",
        "black-Q.bmp", "black-K.bmp"};

const static std::string reds[13] = {"red-A.bmp", "red-2.bmp",
        "red-3.bmp", "red-4.bmp", "red-5.bmp",
        "red-6.bmp", "red-7.bmp", "red-8.bmp",
        "red-9.bmp", "red-10.bmp", "red-J.bmp",
        "red-Q.bmp", "red-K.bmp"};

class DeckOfCards {
public:
    DeckOfCards();
    ~DeckOfCards();

    void Shuffle();
    int DealCard();
    int ScoreHand(std::vector<int> hand, DeckOfCards deck);
    bool NeedShuffle();

    Card** shoe;

private:
    bool shuffle;       
    int card_to_deal;   
    int reshuffle;      

    void CreateShoe();

};

#endif /* DECKOFCARDS_H */

