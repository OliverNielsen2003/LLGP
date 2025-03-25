#include <SFML/Graphics.hpp>
#include<string>
#include<iostream>
using namespace std;

#ifdef _DEBUG
int main()
#else
int WinMain()
#endif
{
    sf::RenderWindow window(sf::VideoMode({ 1920, 1080 }), "Game");

    while (window.isOpen())
    {
        // Event polling section of code - this must be done in the thread which created the window
        // we will talk about threading later, but essentially this must be done here
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();
        window.display();
    }

}

