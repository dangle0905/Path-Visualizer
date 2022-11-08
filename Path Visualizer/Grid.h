#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>



class Grid
{
private:
	std::vector<std::vector<int>> const DIRECTIONS = { {-1,0}, {0,1}, {1,0}, {0,-1} };
	const int mapSize = 50;

	int mapValue = 0;

	std::vector<std::vector<int>> mapValues;
	std::vector<std::vector<sf::Text>> displayMapValues;

	float gridSizeF = 20.f; //if you want to change the grid size just change the variable size here 


	//this is going to make our grid and is one of the shapes
	//it is a vector and each vector holds a shape object
	std::vector<std::vector<sf::RectangleShape>> tileMap;


	//this is for the mouse position we need it for the tile selector
	//sf::Vector2i mousePosScreen = sf::Mouse::getPosition(); //gives us the position of the mouse in the entire screen
	sf::Vector2i mousePosWindow = sf::Mouse::getPosition();
	sf::Vector2f mousePosView;
	sf::Vector2u mousePosGrid;

	unsigned gridSizeU = static_cast<unsigned>(gridSizeF);

	//this the obj of our tile selector
	sf::RectangleShape tileSelector;

	sf::Text text;
	sf::Text timerText;
	sf::Font font;

	sf::Time timeElapsed;
	sf::Clock dtClock;

	sf::Text textMapValue;



	std::string searchType = "None";


public:
	//here is our constructor
	Grid(sf::RenderWindow& window);
	void drawGrid(sf::RenderWindow& window);
};

