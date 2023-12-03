//
//  main.cpp
//  
//
//  Created by Adam Goldberg on 12/1/23.
//

#include <stdio.h>
#include <iostream>
#include <string>
#include <chrono>

#include "include/gear_ratios.hpp"

int main()
{
    aoc::gear_ratios impl{};
    auto const start = std::chrono::steady_clock::now();
    auto const count = impl.GetPartNumberSum("input/gear_ratios.txt");
    auto const end = std::chrono::steady_clock::now();
    std::cout << "Count: " << std::to_string(count) << std::endl;
    std::cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;
}
