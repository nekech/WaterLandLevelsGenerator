//
//  Level.h
//  GenerateLevels
//
//  Created by Николай Протасов on 22.08.2021.
//

#ifndef Level_h
#define Level_h

#include <nlohmann/json.hpp>

#include "Vector2.h"

struct Level
{
    int width;
    int height;
    
    std::vector<Vector2<int>> mounts;
    std::vector<Vector2<int>> fountains;
    
    std::vector<Vector2<int>> water;
    std::vector<Vector2<int>> land;
    
    Level()
    {
        width = 0;
        height = 0;
    }
    
    Level(nlohmann::json jsonLevel)
    {
        
        width = jsonLevel["Width"].get<int>();
        height = jsonLevel["Height"].get<int>();
        
        //jsonLevel["Mounts"].get_to(mounts);
        
        for(auto const& val : jsonLevel["Mounts"])
        {
            Vector2<int> t1 = val.get<Vector2<int>>();
            mounts.push_back(t1);
            std::cout<<val<<std::endl;
        }
        
        //mounts = jsonLevel.at("Mounts").get<std::vector<Vector2<int>>>();
        //fountains = jsonLevel["Fountains"].get<std::vector<Vector2<int>>>();
        
        //water = jsonLevel["Water"].get<std::vector<Vector2<int>>>();
        //land = jsonLevel["Land"].get<std::vector<Vector2<int>>>();
    }
    
    nlohmann::json serialize()
    {
        nlohmann::json resJson;
        
        resJson["Width"] = width;
        resJson["Height"] = height;
        
        resJson["Mounts"] = mounts;
        resJson["Fountains"] = fountains;
        
        resJson["Water"] = water;
        resJson["Land"] = land;
        
        return resJson;
    }
};

#endif /* Level_h */
