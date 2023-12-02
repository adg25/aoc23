#pragma once

#include <string>
#include <fstream>
#include <iostream>

namespace aoc
{
class trebuchet{
public:
    static int GetCount(std::string const& filePath)
    {
        std::fstream f;
        f.open(filePath);
        if(!f.is_open())
        {
            std::cout << "Could not open file!" << std::endl;
            return 0;
        }
        std::string line;
        auto const* digits = "0123456789";

        auto count = 0;
        while(getline(f, line))
        {
            std::cout << "line: " << line << std::endl;
            auto const firstIntChar = line.find_first_of(digits);
            auto const secondIntChar = line.find_last_of(digits);

            int const firstInt = line.at(firstIntChar) - '0';
            int const secondInt = line.at(secondIntChar) - '0';
            auto const result = (firstInt * 10) + secondInt;
            std::cout << "firstInt: " << std::to_string(firstInt) << " | secondInt: " << std::to_string(secondInt) << std::endl;
            std::cout << "result: " << std::to_string(result) << std::endl;
            count += result;
        }
        return count;
    }
};
}
