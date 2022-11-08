#pragma once
#include <SFML/Graphics.hpp>

class Algorithms
{
public:
	//pure abstract class we have to implement this
	virtual void myAlgorithm(std::string& searchType, std::vector<std::vector<int>>& mapValues ,std::vector<std::vector<sf::RectangleShape>>& tileMap, std::vector<std::vector<sf::Text>>& displayMapValues, sf::Time& timeElapsed, sf::RenderWindow& window) = 0;
};

