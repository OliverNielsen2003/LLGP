#include <SFML/Graphics.hpp>
#include<string>
#include<iostream>
#include "Event.h"
using namespace std;


class InputManager
{
public:
    static inline LLGP::Event<int> notifyme;
    static inline LLGP::Event<> physicsTick;

    InputManager()
    {
        notifyme.AddListener(this, std::bind(&InputManager::makeNoise, this, std::placeholders::_1));
        physicsTick.AddListener(this, std::bind(&InputManager::onFixedUpdate, this));

    }

    void makeNoise(int value)
    {
        string keyPressed;
        switch (value)
        {
        case 0:
            keyPressed = "Left";
            break;
        case 1:
            keyPressed = "Right";
            break;
        case 2:
            keyPressed = "Up";
            break;
        case 3:
            keyPressed = "Down";
            break;
        }
        std::cout << "Player pressed" << keyPressed << std::endl;
    }

    void onFixedUpdate()
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        {
            makeNoise(0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        {
            makeNoise(1);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
        {
            makeNoise(2);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
        {
            makeNoise(3);
        }
    }
};
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

    InputManager bobby = InputManager();  // Bob has the event, when it is "invoked" all objects that listened for it (makeNoise) will say something
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

        // Physics looop (totally should have some timer stuff in here, see chrono example
        InputManager::physicsTick();

        window.clear();
        moveCharacter(sprite);
        characterOffScreen(sprite);
        window.draw(sprite);
        window.draw(AI);
        window.display();
    }

}

