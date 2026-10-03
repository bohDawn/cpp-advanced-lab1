#pragma once

#include <vector>
#include <random>
#include <compare>
#include <cstddef>

struct Card {
    int rank;
    int suit;

    std::strong_ordering operator<=>(const Card& other) const {
        return rank <=> other.rank;
    }

    bool operator==(const Card& other) const {
        return rank == other.rank;
    }
};

class CardDealer {
private:
    std::vector<Card> deck;
    std::size_t current_index;
    int num_suits;
    int cards_per_suit;
    std::mt19937 rng;

    void generate_and_shuffle_deck();

public:
    explicit CardDealer(int suits, int cards = 13);
    Card operator()();
};