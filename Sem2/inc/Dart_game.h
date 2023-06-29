#ifndef DART_GAME_H
#define DART_GAME_H

#include "SFML/Graphics.hpp"
#include "Dart.h"
#include "Scoreboard.h"
#include "TextBox.h"
#include <thread>
#include "fstream"
#include <chrono>
#include <vector>
#include <iostream>
#include <cmath>

#define WIDTH 1164
#define HEIGHT 640
using namespace std::chrono_literals;

#define WIDTH 1164
#define HEIGHT 640

namespace dg {
    //ускорение свободного падения и т д для формул
    const float G = 9.8;
    const float D_T = 0.04;
    const double PI = acos(-1);

    float getAngle(float x0, float y0, float x1, float y1);

    void update(sf::RenderWindow &window, Dart &dart, Scoreboard &scoreboard, const sf::Sprite& background);

    bool moveWhenPush(sf::RenderWindow &window, Dart &dart, Scoreboard &scoreboard, const sf::Sprite& background);

    float getDistance(float x0, float y0, float x1, float y1);

    void startGame(sf::RenderWindow &window, Dart &dart, Scoreboard &scoreboard, const sf::Sprite& background);
}

#endif  // DART_GAME_H
