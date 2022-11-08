#include "DFS.h"
#include <stack>

void DFS::myAlgorithm(std::string& searchType, std::vector<std::vector<int>>& mapValues, std::vector<std::vector<sf::RectangleShape>>& tileMap, std::vector<std::vector<sf::Text>>& displayMapValues, sf::Time& timeElapsed, sf::RenderWindow& window)
{
    sf::Clock startClock;

    std::pair<int, int> starting_coordinates;

    //directions 
    int up[] = { 0,-1 };
    int down[] = { 0, 1 };
    int right[] = { 1,0 };
    int left[] = { -1,0 };

    for (int i = 0; i < 50; i++) {
        for (int j = 0; j < 50; j++) {
            if (tileMap[i][j].getFillColor() == sf::Color::Blue) {
                starting_coordinates = { i,j };
            }
        }
    }

    std::stack<std::pair<int, int>> q;

    q.push(starting_coordinates);


    while (!q.empty())
    {

        auto current = q.top();
        q.pop();



        for (std::vector<int> direction : DIRECTIONS)
        {
            int newX = current.first + direction[0];
            int newY = current.second + direction[1];

            //bases cases, this one for out of bounds
            if (newX < 0 || newX > 49 || newY < 0 || newY > 49) {
                continue;
            }

            //means we have visited this node already
            if (tileMap[newX][newY].getFillColor() == sf::Color::Magenta || tileMap[newX][newY].getFillColor() == sf::Color::Blue) {
                continue;
            }

            //means this is a wall
            if (tileMap[newX][newY].getFillColor() == sf::Color::Green) {
                continue;
            }

            //reach our target
            if (tileMap[newX][newY].getFillColor() == sf::Color::Red) {
                timeElapsed = startClock.getElapsedTime();
                std::cout << timeElapsed.asSeconds() << "\n";
                std::stack<std::pair<int, int>> empty;
                std::swap(q, empty);
                break;

            }

            tileMap[newX][newY].setFillColor(sf::Color::Magenta);


            window.clear();
            for (int x = 0; x < mapSize; x++)
            {
                for (int y = 0; y < mapSize; y++)
                {


                    window.draw(tileMap[x][y]);


                }
            }

            window.display();


            q.push({ newX,newY });

        }




    }
}
