#include "Dijkstra.h"
#include <queue>
#include <set>


void Dijkstra::myAlgorithm(std::string& searchType, std::vector<std::vector<int>>& mapValues, std::vector<std::vector<sf::RectangleShape>>& tileMap, std::vector<std::vector<sf::Text>>& displayMapValues, sf::Time& timeElapsed, sf::RenderWindow& window)
{


    sf::Clock startClock;

    std::pair<int, int> starting_coordinates;


    for (int i = 0; i < 50; i++) {
        for (int j = 0; j < 50; j++) {
            if (tileMap[i][j].getFillColor() == sf::Color::Blue) {
                starting_coordinates = { i,j };
            }
        }
    }

    struct myComparator {
        int operator()(std::pair<std::pair<int, int>, int>& val1, std::pair<std::pair<int, int>, int>& val2)
        {
            return val1.second > val2.second;
        }
    };

    std::priority_queue<std::pair<std::pair<int, int>, int>, std::vector<std::pair<std::pair<int, int>, int>>, myComparator> pq;

    pq.push({ starting_coordinates, 0 });
    mapValues[starting_coordinates.first][starting_coordinates.second] = 0;
    std::set<std::pair<int, int>> visited;
    std::set<int> valueVisited;
    valueVisited.insert(0);

    //to test if my min heap priorty queue was working correctly
    /*

    pq.push({ {1,1}, 5 });
    pq.push({ {1,2}, 2 });
    pq.push({ {1,3}, 3 });
    pq.push({ {1,4}, 6 });
    pq.push({ {1,5}, 1 });
    pq.push({ {1,6}, 8 });

    while (pq.empty() == false) {

        auto current = pq.top();

        std::cout << "this is the coordinate: (" << current.first.first << ", " << current.first.second << ") this is the value: " << current.second << "\n";
        pq.pop();

    }



    */


    while (!pq.empty())
    {

        auto current = pq.top();

        std::pair<int, int> pairCurrent = { current.first.first, current.first.second };



        //while the node is found we pop it until its not found
        while (visited.find(pairCurrent) != visited.end())
        {
            //pop the duplicate node
            pq.pop();
            //now go to next node
            current = pq.top();
            //check until pairCurrent == visited.end
            pairCurrent = { current.first.first, current.first.second };

        }

        visited.insert(pairCurrent);

        pq.pop();


        for (std::vector<int> direction : DIRECTIONS)
        {
            //here we get the new coordinates and then are going to set a new value to it
            int newX = current.first.first + direction[0];
            int newY = current.first.second + direction[1];

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
            if (tileMap[newX][newY].getFillColor() == sf::Color::Red)
            {
                mapValues[newX][newY] = mapValues[current.first.first][current.first.second] + 1;
                timeElapsed = startClock.getElapsedTime();

                //////////////////////////////to break out of the queue//////////////////////////////////////////////
                std::priority_queue<std::pair<std::pair<int, int>, int>, std::vector<std::pair<std::pair<int, int>, int>>, myComparator> empty;
            std:swap(pq, empty);
                ///////////////////////////////////////////////////////////////////////////////////////////////

                //the coordinate and its target value
                int targetValue = mapValues[newX][newY] - 1;
                std::pair<int, int> redCoordinates = { newX, newY };

                std::cout << "the starting coordinates for red is " << redCoordinates.first << ", " << redCoordinates.second << " and it's target value is: " << mapValues[newX][newY] - 1 << std::endl;
                std::set<int> visitedValues;
                visitedValues.insert(mapValues[newX][newY]);

                while (mapValues[newX][newY] != 0)
                {
                    for (std::vector<int> direction : DIRECTIONS)
                    {
                        newX = redCoordinates.first + direction[0];
                        newY = redCoordinates.second + direction[1];

                        std::cout << "the first coordinate we checked is: " << newX << ", " << newY << std::endl;
                        //system("pause");
                        if (tileMap[newX][newY].getFillColor() == sf::Color::White || tileMap[newX][newY].getFillColor() == sf::Color::Green) {
                            continue;
                        }

                        if (mapValues[newX][newY] == targetValue && visitedValues.find(targetValue) == visitedValues.end())
                        {
                            if (tileMap[newX][newY].getFillColor() == sf::Color::Blue)
                            {
                                visitedValues.insert(targetValue);
                                redCoordinates.first = newX;
                                redCoordinates.second = newY;
                                break;
                            }
                            else
                            {
                                tileMap[newX][newY].setFillColor(sf::Color::Yellow);
                                window.draw(tileMap[newX][newY]);
                                window.setFramerateLimit(30);
                                window.display();
                                visitedValues.insert(targetValue);
                                redCoordinates.first = newX;
                                redCoordinates.second = newY;
                                break;
                            }


                        }

                    }
                    targetValue--;

                }



                ///////////////////////////////////////////////////////////////////////////////
                break;
                ///////////////////////////////////////////////////////////////////////////
            }



            tileMap[newX][newY].setFillColor(sf::Color::Magenta);



            if (mapValues[newX][newY] == 0) {
                mapValues[newX][newY] = mapValues[current.first.first][current.first.second] + 1;
            }





            window.clear();
            for (int x = 0; x < mapSize; x++)
            {
                for (int y = 0; y < mapSize; y++)
                {
                    //our map is now on screen;
                    window.draw(tileMap[x][y]);


                }
            }

            window.display();



            pq.push({ { newX,newY },mapValues[newX][newY] });



        }




    }
}
