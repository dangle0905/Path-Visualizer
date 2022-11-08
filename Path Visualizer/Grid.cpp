#include "Grid.h"
#include <sstream>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "BFS.h"
#include "DFS.h"
#include "Dijkstra.h"
//our constructor
Grid::Grid(sf::RenderWindow& window) 
{
			font.loadFromFile("fonts/Dosis-Light.ttf");
			text.setCharacterSize(35);
			text.setFillColor(sf::Color::White);
			text.setFont(font);
			text.setPosition(20.f, 20.f);
			text.setPosition(1030, 0);

			//resizing the map
			tileMap.resize(mapSize, std::vector<sf::RectangleShape>());

			//this should store the values of the map. it will be a 50 x 50 size map
			std::vector<std::vector<int>> mapValuesInitializer(mapSize, std::vector<int>(mapSize, mapValue));
			this->mapValues = mapValuesInitializer;
			std::vector<std::vector<sf::Text>> displayMapValuesInitializer(mapSize, std::vector<sf::Text>(mapSize, textMapValue));
			this->displayMapValues = displayMapValuesInitializer;

			//lets give it some attributes for our tileSelector shape
			tileSelector.setFillColor(sf::Color::Transparent);
			tileSelector.setOutlineThickness(1.f);
			tileSelector.setOutlineColor(sf::Color::Green);


			//doesnt draw the map. juste sets the object into the vector
			for (int x = 0; x < mapSize; x++)
			{
				tileMap[x].resize(mapSize, sf::RectangleShape());
				for (int y = 0; y < mapSize; y++)
				{
					tileMap[x][y].setSize(sf::Vector2f(gridSizeF, gridSizeF));
					tileMap[x][y].setFillColor(sf::Color::White);
					tileMap[x][y].setOutlineThickness(1.f);
					tileMap[x][y].setOutlineColor(sf::Color::Black);
					tileMap[x][y].setPosition(x * gridSizeF, y * gridSizeF);

				}
			}


}
void Grid::drawGrid(sf::RenderWindow& window)
{

	tileSelector.setSize(sf::Vector2f(gridSizeF, gridSizeF));
	tileSelector.setFillColor(sf::Color::Transparent);
	tileSelector.setOutlineThickness(1.f);
	tileSelector.setOutlineColor(sf::Color::Green); //the border of the tile selector is green now

	textMapValue.setCharacterSize(10);
	textMapValue.setFillColor(sf::Color::Black);
	textMapValue.setFont(font);

	
	//mouse position in the window
	mousePosWindow = sf::Mouse::getPosition(window);

	//we dont need the mouses position the screen just the window
	//mousePosScreen = sf::Mouse::getPosition();
	//setView is to set the camera. we don't need that
	//window.setView(view);
	//we dont need the mouse position for the camera
	//mousePosView = window.mapPixelToCoords(mousePosWindow);

	if (mousePosWindow.x >= 0.f && mousePosWindow.x <= gridSizeF*mapSize)
		mousePosGrid.x = mousePosWindow.x / gridSizeU; //cast to unsigned
	if (mousePosWindow.y >= 0.f && mousePosWindow.y <= gridSizeF * mapSize)
		mousePosGrid.y = mousePosWindow.y / gridSizeU;
	window.setView(window.getDefaultView());

	//update game elements
	tileSelector.setPosition(mousePosGrid.x * gridSizeF, mousePosGrid.y * gridSizeF); //multiply it with the grid size and it moves like its selecting a grid

	//update ui
	std::stringstream ss;
	ss << "Path Finder Algorithm Visualizer\n"
		<< "By Dang Le\n\n"
		<< "Keys:\n"
		<< "Left Shift Clears the Entire Grid \n"
		<< "Right Shift Clears Only the Filled area \n"
		<< "Enter Starts BFS Search\n"
		<< "Back Space Starts DFS Search\n"
		<< ""
		<< "Left Click To Draw Wall\n"
		<< "Middle Click To Draw Starting Point\n"
		<< "Right Click to Draw Target\n\n"
		<< "Window (Position from Window): " << mousePosWindow.x << " x " << mousePosWindow.y << "\n"
		<< "Grid (Grid Position): " << mousePosGrid.x << ", " << mousePosGrid.y << "\n"
		<< "Search Type: " << searchType << "\n"
		<< "Time Elapsed: " << timeElapsed.asSeconds() << "\n";

	text.setString(ss.str());
	
	window.clear();

	//this is to select and change the tiles colors to red
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		if ((mousePosGrid.x >= 0 && mousePosGrid.x <= mapSize) && (mousePosGrid.y >= 0 && mousePosGrid.y <= mapSize)) {
			tileMap[mousePosGrid.x][mousePosGrid.y].setFillColor(sf::Color::Green);
		}
	}

	else if (sf::Mouse::isButtonPressed(sf::Mouse::Middle)) {
		if ((mousePosGrid.x >= 0 && mousePosGrid.x <= mapSize) && (mousePosGrid.y >= 0 && mousePosGrid.y <= mapSize)) {
			tileMap[mousePosGrid.x][mousePosGrid.y].setFillColor(sf::Color::Blue);
		}
	}

	else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
		if ((mousePosGrid.x >= 0 && mousePosGrid.x <= mapSize) && (mousePosGrid.y >= 0 && mousePosGrid.y <= mapSize)) {
			tileMap[mousePosGrid.x][mousePosGrid.y].setFillColor(sf::Color::Red);
		}
	}
	//hitting back button clears the tiles
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
		for (int x = 0; x < mapSize; x++)
		{
			for (int y = 0; y < mapSize; y++)
			{
				//our map is now on screen;
				tileMap[x][y].setFillColor(sf::Color::White);
			}
		}
	}
	//hitting back button clears the tiles clears the selection but not the walls and everything
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)) {
		for (int x = 0; x < mapSize; x++)
		{
			for (int y = 0; y < mapSize; y++)
			{
				if (tileMap[x][y].getFillColor() == sf::Color::Magenta)
				{
					tileMap[x][y].setFillColor(sf::Color::White);

				}


			}
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		searchType = "Breadth First Search";
		BFS bfs;
		bfs.myAlgorithm(searchType, mapValues, tileMap, displayMapValues, timeElapsed, window);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
	{
		searchType = "Depth First Search";
		DFS dfs;
		dfs.myAlgorithm(searchType, mapValues, tileMap, displayMapValues, timeElapsed, window);


	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) 
	{
		searchType = "Dikstra";
		Dijkstra shortestPath;
		shortestPath.myAlgorithm(searchType, mapValues, tileMap, displayMapValues, timeElapsed, window);

	}


	for (int x = 0; x < mapSize; x++)
	{
		for (int y = 0; y < mapSize; y++)
		{
			//our map is now on screen;

			window.draw(tileMap[x][y]);
			window.draw(displayMapValues[x][y]);


		}
	}

	window.draw(tileSelector);



	//render ui
	window.draw(text);



};


