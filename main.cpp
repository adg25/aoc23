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

#include "include/trebuchet.hpp"

int main()
{

    auto const start = std::chrono::steady_clock::now();
    auto const count = aoc::trebuchet::GetCountWords("input/trebuchet.txt");
    auto const end = std::chrono::steady_clock::now();
    std::cout << "Count: " << std::to_string(count) << std::endl;
    std::cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;
}
