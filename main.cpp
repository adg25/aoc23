//
//  main.cpp
//  
//
//  Created by Adam Goldberg on 12/1/23.
//

#include <stdio.h>
#include <iostream>
#include <string>

#include "include/trebuchet.hpp"

int main()
{
    auto const count = aoc::trebuchet::GetCountWords("input/trebuchet.txt");
    std::cout << "Count: " << std::to_string(count) << std::endl;
}
