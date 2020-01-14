#include "Controller.h"

Controller::Controller()
{
    DeckOfCards deck;
}

Controller::~Controller()
{
}

/**
 * @brief Run game in infinite loop
 * 
 * @param renderer 
 */
void Controller::GameLoop(Renderer *renderer)
{
    bool game_over = false;

    while (!game_over)
    {
        /// - Suffle cards if needed
        if (deck.NeedShuffle())
        {
            deck.Shuffle();
        }

        /// - Initiate card
        ClearHands();
        renderer->RenderTable(dealer.hand, player.hand, deck, dealer.faceup, player.score);
        SDL_RenderPresent(renderer->renderer);

        /// - Distribute cards
        DealHands(renderer);

        /// - Print player score onto screen
        PrintPlayerScore(renderer);
        SDL_RenderPresent(renderer->renderer);

        /// - Player plays
        PlayPlayerHand(renderer);

        /// - Check player's card
        if (player.score <= 21)
        {
            /// - Play dealer's card
            PlayDealerHand(renderer);
        }
        /// - Display dealer score
        PrintDealerScore(renderer);

        /// - Check who won
        WhoWon(renderer);
        SDL_Event e;
        bool quit = false;
        while (!quit)
        {
            while (SDL_PollEvent(&e))
            {
                if (e.type == SDL_QUIT)
                {
                    quit = true;
                    game_over = true;
                }
                if (e.type == SDL_KEYDOWN)
                {
                    /// - Waiting for key input for replay or quit
                    switch (e.key.keysym.sym)
                    {
                    case SDLK_p:
                        quit = true;
                        break;
                    case SDLK_q:
                        quit = true;
                        game_over = true;
                        break;
                    default:
                        break;
                    }
                }

                /// - Waiting for mouse input
                if (e.type == SDL_MOUSEBUTTONUP)
                {
                    int x = e.button.x;
                    int y = e.button.y;
                    if ((x >= choice_one.x) && (x <= choice_one.x + choice_one.w) &&
                        (y >= choice_one.y) && (y <= choice_one.y + choice_one.h))
                    {
                        quit = true;
                    }

                    if ((x >= choice_two.x) && (x <= choice_two.x + choice_two.w) &&
                        (y >= choice_two.y) && (y <= choice_two.y + choice_two.h))
                    {
                        quit = true;
                        game_over = true;
                    }
                }
            }
        }
    }
}

/**
 * @brief Display player's score
 * 
 * @param renderer 
 */
void Controller::PrintPlayerScore(Renderer *renderer)
{
    const std::string res_path = "../res/";
    SDL_Texture *tenth = NULL;
    SDL_Texture *oneth = NULL;

    SDL_RenderFillRect(renderer->renderer, &p_score_tenth);
    SDL_RenderFillRect(renderer->renderer, &p_score_oneth);
    tenth = renderer->LoadTexture(res_path + "zero.bmp");
    oneth = renderer->LoadTexture(res_path + "zero.bmp");

    if (player.score / 10 == 1)
    {
        tenth = renderer->LoadTexture(res_path + "one.bmp");
    }
    else if (player.score / 10 == 2)
    {
        tenth = renderer->LoadTexture(res_path + "two.bmp");
    }

    if (player.score % 10 == 1)
    {
        oneth = renderer->LoadTexture(res_path + "one.bmp");
    }
    else if (player.score % 10 == 2)
    {
        oneth = renderer->LoadTexture(res_path + "two.bmp");
    }
    else if (player.score % 10 == 3)
    {
        oneth = renderer->LoadTexture(res_path + "three.bmp");
    }
    else if (player.score % 10 == 4)
    {
        oneth = renderer->LoadTexture(res_path + "four.bmp");
    }
    else if (player.score % 10 == 5)
    {
        oneth = renderer->LoadTexture(res_path + "five.bmp");
    }
    else if (player.score % 10 == 6)
    {
        oneth = renderer->LoadTexture(res_path + "six.bmp");
    }
    else if (player.score % 10 == 7)
    {
        oneth = renderer->LoadTexture(res_path + "seven.bmp");
    }
    else if (player.score % 10 == 8)
    {
        oneth = renderer->LoadTexture(res_path + "eight.bmp");
    }
    else if (player.score % 10 == 9)
    {
        oneth = renderer->LoadTexture(res_path + "nine.bmp");
    }

    SDL_RenderCopy(renderer->renderer, tenth, NULL, &p_score_tenth);
    SDL_RenderCopy(renderer->renderer, oneth, NULL, &p_score_oneth);
}

