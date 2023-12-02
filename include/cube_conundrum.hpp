#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

namespace aoc
{
    // only 12 red cubes, 13 green cubes, and 14 blue cubes
    static const std::unordered_map<std::string, int> allowed = {
        {"red", 12},
        {"green", 13},
        {"blue", 14} 
    };

class cube_conundrum
{
    struct RGB{
        int Red{};
        int Green{};
        int Blue{};
    };
  public:

    static int GetNonViolatingGames(std::string const& filePath)
    {
        std::fstream f;
        f.open(filePath);
        std::string line;

        auto idSum = 0;
        auto gameIdx = 1;
        while(getline(f, line))
        {
            // game loop
            std::string handLine;
            std::stringstream ss(line);
            bool possible = true;
            while(getline(ss, handLine, ';'))
            {
                if(GameViolates(handLine))
                {
                    possible = false;
                    break;
                }
            }
            if(possible)
            {
                idSum += gameIdx;
            }
            gameIdx++;
        }
        return idSum;
    }

    static int GetPowerSum(std::string const& filePath)
    {
        std::fstream f;
        f.open(filePath);
        std::string line;

        auto count = 0;
        while(getline(f, line))
        {
            std::string handLine;
            std::stringstream ss(line);
            RGB rgbPossible{};
            while(getline(ss, handLine, ';'))
            {
                auto const& breakdown = BreakdownCubes(handLine);
                rgbPossible.Blue = std::max(rgbPossible.Blue, breakdown.Blue);
                rgbPossible.Red = std::max(rgbPossible.Red, breakdown.Red);
                rgbPossible.Green = std::max(rgbPossible.Green, breakdown.Green);
            }
            count += Power(rgbPossible.Blue, rgbPossible.Green, rgbPossible.Red);
        }  
        return count;
    }

    private:
    static bool GameViolates(std::string const& hand)
    {
        std::stringstream ss(hand);
        std::string handOpts;
        while(getline(ss, handOpts, ','))
        {
            if(CubeViolates(handOpts))
            {
                return true;
            }
        }
        return false;
    }

    static bool CubeViolates(std::string const& cubeGrab)
    {
        int count;
        std::string color;
        std::stringstream ss(cubeGrab);
        ss >> count >> color;
        return allowed.find(color)->second < count;
        
    }

    static RGB BreakdownCubes(std::string const& hand)
    {
        RGB ret{};
        std::stringstream ss(hand);
        std::string handOpts;
        auto setField = [&ret](auto const& color, auto count)
        {
            if(color == "red")
            {
                ret.Red = count;
            }
            else if(color == "green")
            {
                ret.Green = count;
            }
            else{
                ret.Blue = count;
            }
        };
        while(getline(ss, handOpts, ','))
        {
            int count;
            std::string color;
            std::stringstream ss(handOpts);
            ss >> count >> color;  
            setField(color, count);
        } 
        return ret;
    }

    static int Power(int a, int b, int c)
    {
        return a * b * c;
    }
};
}