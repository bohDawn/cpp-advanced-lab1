// Compiler: MSVC with /std:c++latest or GCC/Clang with -std=c++23.
// Precompiled header is not used.

#include "LabAnalyzer.h"
#include <iostream>
#include <stdexcept>

int main() {
    try {
        std::cout << "=== Lab 1: Functional Programming ===\n";
        std::cout << "1. Manual mode\n";
        std::cout << "2. Software experiment\n";
        
        int choice = get_valid_input("Choose mode (1 or 2): ", 1);

        if (choice == 1) {
            int num_suits = get_valid_input("Enter the number of suits (> 0): ", 1);
            int cards_to_deal = get_valid_input("Enter the number of cards to deal (> 0): ", 1);
            deal_and_analyze_stacks(num_suits, cards_to_deal);
        } else if (choice == 2) {
            run_experiment();
        } else {
            std::cout << "Unknown mode.\n";
        }

    } catch (const std::exception& e) {
        std::cerr << "\n[Critical Error]: " << e.what() << "\n";
        return 1;
    }

    return 0;
}