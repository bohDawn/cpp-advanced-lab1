#pragma once

#include <string>

int get_valid_input(const std::string& prompt, int min_val);
void deal_and_analyze_stacks(int num_suits, int cards_to_deal);
void run_experiment();