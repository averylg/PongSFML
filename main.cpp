#include <SFML/Graphics.hpp>

#include "utils.h"
#include "GameState.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML works!");

    sf::CircleShape ball(10.f);
    ball.setFillColor(sf::Color::Green);
    ball.setOrigin(ball.getOrigin().x + ball.getRadius(), ball.getOrigin().y + ball.getRadius());
    ball.setPosition(WIDTH / 2, HEIGHT / 2);

    sf::RectangleShape player1(sf::Vector2f(40.0f, 200.0f));
    player1.setFillColor(sf::Color::Red);
    player1.setOrigin(player1.getOrigin().x + (player1.getSize().x / 2), player1.getOrigin().y + (player1.getSize().y / 2));
    player1.setPosition(player1.getSize().x + (player1.getSize().x / 2), HEIGHT / 2);

    sf::RectangleShape player2(sf::Vector2f(40.0f, 200.0f));
    player2.setFillColor(sf::Color::Blue);
    player2.setOrigin(player2.getOrigin().x + (player2.getSize().x / 2), player2.getOrigin().y + (player2.getSize().y / 2));
    player2.setPosition(WIDTH - player1.getPosition().x, player1.getPosition().y);

    ballXDir = 1;
    ballYDir = 1;

    sf::CircleShape circle(200.0f);
    circle.setOrigin(circle.getOrigin().x + circle.getRadius(), circle.getOrigin().y + circle.getRadius());
    circle.setPosition(WIDTH / 2, HEIGHT / 2);

    gs::State state = gs::State::WELCOME;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        switch (state)
        {
        case gs::State::WELCOME:

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
            {
                state = gs::State::GAME;
            }
            ball.setPosition(WIDTH / 2, HEIGHT / 2);
            player1.setPosition(player1.getSize().x + (player1.getSize().x / 2), HEIGHT / 2);
            player2.setPosition(WIDTH - player1.getPosition().x, player1.getPosition().y);

            window.clear();
            break;
        case gs::State::GAME:

            

            if (ball.getPosition().y + ball.getRadius() > HEIGHT
                || ball.getPosition().y - ball.getRadius() < 0)
            {
                ballYDir = -ballYDir;
            }
            

            if (ball.getPosition().y < player1.getPosition().y + (player1.getSize().y / 2) &&
                ball.getPosition().y > player1.getPosition().y - (player1.getSize().y / 2))
            {
                if (ball.getPosition().x - ball.getRadius() <= player1.getPosition().x + (player1.getSize().x / 2))
                {
                    ballXDir = -ballXDir;
                }
                
            }

            if (ball.getPosition().x <= 0)
            {
                state = gs::State::LOSE;
            }

            if (ball.getPosition().y < player2.getPosition().y + (player2.getSize().y / 2) &&
                ball.getPosition().y > player2.getPosition().y - (player2.getSize().y / 2))
            {
                if (ball.getPosition().x + ball.getRadius() >= player2.getPosition().x - (player1.getSize().x / 2))
                {
                    ballXDir = -ballXDir;
                }
            }

            if (ball.getPosition().x >= WIDTH)
            {
                state = gs::State::WIN;
            }

            ball.setPosition(ball.getPosition().x + ballXDir, ball.getPosition().y + ballYDir);

            if (player1.getPosition().y - (player1.getSize().y / 2) < 0)
            {
                player1.setPosition(player1.getPosition().x, player1.getSize().y / 2);
            }
            else if (player1.getPosition().y + (player1.getSize().y / 2) > HEIGHT)
            {
                player1.setPosition(player1.getPosition().x, HEIGHT - (player1.getSize().y / 2));
            }
            else
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                {
                    player1.move(0, -1);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                {
                    player1.move(0, 1);
                }
            }

            if (player2.getPosition().y - (player2.getSize().y / 2) < 0)
            {
                player2.setPosition(player2.getPosition().x, player2.getSize().y / 2);
            }
            else if (player2.getPosition().y + (player2.getSize().y / 2) > HEIGHT)
            {
                player2.setPosition(player2.getPosition().x, HEIGHT - (player2.getSize().y / 2));
            }
            else
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                {
                    player2.move(0, -1);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                {
                    player2.move(0, 1);
                }
            }

            

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
            {
                state = gs::State::PAUSE;
            }
            

            window.clear();
            window.draw(player1);
            window.draw(player2);
            window.draw(ball);
            break;
        case gs::State::PAUSE:
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
            {
                state = gs::State::GAME;
            }
            window.clear();
            window.draw(player1);
            window.draw(player2);
            window.draw(ball);
            break;
        case gs::State::WIN:
            window.clear();
            circle.setFillColor(sf::Color::Red);
            window.draw(circle);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
            {
                state = gs::State::WELCOME;
            }
            break;
        case gs::State::LOSE:
            window.clear();
            circle.setFillColor(sf::Color::Blue);
            window.draw(circle);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
            {
                state = gs::State::WELCOME;
            }
            break;
        }


        window.display();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            window.close();
        }

        
    }

    return 0;
}