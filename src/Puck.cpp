#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <random>
#include "Paddle.hpp"
#include "EnemyAi.hpp"
#include "Misc.hpp"

sf::SoundBuffer PuckBuffer;
sf::Sound PuckSound(PuckBuffer);

sf::CircleShape Puck;
sf::Vector2f PuckVelocity({4.f, 5.f});
sf::Vector2f PuckPosition({0.f, 0.f});
float PuckRadius;
float PuckSpeed = 7.f;

void InitPuckHitBuffer(){
    PuckBuffer.loadFromFile("Assets/PuckHit.wav");
}

sf::CircleShape DrawPuck(const sf::Vector2f& ViewSize){
    PuckRadius = ViewSize.y * 0.025f;

    Puck.setRadius(PuckRadius);
    Puck.setFillColor(sf::Color::White);
    Puck.setOutlineColor(sf::Color::White);
    Puck.setOrigin({PuckRadius, PuckRadius});
    Puck.setPosition({ViewSize.x * 0.5f, ViewSize.y * 0.5f});

    return Puck;
}

void UpdatePuckPosition(const sf::Vector2f& ViewSize){
    bool WithinBounds = ViewSize.y <= PuckPosition.y + PuckRadius || 0.f >= PuckPosition.y - PuckRadius;
    bool PaddleCollision = PuckPosition.y + PuckRadius <= PaddlePosition.y + PaddleSize.y && PuckPosition.y - PuckRadius >= PaddlePosition.y - PaddleSize.y && PuckPosition.x - PuckRadius <= PaddleSize.x / 2.f;
    bool EnemyPaddleCollision = PuckPosition.y + PuckRadius >= EnemyPaddlePosition.y - (EnemyPaddleSize.y / 2.f) && PuckPosition.y - PuckRadius <= EnemyPaddlePosition.y + (EnemyPaddleSize.y / 2.f) && PuckPosition.x + PuckRadius >= EnemyPaddlePosition.x - (EnemyPaddleSize.x / 2.f);

    if(WithinBounds){
        PuckVelocity.y = -PuckVelocity.y;
        PuckSound.play();
    }
    else if(PaddleCollision){
        sf::Vector2f RawDirection = PuckPosition - PaddlePosition;
        float Length = std::sqrt((RawDirection.x * RawDirection.x) + (RawDirection.y * RawDirection.y));

        if(Length == 0.f){
            PuckVelocity = {1.f * PuckSpeed, 0.f};
        }
        else{
            PuckVelocity = {(RawDirection.x/Length) * PuckSpeed, (RawDirection.y/Length) * PuckSpeed};
        }
        PuckSound.play();
    }
    else if(EnemyPaddleCollision){
        sf::Vector2f RawDirection = PuckPosition - EnemyPaddlePosition;
        float Length = std::sqrt((RawDirection.x * RawDirection.x) + (RawDirection.y * RawDirection.y));

        if(Length == 0.f){
            PuckVelocity = {-1.f * PuckSpeed, 0.f};
        }
        else{
            PuckVelocity = {(RawDirection.x/Length) * PuckSpeed, (RawDirection.y/Length) * PuckSpeed};
        }
        PuckSound.play();
    }

    PuckPosition += PuckVelocity;
}

void UpdatePuck(sf::RenderWindow& Window, const sf::View& View){
    sf::Vector2f ViewSize = View.getSize();

    UpdatePuckPosition(ViewSize);
    Puck.setPosition(PuckPosition);

    Window.draw(Puck);
}

void ForceUpdatePuck(sf::RenderWindow& Window, const sf::View& View){
    sf::Vector2f ViewSize = View.getSize();

    Puck = DrawPuck(ViewSize);
    Puck.setPosition(PuckPosition);

    Window.draw(Puck);
}

void InitPuck(const sf::View& View){
    static std::random_device RandomDevice;
    static std::mt19937 NumberGenerator(RandomDevice());
    std::uniform_real_distribution<float> dist(0, 1);

    float XVelocity = PuckSpeed;
    float YVelocity = dist(NumberGenerator) * PuckSpeed;

    sf::Vector2f ViewSize = View.getSize();
    DrawPuck(ViewSize);
    PuckVelocity = {XVelocity, YVelocity};
}