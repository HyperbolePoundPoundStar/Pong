#include <iostream>
#include <thread>
#include <chrono>
#include <SFML/Graphics.hpp>

#include "Paddle.hpp"
#include "Puck.hpp"
#include "EnemyAi.hpp"
#include "Misc.hpp"

sf::SoundBuffer ScoreBuffer;
sf::Sound ScoreAudio(ScoreBuffer);

float PaddleSpeed = 5;
float EnemyPaddleSpeed = 5;

int PlayerScore = 0;
int EnemyScore = 0;

sf::Clock Cooldown;

void InitScoreBuffer(){
    ScoreBuffer.loadFromFile("Assets/Score.wav");
}

void UpdateScore(sf::RenderWindow& Window, sf::View& View){
    sf::Vector2f ViewSize = View.getSize();

    if(PuckPosition.x - PuckRadius < 0.f){
        EnemyScore += 1;
    }
    else if(PuckPosition.x + PuckRadius > ViewSize.x){
        PlayerScore += 1;
    }
    else{
        return;
    }

    Window.clear();
    ScoreAudio.play();

    PuckPosition = {ViewSize.x / 2.f, ViewSize.y / 2.f};
    PuckVelocity = {-PuckVelocity.x, PuckVelocity.y};

    PaddlePosition.y = ViewSize.y / 2.f;
    EnemyPaddlePosition.y = ViewSize.y / 2.f;

    ForceUpdatePuck(Window, View);
    ForceUpdatePaddle(Window, View);
    ForceUpdateEnemyPaddle(Window, View);

    Cooldown.restart();
}

void UpdateGame(sf::RenderWindow& PongWindow, sf::View& View){
    PongWindow.clear();
        
    UpdatePaddle(PongWindow, View, PaddleSpeed);
    UpdateEnemyPaddle(PongWindow, View, EnemyPaddleSpeed);
    UpdatePuck(PongWindow, View);
    UpdateScore(PongWindow, View);

    PongWindow.display();
}

int main(){
    sf::RenderWindow PongWindow(sf::VideoMode({800, 600}), "Pong Game", sf::Style::Titlebar | sf::Style::Close);
    PongWindow.setFramerateLimit(60);
    sf::View View = PongWindow.getView();

    InitPuck(View);
    InitPaddle(View);
    InitEnemyPaddle(View);
    InitScoreBuffer();
    InitPuckHitBuffer();
    UpdateGame(PongWindow, View);

    while (PongWindow.isOpen()){

        while (const std::optional Event = PongWindow.pollEvent()){
            if (Event->is<sf::Event::Closed>()){
                PongWindow.close();
            }
        }

        View = PongWindow.getView();

        if(Cooldown.getElapsedTime().asSeconds() < 1.5f){
            continue;
        }

        UpdateGame(PongWindow, View);
    }

    return 0;
}