#include "CardDealer.h"
#include <algorithm>
#include <stdexcept>

void CardDealer::generate_and_shuffle_deck() {
    deck.clear();
    deck.reserve(num_suits * cards_per_suit);
    
    for (int s = 0; s < num_suits; ++s) {
        for (int r = 0; r < cards_per_suit; ++r) {
            deck.push_back(Card{r, s});
        }
    }
    
    std::ranges::shuffle(deck, rng);
    current_index = 0;
}

CardDealer::CardDealer(int suits, int cards)
    : current_index(0), num_suits(suits), cards_per_suit(cards) {
    
    if (suits <= 0 || cards <= 0) {
        throw std::invalid_argument("Number of suits and cards must be positive.");
    }

    std::random_device rd;
    rng = std::mt19937(rd());
    
    generate_and_shuffle_deck();
}

Card CardDealer::operator()() {
    if (current_index >= deck.size()) {
        generate_and_shuffle_deck();
    }
    return deck[current_index++];
}