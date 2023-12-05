#pragma once

#include <unordered_set>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>
#include "absl/strings/str_split.h"
#include <set>
#include <cmath>

namespace aoc
{
  class scratch_cards
  {
    struct ScratchCard
    {
        std::size_t numMatching{};
        int numWon{};
    };
    public:
        static int GetScratchSum(std::string const& filePath)
        {
            auto scratches = GetScratchCards(filePath);
            int count = 0;
            std::cout << "total lines: " << scratches.size() << std::endl;
            for(auto i = 0; i < scratches.size(); i++)
            {
                auto const& scratch = scratches.at(i);
                count += scratch.numWon;

                auto const next = i + 1;
                auto const end = next + scratch.numMatching;
                std::cout << "next: " << next << " end: " << end << std::endl;
                for(auto j = next; j < end; j++)
                {
                    auto val = 1;
                    if(scratch.numWon != 0)
                    {
                        val = scratch.numWon;
                    }
                    scratches.at(j).numWon += val;
                }
                std::cout << "num matching: " << scratch.numMatching << " | " << "num won: " << scratch.numWon << std::endl;
            }
            return count + scratches.size();
        }

    private:
        static std::vector<ScratchCard> GetScratchCards(std::string const& filePath)
        {
            std::fstream f;
            f.open(filePath);
            std::string line;

            std::vector<ScratchCard> scratches{};
            while(getline(f, line))
            {
                // split on "|", left set is winners, right set is our num
                std::vector<std::string> split = absl::StrSplit(line, "|");
                std::set<std::string> winning = absl::StrSplit(split.at(0), " ", absl::SkipEmpty());
                std::set<std::string> myNums = absl::StrSplit(split.at(1), " ", absl::SkipEmpty());
                std::vector<std::string> intersect{};
                std::set_intersection(winning.begin(), winning.end(), myNums.begin(), myNums.end(), std::back_inserter(intersect));
                auto const numOverlapping = intersect.size();;
                scratches.emplace_back(ScratchCard{
                    .numMatching = numOverlapping
                });
            }
            return scratches;
        }
  };
}