#include "Renderer.h"
#include "DeckOfCards.h"

/**
 * @brief Construct a new Renderer:: Renderer object
 * 
 * @param window_width 
 * @param window_height 
 */
Renderer::Renderer(const std::size_t window_width,
        const std::size_t window_height) :
window_width(window_width), window_height(window_height) {
    /// - Create the window
    window = SDL_CreateWindow("Simple Blackjack Game using SDL library", SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED, window_width, window_height, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
    }

    /// - Create renderer
    renderer = SDL_CreateRenderer(window, -1,
            SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
    }
}

/**
 * @brief Destroy the Renderer:: Renderer object
 * 
 */
Renderer::~Renderer() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

/**
 * @brief Hiding dealer's card and update window once anything changed
 * 
 * @param dealer 
 * @param player 
 * @param deck 
 * @param show 
 * @param playerScore 
 */
void Renderer::RenderTable(std::vector<int> dealer, std::vector<int> player, DeckOfCards deck, bool show, uint playerScore) {
    const std::string res_path = "../res/";

    /// - Clear black window
    SDL_SetRenderDrawColor(renderer, col_bkgrd.r, col_bkgrd.g, col_bkgrd.b, col_bkgrd.a); // set to green
    SDL_RenderClear(renderer);

    /// - Draw badges
    SDL_SetRenderDrawColor(renderer, col_badge.r, col_badge.g, col_badge.b, col_badge.a);

    /// - Load Dealer text bmp
    SDL_RenderFillRect(renderer, &box_dealer);
    SDL_Texture *he_one = LoadTexture(res_path + "Dealer.bmp");
    SDL_RenderCopy(renderer, he_one, NULL, &box_dealer);
    
    /// - Load Player text bmp
    SDL_RenderFillRect(renderer, &box_player);
    SDL_Texture *he_two = LoadTexture(res_path + "Player.bmp");
    SDL_RenderCopy(renderer, he_two, NULL, &box_player);
    
    /// - Load Hit text bmp
    SDL_RenderFillRect(renderer, &choice_one);
    SDL_Texture *ch_one = LoadTexture(res_path + "Hit.bmp");
    SDL_RenderCopy(renderer, ch_one, NULL, &choice_one);
    
    /// - Load Stand text bmp
    SDL_RenderFillRect(renderer, &choice_two);
    SDL_Texture *ch_two = LoadTexture(res_path + "Stand.bmp");
    SDL_RenderCopy(renderer, ch_two, NULL, &choice_two);
    
    /// - Load Player Score text bmp
    SDL_RenderFillRect(renderer, &p_score_board);
    SDL_Texture *p_score = LoadTexture(res_path + "Score.bmp");
    SDL_RenderCopy(renderer, p_score, NULL, &p_score_board);
    
    /// - Load Dealer Score text bmp
    SDL_RenderFillRect(renderer, &d_score_board);
    SDL_Texture *d_score = LoadTexture(res_path + "Score.bmp");
    SDL_RenderCopy(renderer, d_score, NULL, &d_score_board);
    
    /// - Load Result text bmp
    SDL_RenderFillRect(renderer, &game_result_image);
    SDL_Texture *result = LoadTexture(res_path + "Result.bmp");
    SDL_RenderCopy(renderer, result, NULL, &game_result_image);

    SDL_Texture *tenth = NULL;
    SDL_Texture *oneth = NULL;

    
    /// - Load Score number bmp
    SDL_RenderFillRect(renderer, &d_score_tenth);
    SDL_RenderFillRect(renderer, &d_score_oneth);
    SDL_RenderFillRect(renderer, &p_score_tenth);
    SDL_RenderFillRect(renderer, &p_score_oneth);
    tenth = LoadTexture(res_path + "zero.bmp");
    oneth = LoadTexture(res_path + "zero.bmp");
    SDL_RenderCopy(renderer, tenth, NULL, &d_score_tenth);
    SDL_RenderCopy(renderer, oneth, NULL, &d_score_oneth);

    if(playerScore/10 == 1)
    {
            tenth = LoadTexture(res_path + "one.bmp");
    }
    else if(playerScore/10 == 2)
    {
            tenth = LoadTexture(res_path + "two.bmp");
    }

    if(playerScore % 10 == 1)
    {
            oneth = LoadTexture(res_path + "one.bmp");
    }
    else if(playerScore % 10 == 2)
    {
            oneth = LoadTexture(res_path + "two.bmp");
    }
    else if(playerScore % 10 == 3)
    {
            oneth = LoadTexture(res_path + "three.bmp");
    }
    else if(playerScore % 10 == 4)
    {
            oneth = LoadTexture(res_path + "four.bmp");
    }
    else if(playerScore % 10 == 5)
    {
            oneth = LoadTexture(res_path + "five.bmp");
    }
    else if(playerScore % 10 == 6)
    {
            oneth = LoadTexture(res_path + "six.bmp");
    }
    else if(playerScore % 10 == 7)
    {
            oneth = LoadTexture(res_path + "seven.bmp");
    }
    else if(playerScore % 10 == 8)
    {
            oneth = LoadTexture(res_path + "eight.bmp");
    }
    else if(playerScore % 10 == 9)
    {
            oneth = LoadTexture(res_path + "nine.bmp");
    }

    SDL_RenderCopy(renderer, tenth, NULL, &p_score_tenth);
    SDL_RenderCopy(renderer, oneth, NULL, &p_score_oneth);

    /// - Draw card
    SDL_SetRenderDrawColor(renderer, col_card.r, col_card.g, col_card.b, col_card.a);

    /// - Draw dealer's hand
    for (int i = 0; i < (int)dealer.size(); i++) {
        SDL_RenderFillRect(renderer, &d_pos[i]);
        // skip drawing the first card if it's not face up
        if (!(i == 0 && show == false)) {
            SDL_Texture *rank = SDL_CreateTextureFromSurface(renderer, deck.shoe[dealer[i]]->GetRank());
            SDL_Texture *suit = SDL_CreateTextureFromSurface(renderer, deck.shoe[dealer[i]]->GetSuit());
            SDL_Rect rect_rank = {.x = 30 + (i * 120), .y = 100, .w = 40, .h = 40};
            SDL_Rect rect_suit = {.x = 30 + (i * 120), .y = 140, .w = 40, .h = 40};
            SDL_RenderCopy(renderer, rank, NULL, &rect_rank);
            SDL_RenderCopy(renderer, suit, NULL, &rect_suit);
        }
    }

    /// - Draw Player's hand
    for (int i = 0; i < (int)player.size(); i++) {
        SDL_RenderFillRect(renderer, &p_pos[i]);
        SDL_Texture *rank = SDL_CreateTextureFromSurface(renderer, deck.shoe[player[i]]->GetRank());
        SDL_Texture *suit = SDL_CreateTextureFromSurface(renderer, deck.shoe[player[i]]->GetSuit());
        SDL_Rect rect_rank = {.x = 30 + (i * 120), .y = 440, .w = 40, .h = 40};
        SDL_Rect rect_suit = {.x = 30 + (i * 120), .y = 480, .w = 40, .h = 40};
        SDL_RenderCopy(renderer, rank, NULL, &rect_rank);
        SDL_RenderCopy(renderer, suit, NULL, &rect_suit);
    }
}

