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
    public:
        static int GetScratchSum(std::string const& filePath)
        {
            std::fstream f;
            f.open(filePath);
            std::string line;

            auto count = 0;
            while(getline(f, line))
            {
                // split on "|", left set is winners, right set is our num
                std::vector<std::string> split = absl::StrSplit(line, "|");
                std::set<std::string> winning = absl::StrSplit(split.at(0), " ", absl::SkipEmpty());
                std::set<std::string> myNums = absl::StrSplit(split.at(1), " ", absl::SkipEmpty());
                std::vector<std::string> intersect{};
                std::set_intersection(winning.begin(), winning.end(), myNums.begin(), myNums.end(), std::back_inserter(intersect));
                auto const numOverlapping = intersect.size();;
                if(numOverlapping == 0)
                {
                    continue;
                }
                count +=  (1 << (numOverlapping - 1));
            }
            return count;
        }
  };
}