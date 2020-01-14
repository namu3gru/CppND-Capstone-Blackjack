#include "DeckOfCards.h"

DeckOfCards::DeckOfCards() : shuffle(true), card_to_deal(0), reshuffle(0) {
    CreateShoe();
}

DeckOfCards::~DeckOfCards() {
}

/**
 * @brief Shuffle card
 * 
 */
void DeckOfCards::Shuffle() {
    // random number generator set-up
    std::random_device ran_dev;
    std::mt19937 ran_engine(ran_dev());
    std::uniform_int_distribution<int> card_to_swap(0, 51);
    std::uniform_int_distribution<int> reshuffle_card(35, 42);

    Card *temp;
    std::size_t swap;

    /// - Use Fitsher-Yates shuffle algorithm
    for (std::size_t card = cards_in_deck - 1; card > 0; card--) {
        swap = card_to_swap(ran_engine) % card;

        temp = shoe[swap];
        shoe[swap] = shoe[card];
        shoe[card] = temp;
    }

    card_to_deal = 0;
    reshuffle = reshuffle_card(ran_engine);
    shuffle = false;

    return;
}

/**
 * @brief Create deck of card
 * 
 */
void DeckOfCards::CreateShoe() {
    shoe = new Card*[cards_in_deck];

    int i, rank;
    for (i = 0; i < cards_in_deck; i++) {
        rank = i /26;
        shoe[i] = new Card(rank % 2 ? reds[i % 13] : blacks[i % 13],
                        suits[i / 13],
                        values[i % 13]);
    }
}

/**
 * @brief Deals card
 * 
 * @return int 
 */
int DeckOfCards::DealCard() {
    int card = card_to_deal++;
    if (card_to_deal == reshuffle) {
        shuffle = true;
    }
    return card;
}

/**
 * @brief Calculate card score then return it. Determine current deal is blackjack.
 * 
 * @param hand 
 * @param deck 
 * @return int 
 */
int DeckOfCards::ScoreHand(std::vector<int> hand, DeckOfCards deck) {
    int score = 0;

    if (!hand.empty()) {
        bool soft_count = false;
        bool has_ace = false;
        int blackJack = 100;

        for (int card : hand) {
            if (deck.shoe[card]->GetValue() == 11) {
                if (!has_ace) {
                    has_ace = true;
                    soft_count = true;
                    score += 11;
                } else {
                    score += 1;
                }
            } 
            else 
            {
                score += deck.shoe[card]->GetValue();
            }

            if(has_ace && score == 21) /// - If it has ace and 10/K/Q/J then it is blackjack
            {
                return blackJack; /// - Return blackjack value
            }
            if ((score > 21) && soft_count) {
                soft_count = false;
                score -= 10;
            }
        }
    }
    return score;
}

bool DeckOfCards::NeedShuffle() {
    return shuffle;
}