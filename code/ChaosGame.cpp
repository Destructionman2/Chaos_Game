// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <SFML/Graphics/RectangleShape.hpp>

// Make code easier to type with "using namespace"
using namespace sf;
using namespace std;

int main()
{
    // Create a video mode object
    VideoMode vm(1920, 1080);
    // Create and open a window for the game
    RenderWindow window(vm, "Chaos Game!", Style::Default);

    vector<Vector2f> vertices;
    vector<Vector2f> points;
    bool userRepeat = false;
    bool promt = false;
    sf::Font font;
    sf::Text text;
    sf::Text repeatText;
    if (!font.loadFromFile("FromCartoonBlocks.ttf")) cout << "Font failed to load" << endl;

    text.setFont(font);
    text.setString("Click on three points on the screen to set the vertices for the triangle!");
    text.setCharacterSize(48);
    text.setPosition({ 100,100 });
    text.setFillColor(sf::Color::White);

    repeatText.setFont(font);
    repeatText.setString("To exit, hit escape key but to reset hit N");
    repeatText.setCharacterSize(36);
    repeatText.setPosition({ 100,150 });
    repeatText.setFillColor(sf::Color::Red);

    //text.setFillColor(sf::Text::Bold | sf::Text::Underline);

    while (window.isOpen())
    {
        /*
        ****************************************
        Handle the players input
        ****************************************
        */
        Event event;
        while (window.pollEvent(event))
        {
            // Resets what is displayed and restarts the triangle chaos game
            if (userRepeat)
            {
                window.clear();
                vertices.clear();
                points.clear();
                userRepeat = false;
                promt = false;

            }
            
            if (event.type == Event::Closed)
            {
                 // Quit the game when the window is closed
                 window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    std::cout << "the left button was pressed" << std::endl;
                    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                    std::cout << "mouse y: " << event.mouseButton.y << std::endl;

                    if (vertices.size() < 3)
                    {
                        vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                    }
                    else if (points.size() == 0)
                    {
                        ///fourth click
                        ///push back to points vector
                        points.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                        std::cout << std::endl << "point was clicked to start chaos game!" << std::endl;

                        // To display option to user if to exit or repeat
                        promt = true;
                    }
                }
            }
            
            if (Keyboard::isKeyPressed(Keyboard::Escape))
            {
                std::cout << "Escape Key was entered and ended program!" << std::endl;
                window.close();
            }

            // If user wishes to reset, it will make userRepeat true
            if (promt)
            {
                if (Keyboard::isKeyPressed(Keyboard::N))
                {
                    std::cout << "[REPEAT] the N key was pressed and resetted the chaos game!" << std::endl << std::endl;
                    userRepeat = true;
                }
            }

            /*
            ****************************************
            Draw
            ****************************************
            */

            window.clear();
            window.draw(text);

            for (int i = 0; i < vertices.size(); i++)
            {
                RectangleShape rect(Vector2f(10, 10));
                rect.setPosition(Vector2f(vertices[i].x, vertices[i].y));
                rect.setFillColor(Color::Blue);
                window.draw(rect);
            }

            // Moved Point size > 0 if statement to make it be able to display.
            if (points.size() > 0)
            {
                ///generate more point(s)
                ///select random vertex
                ///calculate midpoint between random vertex and the last point in the vector
                ///push back the newly generated coord.

                Vector2f temp = points[0];
                for (int i = 0; i < 5000; i++)
                {
                    int r = rand() % 3;
                    temp = (temp + vertices[r]) / 2.0f;
                    sf::CircleShape circle(1.0f);
                    circle.setPosition(temp);
                    if (r == 0)
                    {
                        circle.setFillColor(sf::Color::Green);
                    }
                    if (r == 1)
                    {
                        circle.setFillColor(sf::Color::Blue);
                    }
                    if (r == 2)
                    {
                        circle.setFillColor(sf::Color::Red);
                    }
                    window.draw(circle);
                }
                window.draw(repeatText);
            }
            window.display();
        }
    }
}