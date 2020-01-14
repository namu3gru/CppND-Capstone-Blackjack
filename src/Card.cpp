#include "Card.h"
Card::Card() {

}
/**
 * @brief Construct a new Card, loading cards rank and suit file
 * 
 * @param rank_file 
 * @param suit_file 
 * @param val 
 */
Card::Card(const std::string rank_file, const std::string suit_file, int val) :
    value(val) {

    const std::string res_path = "../res/";
    std::string rankpath = res_path + rank_file;
    std::string suitpath = res_path + suit_file;

    rank = SDL_LoadBMP(rankpath.c_str());
    if (rank == nullptr) {
        std::cout << "rank SDL_LoadBMP Error: " << rankpath << SDL_GetError() << std::endl;
    }

    suit = SDL_LoadBMP(suitpath.c_str());
        if (suit == nullptr) {
        std::cout << "suit SDL_LoadBMP Error" << suitpath << SDL_GetError() << std::endl;
    }
}

Card::~Card() {
    SDL_FreeSurface(rank);
    SDL_FreeSurface(suit);
}

/**
 * @brief Return resource path
 * 
 * @param subDir 
 * @return std::string 
 */
std::string Card::GetResourcePath(const std::string &subDir) {
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

int Card::GetValue() {
    return value;
}

SDL_Surface* Card::GetRank() {
    return rank;
}

SDL_Surface* Card::GetSuit() {
    return suit;
}