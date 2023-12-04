#pragma once

#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
#include <ctype.h>
#include <stack>
#include <optional>
#include <tuple>

namespace aoc
{
struct GearPart
{
    std::stack<int> nums{};
    std::pair<int, int> range{};
    bool used{false};
    int result() const
    {
        auto cpy = nums;
        int mult = 1;
        int res = 0;
        while(!cpy.empty())
        {
            auto tmp = cpy.top();
            res += tmp * mult;
            mult *= 10;
            cpy.pop();
        }
        return res;
    }

    bool IsWithinRange(int val) const
    {
        return val >= range.first && val <= range.second && !used;
    }
};

struct Line
{
    std::vector<GearPart> gearParts{};
    std::vector<int> symbolIndices{};

    int GetPartIfMatchesSymbol(int symbolIdx)
    {
        auto first = 0; auto second = 0;
        auto it = std::find_if(gearParts.begin(), gearParts.end(), [symbolIdx](auto const& g){
            return g.IsWithinRange(symbolIdx);
        });
        if(it != gearParts.end())
        {
            // std::cout << "Found number to erase: " << it->result() << std::endl;
            first = it->result();
            it->used = true;

        }
        auto const& it2 = std::find_if(gearParts.begin(), gearParts.end(), [symbolIdx](auto const& g){
            return g.IsWithinRange(symbolIdx);
        });
        if(it2 != gearParts.cend())
        {
            // std::cout << "Found second number to erase: " << it->result() << std::endl;
            second = it2->result();
            it->used = true;
        }
       // std::cout << "returning " << first << " + " << second << std::endl;
        return first + second;
    }

    void print()
    {
        std::cout << "--------" << std::endl;
        std::cout << "gears: " << std::endl;
        std::for_each(gearParts.begin(), gearParts.end(), [](auto const& g){
            std::cout << "Num: " << g.result() << std::endl;
            std::cout << "Range: [" << std::to_string(g.range.first) << "," << std::to_string(g.range.second) << "]" << std::endl;
        });
        std::for_each(symbolIndices.begin(), symbolIndices.end(), [](auto s){
            std::cout << "Symbol: " << std::to_string(s) << std::endl;
        });
        std::cout << "--------" << std::endl;
    }
};

// advent of code day 3
class gear_ratios
{
  public:
    const char kDot = '.'; // kendrick lamar
    int GetPartNumberSum(std::string const& filePath)
    {
        auto lines = ParseLines(filePath);
        int sum = 0;
        // there are no symbols in the top or bottom line
        for(auto i = 1; i < lines.size() - 1; i++)
        {
           // std::cout << "sum before: " << sum << std::endl;
            auto& prev = lines.at(i - 1);
            auto& curr = lines.at(i);
            auto& next = lines.at(i + 1);
            if(i == lines.size() - 2)
            {
                prev.print();
                curr.print();
                next.print();
            }
            auto const& symbols = curr.symbolIndices;
            for(auto symbolIdx : symbols)
            {
                sum += prev.GetPartIfMatchesSymbol(symbolIdx);
                sum += curr.GetPartIfMatchesSymbol(symbolIdx);
                sum += next.GetPartIfMatchesSymbol(symbolIdx);
            }
            std::cout << "sum after: " << sum << std::endl;
        }
        return sum;
    }

  private:
    std::vector<Line> ParseLines(std::string const& filePath)
    {
        std::fstream f;
        f.open(filePath);
        std::string line;
        std::vector<Line> lines{};
        while(getline(f, line))
        {
            Line lineData{};
            GearPart parsingPart{};
            auto i = 0;
            std::for_each(line.begin(), line.end(), [&](auto const& c){
                if(c == kDot)
                {
                    if(!parsingPart.nums.empty())
                    {
                        // end of the range of numbers
                        parsingPart.range.second = i;
                        lineData.gearParts.push_back(parsingPart);
                        // reset the current parsing data
                        parsingPart = GearPart{};
                    }
                }
                else if(std::isdigit(c))
                {
                   if(parsingPart.nums.empty())
                   {
                    // first number in the range
                    // gear symbols can be matched diagonally, so the range must include the number start index minus 1
                    parsingPart.range.first = i - 1;
                   }
                   auto dig = c - '0';
                   parsingPart.nums.push(dig);
                }
                else
                {
                    if(!parsingPart.nums.empty())
                    {
                        // end of the range of numbers
                        parsingPart.range.second = i;
                        lineData.gearParts.push_back(parsingPart);
                        // reset the current parsing data
                        parsingPart = GearPart{};
                    }
                    // bingo we've got a symbol
                    lineData.symbolIndices.push_back(i);
                }
                i++;
            });
            lines.emplace_back(std::move(lineData));
        }
        return lines;
    }

        Line _previousLine{};
};
}