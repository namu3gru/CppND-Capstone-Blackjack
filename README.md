# CppND-Capstone-BlackJack
This is simple blackjack game for UDACITY capstone project.

## Requirement
- SDL2
- C++17

## Overview
The program introduces you to simple blackjack game against dealer.
SDL allows either keyboard inputs(H for hit, S for stand, P for replay and Q for quit) or mouse clicks over each button on the screen.
Player will be given 2 cards initially, faced up and will choose hit or stand.
One of dealer's card will be hidden.
Player's current score will be displayed and dealer's score will be given once whoever wins.
Result will shows Dealer Won / Player Won / Push or Blackjack!.
This follows basic blackjack rules, no splitting, betting, doubling down or etc.

## Getting Started
### Notice 
This requires SDL2 library(libsdl2-dev).
### Building
This project contains cmake that allows you to make easy. 

```
mkdir build
cd build
cmake ..
make
```