/**
 * @brief Display dealer's score
 * 
 * @param renderer 
 */
void Controller::PrintDealerScore(Renderer *renderer)
{
    const std::string res_path = "../res/";
    SDL_Texture *tenth = NULL;
    SDL_Texture *oneth = NULL;

    SDL_RenderFillRect(renderer->renderer, &d_score_tenth);
    SDL_RenderFillRect(renderer->renderer, &d_score_oneth);
    tenth = renderer->LoadTexture(res_path + "zero.bmp");
    oneth = renderer->LoadTexture(res_path + "zero.bmp");
    SDL_RenderCopy(renderer->renderer, tenth, NULL, &d_score_tenth);
    SDL_RenderCopy(renderer->renderer, oneth, NULL, &d_score_oneth);

    if (dealer.score / 10 == 1)
    {
        tenth = renderer->LoadTexture(res_path + "one.bmp");
    }
    else if (dealer.score / 10 == 2)
    {
        tenth = renderer->LoadTexture(res_path + "two.bmp");
    }

    if (dealer.score % 10 == 1)
    {
        oneth = renderer->LoadTexture(res_path + "one.bmp");
    }
    else if (dealer.score % 10 == 2)
    {
        oneth = renderer->LoadTexture(res_path + "two.bmp");
    }
    else if (dealer.score % 10 == 3)
    {
        oneth = renderer->LoadTexture(res_path + "three.bmp");
    }
    else if (dealer.score % 10 == 4)
    {
        oneth = renderer->LoadTexture(res_path + "four.bmp");
    }
    else if (dealer.score % 10 == 5)
    {
        oneth = renderer->LoadTexture(res_path + "five.bmp");
    }
    else if (dealer.score % 10 == 6)
    {
        oneth = renderer->LoadTexture(res_path + "six.bmp");
    }
    else if (dealer.score % 10 == 7)
    {
        oneth = renderer->LoadTexture(res_path + "seven.bmp");
    }
    else if (dealer.score % 10 == 8)
    {
        oneth = renderer->LoadTexture(res_path + "eight.bmp");
    }
    else if (dealer.score % 10 == 9)
    {
        oneth = renderer->LoadTexture(res_path + "nine.bmp");
    }

    SDL_RenderCopy(renderer->renderer, tenth, NULL, &d_score_tenth);
    SDL_RenderCopy(renderer->renderer, oneth, NULL, &d_score_oneth);
}

/**
 * @brief Clear both player and dealer hand
 * 
 */
void Controller::ClearHands()
{
    dealer.hand.clear();
    dealer.score = 0;
    dealer.faceup = false;

    player.hand.clear();
    player.score = 0;
    player.faceup = true;
}

/**
 * @brief Deal initial hand
 * 
 * @param renderer 
 */
void Controller::DealHands(Renderer *renderer)
{
    for (int i = 0; i < 2; i++)
    {
        player.hand.push_back(deck.DealCard());
        renderer->RenderTable(dealer.hand, player.hand, deck, dealer.faceup, player.score);
        SDL_RenderPresent(renderer->renderer);
        SDL_Delay(200);

        dealer.hand.push_back(deck.DealCard());
        renderer->RenderTable(dealer.hand, player.hand, deck, dealer.faceup, player.score);
        SDL_RenderPresent(renderer->renderer);
        SDL_Delay(200);
    }

    player.score = deck.ScoreHand(player.hand, deck);
    dealer.score = deck.ScoreHand(dealer.hand, deck);
    if (player.score == 100)
    {
        isBlackJack = true;
        player.score = 21;
    }
    else
    {
        isBlackJack = false;
    }
}

/**
 * @brief Have player choose option
 * 
 * @param renderer 
 */
