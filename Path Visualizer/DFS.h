#pragma once
#include "Algorithms.h"
#include <queue>
#include <sstream>
#include <iostream>



class DFS : public Algorithms
{
private:
	std::vector<std::vector<int>> const DIRECTIONS = { {-1,0}, {0,1}, {1,0}, {0,-1} };
	const int mapSize = 50;

public:
	void myAlgorithm(std::string& searchType, std::vector<std::vector<int>>& mapValues, std::vector<std::vector<sf::RectangleShape>>& tileMap, std::vector<std::vector<sf::Text>>& displayMapValues, sf::Time& timeElapsed, sf::RenderWindow& window);
};

