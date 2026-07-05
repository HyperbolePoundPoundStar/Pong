#pragma once
#include <SFML/Graphics.hpp>

extern sf::Vector2f EnemyPaddlePosition;
extern sf::Vector2f EnemyPaddleSize;
extern sf::RectangleShape EnemyPaddle;

void UpdateEnemyPaddle(sf::RenderWindow& Window, const sf::View& View, const float& EnemyPaddleSpeed);
void ForceUpdateEnemyPaddle(sf::RenderWindow& Window, const sf::View& View);
void InitEnemyPaddle(const sf::View& View);