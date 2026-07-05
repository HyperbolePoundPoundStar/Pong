#pragma once
#include <SFML/Graphics.hpp>

extern sf::CircleShape Puck;
extern sf::Vector2f PuckPosition;
extern sf::Vector2f PuckVelocity;
extern float PuckRadius;
extern float PuckSpeed;

void UpdatePuck(sf::RenderWindow& Window, const sf::View& View);
void ForceUpdatePuck(sf::RenderWindow& Window, const sf::View& View);
void InitPuckHitBuffer();
void InitPuck(const sf::View& View);