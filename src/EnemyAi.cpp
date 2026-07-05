#include <SFML/Graphics.hpp>
#include "Puck.hpp"

sf::Vector2f EnemyPaddlePosition = {0.f, 0.f};
sf::Vector2f EnemyPaddleSize = {0.f, 0.f};
sf::RectangleShape EnemyPaddle;

sf::RectangleShape DrawEnemyPaddle(const sf::Vector2f& ViewSize){
    EnemyPaddle.setSize({ViewSize.x * 0.06f, ViewSize.y * 0.2f});
    EnemyPaddleSize = EnemyPaddle.getSize();
    EnemyPaddlePosition = {ViewSize.x, ViewSize.y * 0.5f};

    EnemyPaddle.setFillColor(sf::Color::White);
    EnemyPaddle.setOutlineColor(sf::Color::White);
    EnemyPaddle.setPosition({EnemyPaddlePosition});

    return EnemyPaddle;
}

void UpdateEnemyPaddlePosition(const sf::Vector2f& ViewSize, const float& EnemyPaddleSpeed){
    bool PuckApproaching = PuckVelocity.x > 0.f;

    if(PuckApproaching && PuckPosition.y < EnemyPaddlePosition.y){
        EnemyPaddlePosition.y -= EnemyPaddleSpeed;
    }
    else if(PuckApproaching && PuckPosition.y > EnemyPaddlePosition.y){
        EnemyPaddlePosition.y += EnemyPaddleSpeed;
    }

    EnemyPaddlePosition.y = std::clamp(EnemyPaddlePosition.y, EnemyPaddleSize.y / 2.0f, ViewSize.y - (EnemyPaddleSize.y / 2.0f));
}

void UpdateEnemyPaddle(sf::RenderWindow& Window, const sf::View& View, const float& EnemyPaddleSpeed){
    sf::Vector2f ViewSize = View.getSize();

    UpdateEnemyPaddlePosition(ViewSize, EnemyPaddleSpeed);
    EnemyPaddle.setPosition(EnemyPaddlePosition);

    Window.draw(EnemyPaddle);
}

void ForceUpdateEnemyPaddle(sf::RenderWindow& Window, const sf::View& View){
    sf::Vector2f ViewSize = View.getSize();
    EnemyPaddle.setPosition(EnemyPaddlePosition);

    Window.draw(EnemyPaddle);
}

void InitEnemyPaddle(const sf::View& View){
    sf::Vector2f ViewSize = View.getSize();
    DrawEnemyPaddle(ViewSize);
    
    EnemyPaddleSize = EnemyPaddle.getSize();
    EnemyPaddle.setOrigin(sf::Vector2f({EnemyPaddleSize.x / 2.0f, EnemyPaddleSize.y / 2.0f}));
}