void Controller::PlayPlayerHand(Renderer *renderer)
{
    SDL_Event e;
    bool done = false;
    while (!done)
    {
        while (SDL_PollEvent(&e))
        {
            bool hit = false;
            if (isBlackJack == false) /// - Check blackjack status
            {
                if (e.type == SDL_KEYDOWN)
                {
                    /// - Waiting player's choice of hit or stand
                    switch (e.key.keysym.sym)
                    {
                    case SDLK_h:
                        hit = true;
                        break;
                    case SDLK_s:
                        done = true;
                        break;
                    default:
                        break;
                    }
                }

                if (e.type == SDL_MOUSEBUTTONUP)
                {
                    int x = e.button.x;
                    int y = e.button.y;
                    if ((x >= choice_one.x) && (x <= choice_one.x + choice_one.w) &&
                        (y >= choice_one.y) && (y <= choice_one.y + choice_one.h))
                    {
                        hit = true;
                    }

                    if ((x >= choice_two.x) && (x <= choice_two.x + choice_two.w) &&
                        (y >= choice_two.y) && (y <= choice_two.y + choice_two.h))
                    {
                        done = true;
                    }
                }
            }
            else
            {
                /// - If blackjack forcely move to finish and player wins
                done = true;
            }
            if (hit == true)
            {
                player.hand.push_back(deck.DealCard());
                player.score = deck.ScoreHand(player.hand, deck);
                renderer->RenderTable(dealer.hand, player.hand, deck, dealer.faceup, player.score);
                SDL_RenderPresent(renderer->renderer);

                if (player.score > 21 || player.hand.size() == 5)
                {
                    done = true; /// - Player busted or reached to max card(5)
                }
            }
        }
    }
}

/**
 * @brief Play dealer hand, show dealer's whole card
 * 
 * @param renderer 
 */
void Controller::PlayDealerHand(Renderer *renderer)
{
    dealer.faceup = true;
    renderer->RenderTable(dealer.hand, player.hand, deck, dealer.faceup, player.score);
    SDL_RenderPresent(renderer->renderer);
    SDL_Delay(800);

    while (dealer.score < 17 && dealer.hand.size() < 5)
    {
        dealer.hand.push_back(deck.DealCard());
        dealer.score = deck.ScoreHand(dealer.hand, deck);
        renderer->RenderTable(dealer.hand, player.hand, deck, dealer.faceup, player.score);
        SDL_RenderPresent(renderer->renderer);
        SDL_Delay(250);
    }
}

/**
 * @brief Determine who is going to win
 * 
 * @param renderer 
 */
void Controller::WhoWon(Renderer *renderer)
{
    renderer->RenderTable(dealer.hand, player.hand, deck, dealer.faceup, player.score);

    const std::string res_path = "../res/";
    SDL_Texture *winner = renderer->LoadTexture(res_path + "PlayerWon.bmp");
    SDL_Texture *loser = renderer->LoadTexture(res_path + "DealerWon.bmp");
    SDL_Texture *blackjack = renderer->LoadTexture(res_path + "blackjack.bmp");
    SDL_Texture *tie = renderer->LoadTexture(res_path + "Push.bmp");
    SDL_Texture *play = renderer->LoadTexture(res_path + "Replay.bmp");
    SDL_Texture *quit = renderer->LoadTexture(res_path + "Quit.bmp");

    PrintDealerScore(renderer);

    SDL_SetRenderDrawColor(renderer->renderer, col_badge.r, col_badge.g, col_badge.b, col_badge.a);
    SDL_RenderFillRect(renderer->renderer, &choice_one);
    SDL_RenderFillRect(renderer->renderer, &choice_two);
    SDL_RenderCopy(renderer->renderer, play, NULL, &choice_one);
    SDL_RenderCopy(renderer->renderer, quit, NULL, &choice_two);

    if (isBlackJack == true)
    {
        SDL_RenderCopy(renderer->renderer, blackjack, NULL, &game_result);
    }
    else if (player.score > 21)
    {
        SDL_RenderCopy(renderer->renderer, loser, NULL, &game_result);
    }
    else if (dealer.score > 21)
    {
        SDL_RenderCopy(renderer->renderer, winner, NULL, &game_result);
    }
    else if (player.score < dealer.score)
    {
        SDL_RenderCopy(renderer->renderer, loser, NULL, &game_result);
    }
    else if (player.score > dealer.score)
    {
        SDL_RenderCopy(renderer->renderer, winner, NULL, &game_result);
    }
    else
    {
        SDL_RenderCopy(renderer->renderer, tie, NULL, &game_result);
    }
    SDL_RenderPresent(renderer->renderer);
}