/**
 * @brief Validate we have valid pointers to window and renderer
 * 
 * @return true 
 * @return false 
 */
bool Renderer::RendererValid() {
    return ((window != nullptr) && (renderer != nullptr));
}

/**
 * @brief Get the resource path
 * 
 * @param subDir 
 * @return std::string 
 */
std::string Renderer::GetResourcePath(const std::string &subDir) {
#ifdef _WIN32
    const char PATH_SEP = '\\';
#else
    const char PATH_SEP = '/';
#endif
    static std::string baseRes;
    if (baseRes.empty()) {
        char *basePath = SDL_GetBasePath();
        if (basePath) {
            baseRes = basePath;
            SDL_free(basePath);
        } else {
            std::cerr << "Error getting resource path: " << SDL_GetError() << std::endl;
            return "";
        }
        baseRes = baseRes + "res" + PATH_SEP;
    }
    return subDir.empty() ? baseRes : baseRes + subDir + PATH_SEP;
}

/**
 * @brief Takes a file from supplied filename and loads it into the renderer.
 * 
 * @param file 
 * @return SDL_Texture* 
 */
SDL_Texture* Renderer::LoadTexture(const std::string &file) {
	SDL_Texture *texture = nullptr;
	SDL_Surface *loadedImage = SDL_LoadBMP(file.c_str());
	if (loadedImage != nullptr){
		texture = SDL_CreateTextureFromSurface(renderer, loadedImage);
		SDL_FreeSurface(loadedImage);
		if (texture == nullptr){
			std::cout << "SDL_CreateTextureFromSurface failed.\n";
		}
	}
	else {
		std::cout << "LoadBMP failed\n";
	}
	return texture;
}
