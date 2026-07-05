#include <SFML/Graphics.hpp>
#include <algorithm>

sf::Vector2f PaddlePosition = {0.f, 0.f};
sf::Vector2f PaddleSize = {0.f, 0.f};
sf::RectangleShape Paddle;

sf::RectangleShape DrawPaddle(const sf::Vector2f& ViewSize){
    Paddle.setSize({ViewSize.x * 0.06f, ViewSize.y * 0.2f});
    PaddleSize = Paddle.getSize();

    Paddle.setFillColor(sf::Color::White);
    Paddle.setOutlineColor(sf::Color::White);
    Paddle.setPosition({PaddleSize.x, ViewSize.y * 0.5f});

    return Paddle;
}

void UpdatePaddlePosition(const sf::Vector2f& ViewSize, sf::Vector2f& PaddleSize, const float& PaddleSpeed){

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)){
        PaddlePosition.y -= PaddleSpeed;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)){
        PaddlePosition.y += PaddleSpeed;
    }

    PaddlePosition.y = std::clamp(PaddlePosition.y, PaddleSize.y / 2.0f, ViewSize.y - (PaddleSize.y / 2.0f));
}

void UpdatePaddle(sf::RenderWindow& Window, const sf::View& View, const float& PaddleSpeed){
    sf::Vector2f ViewSize = View.getSize();

    UpdatePaddlePosition(ViewSize, PaddleSize, PaddleSpeed);
    Paddle.setPosition(PaddlePosition);

    Window.draw(Paddle);
}

void ForceUpdatePaddle(sf::RenderWindow& Window, const sf::View& View){
    sf::Vector2f ViewSize = View.getSize();
    Paddle.setPosition(PaddlePosition);

    Window.draw(Paddle);
}

void InitPaddle(const sf::View& View){
    sf::Vector2f ViewSize = View.getSize();
    DrawPaddle(ViewSize);
    
    PaddleSize = Paddle.getSize();
    Paddle.setOrigin(sf::Vector2f({PaddleSize.x / 2.0f, PaddleSize.y / 2.0f}));
}