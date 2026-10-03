#include "LabAnalyzer.h"
#include "CardDealer.h"
#include <iostream>
#include <vector>
#include <map>
#include <numeric>
#include <algorithm>
#include <iomanip>
#include <limits>
#include <stdexcept>

int get_valid_input(const std::string& prompt, int min_val) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value && value >= min_val) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
        if (std::cin.eof()) {
            throw std::runtime_error("EOF.");
        }
        std::cout << "[Error] Invalid input. Expected an integer >= " << min_val << ".\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

void deal_and_analyze_stacks(int num_suits, int cards_to_deal) {
    if (cards_to_deal == 0) return;

    CardDealer dealer(num_suits);
    std::vector<int> stack_lengths;
    int current_stack_length = 1;
    Card prev_card = dealer();

    for (int i = 1; i < cards_to_deal; ++i) {
        Card current_card = dealer();
        if (current_card >= prev_card) {
            current_stack_length++;
        } else {
            stack_lengths.push_back(current_stack_length);
            current_stack_length = 1;
        }
        prev_card = current_card;
    }
    stack_lengths.push_back(current_stack_length); 

    size_t total_stacks = stack_lengths.size();
    std::cout << "\n--- Deal Results ---\n";
    std::cout << "Total number of stacks formed: " << total_stacks << "\n\n";

    std::sort(stack_lengths.begin(), stack_lengths.end(), std::less<int>());

    std::map<int, int> length_counts;
    std::for_each(stack_lengths.begin(), stack_lengths.end(), 
        [&length_counts](int len) { length_counts[len]++; }
    );

    std::cout << "Percentage of stacks of each length:\n";
    std::cout << std::fixed << std::setprecision(2);
    for (const auto& [length, count] : length_counts) {
        std::cout << " - Length " << length << ": " 
                  << (static_cast<double>(count) / total_stacks) * 100.0 << "% (" << count << " pcs)\n";
    }

    auto mode_it = std::max_element(length_counts.begin(), length_counts.end(),
        [](const auto& a, const auto& b) { return a.second < b.second; }
    );
    std::cout << "\nMost frequent length (mode): " << mode_it->first << "\n";

    double sum = std::accumulate(stack_lengths.begin(), stack_lengths.end(), 0.0);
    std::cout << "Average stack length: " << sum / total_stacks << "\n";

    double median = (total_stacks % 2 != 0) 
                    ? stack_lengths[total_stacks / 2] 
                    : (stack_lengths[(total_stacks - 1) / 2] + stack_lengths[total_stacks / 2]) / 2.0;
    std::cout << "Median stack length: " << median << "\n";
}

void run_experiment() {
    std::cout << "\n=== Software Experiment ===\n";
    std::cout << std::left << std::setw(25) << "Cards per suit" 
              << std::setw(20) << "Average length" << "Median length\n";
    std::cout << std::string(65, '-') << "\n";

    const int num_suits = 4;
    const int cards_to_deal = 100000;

    for (int cards_per_suit = 5; cards_per_suit <= 50; cards_per_suit += 5) {
        CardDealer dealer(num_suits, cards_per_suit);
        std::vector<int> stack_lengths;
        int current_stack_length = 1;
        Card prev_card = dealer();

        for (int i = 1; i < cards_to_deal; ++i) {
            Card current_card = dealer();
            if (current_card >= prev_card) {
                current_stack_length++;
            } else {
                stack_lengths.push_back(current_stack_length);
                current_stack_length = 1;
            }
            prev_card = current_card;
        }
        stack_lengths.push_back(current_stack_length);

        size_t total_stacks = stack_lengths.size();
        std::sort(stack_lengths.begin(), stack_lengths.end(), std::less<int>());
        
        double sum = std::accumulate(stack_lengths.begin(), stack_lengths.end(), 0.0);
        double average = sum / total_stacks;
        
        double median = (total_stacks % 2 != 0) 
                        ? stack_lengths[total_stacks / 2] 
                        : (stack_lengths[(total_stacks - 1) / 2] + stack_lengths[total_stacks / 2]) / 2.0;

        std::cout << std::left << std::setw(25) << cards_per_suit 
                  << std::fixed << std::setprecision(4) << std::setw(20) << average 
                  << median << "\n";
    }
    std::cout << std::string(65, '-') << "\n";
}