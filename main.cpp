#include <SFML/Graphics.hpp>
#include<string>
#include<iostream>
using namespace std;

bool foundPos = false;
int xPos;
int yPos;
/*
    This version of the SFML "hello world" is statically linked, you may wish to try the dynamically linked version as well.
*/
void moveCharacter(sf::Sprite& sprite)
{

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    {
        sprite.move({ -0.1f, 0.f });
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
        sprite.move({ 0.1f, 0.f });
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
    {
        sprite.move({ 0.f, -0.1f });
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
    {
        sprite.move({ 0.f, 0.1f });
    }
}

void characterOffScreen(sf::Sprite& sprite)
{
    if (sprite.getPosition().y > 1080.f)
    {
        sprite.setPosition({ sprite.getPosition().x, 0.f });
    }
    else if (sprite.getPosition().y < 0.f - (32 * 5))
    {
        sprite.setPosition({ sprite.getPosition().x, 1080.f });
    }

    if (sprite.getPosition().x > 1920.f)
    {
        sprite.setPosition({ 0.f, sprite.getPosition().y });
    }
    else if (sprite.getPosition().x < (0.f - (32 * 5)))
    {
        sprite.setPosition({ 1920.f, sprite.getPosition().y });
    }
}

void aiOffScreen(sf::Sprite& AI)
{
    if (AI.getPosition().y > 1080.f)
    {
        AI.setPosition({ AI.getPosition().x, 0.f });
    }
    else if (AI.getPosition().y < 0.f)
    {
        AI.setPosition({ AI.getPosition().x, 1080.f });
    }
    else
    {

    }

    if (AI.getPosition().x > 1920.f)
    {
        AI.setPosition({ 0.f, AI.getPosition().y });
    }
    else if (AI.getPosition().x < 0.f)
    {
        AI.setPosition({ 1920.f, AI.getPosition().y });
    }
    else
    {

    }
}

bool inRange(int low, int high, int x)
{
    return ((x - high) * (x - low) <= 0);
}

void moveAI(sf::Sprite& AI, int x, int y)
{
    if (AI.getPosition().x < x)
    {
        AI.move({ 0.1f, 0.f });
    }
    else if (AI.getPosition().x > x)
    {
        AI.move({ -0.1f, 0.f });
    }


    if (AI.getPosition().y < y)
    {
        AI.move({ 0.f, 0.1f });
    }
    else if (AI.getPosition().y > y)
    {
        AI.move({ 0.f, -0.1f });
    }


    if (foundPos == false || inRange(xPos - 5, xPos + 5, AI.getPosition().x) && inRange(yPos - 5, yPos + 5, AI.getPosition().y))
    {
        xPos = rand() % 1920;
        yPos = rand() & 1080;
        foundPos = true;
    }

}

void findPosAI()
{
    xPos = rand() % 1919 + 1;
    yPos = rand() % 1079 + 1;
    foundPos = true;
}
#ifdef _DEBUG
int main()
#else
int WinMain()
#endif
{
    sf::RenderWindow window(sf::VideoMode({ 1920, 1080 }), "Game");

    //character
    sf::Texture texture("character.png");
    sf::Sprite sprite(texture);
    sprite.setTextureRect(sf::IntRect({ 1, 1 }, { 32, 32 }));
    sprite.setScale({ 5.f, 5.f });
    sprite.setPosition({ 190.f, 168.f });

    //ai
    sf::Texture dude("character.png");
    sf::Sprite AI(dude);
    AI.setColor({ 255, 0, 0 });
    AI.setTextureRect(sf::IntRect({ 1, 1 }, { 32, 32 }));
    AI.setScale({ 5.f, 5.f });
    AI.setPosition({ 190.f, 168.f });

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
        moveCharacter(sprite);
        moveAI(AI, xPos, yPos);
        aiOffScreen(AI);
        characterOffScreen(sprite);
        window.draw(sprite);
        window.draw(AI);
        window.display();
    }

}

