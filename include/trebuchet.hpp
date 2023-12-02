#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <tuple>

namespace aoc
{
// day 1
class trebuchet{
public:
    static constexpr auto* digits = "0123456789";

    static int GetCount(std::string const& filePath)
    {
        std::fstream f;
        f.open(filePath);
        std::string line;

        auto count = 0;
        while(getline(f, line))
        {
            int const firstInt = GetInt(line, GetFirstDigit(line));
            int const secondInt = GetInt(line, GetLastDigit(line));
            auto const result = Add(firstInt, secondInt);
            count += result;
        }
        return count;
    }

    static int GetCountWords(std::string const& filePath)
    {
        std::vector<std::string> const words = {
            "one", "two", "three", "four", "five",
            "six", "seven", "eight", "nine"
        };
        std::fstream f;
        f.open(filePath);
        std::string line;

        auto count = 0;
        while(getline(f, line))
        {
            // first pass brute force
            // get the position of first int and last int
            // then get the position of each word and compare
            auto const firstDigitPos = GetFirstDigit(line);
            auto const lastDigitPos = GetLastDigit(line);
            auto firstWord = std::make_pair(std::string::npos, 0);
            auto lastWord = std::make_pair(0, 0);
            for(auto i = 0; i < words.size(); i++)
            {
                if(auto const idx = line.find(words.at(i)); idx != std::string::npos)
                {
                    if(idx < firstWord.first)
                    {
                        // new first word
                        firstWord = std::make_pair(idx, i + 1);
                    }
                }
                if(auto const idx = line.rfind(words.at(i)); idx != std::string::npos)
                {
                    if(idx > lastWord.first)
                    {
                        // new last word
                        lastWord = std::make_pair(idx, i + 1);
                    }
                }
            }
            int firstInt;
            int lastInt;
            if(firstWord.first == std::string::npos)
            {
                // there are no words, choose the ints
                firstInt = GetInt(line, firstDigitPos);
                lastInt = GetInt(line, lastDigitPos);
            }
            else
            {
                firstInt = firstWord.first < firstDigitPos ? firstWord.second : GetInt(line, firstDigitPos);
                lastInt = lastWord.first > lastDigitPos ? lastWord.second : GetInt(line, lastDigitPos);
            }
            auto const result = Add(firstInt, lastInt);
            count += result;
            
        }
        return count;
    }

    static std::size_t GetFirstDigit(std::string const& line)
    {
        return line.find_first_of(digits);
    }

    static std::size_t GetLastDigit(std::string const& line)
    {
        return line.find_last_of(digits);
    }

    static int GetInt(std::string const& line, std::size_t pos)
    {
        return line.at(pos) - '0';
    }

    static int Add(int l, int r)
    {
         return (l * 10) + r;
    }
};
}
