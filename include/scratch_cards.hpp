#pragma once

#include <unordered_set>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>
#include "absl/strings/str_split.h"
#include <set>


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
                std::set<std::string> winning = absl::StrSplit(split.at(0), " ");
                std::set<std::string> myNums = absl::StrSplit(split.at(1), " ");
                std::vector<std::string> intersect{};
                std::set_intersection(winning.begin(), winning.end(), myNums.begin(), myNums.end(), std::back_inserter(intersect));
                std::cout << "intersect: " << intersect.size() << std::endl;
                if(intersect.size() == 0)
                {
                    continue;
                }
                auto const pow = 1 << (intersect.size() - 1);
                count += pow;
            }
            return count;
        }
  };
}