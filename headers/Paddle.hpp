#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

extern sf::Vector2f PaddleSize;
extern sf::Vector2f PaddlePosition;
extern sf::Sound PuckSound;
extern sf::RectangleShape Paddle;

void UpdatePaddle(sf::RenderWindow& Window, const sf::View& View, const float& PaddleSpeed);
void ForceUpdatePaddle(sf::RenderWindow& Window, const sf::View& View);
void InitPaddle(const sf::View& View);