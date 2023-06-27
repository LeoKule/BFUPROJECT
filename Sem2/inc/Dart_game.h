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

namespace dg {

    const float G = 9.8;
    const float D_T = 0.04;
    class DartGame {
    public:
        DartGame();
         void run();

    private:
        float getDistance(float x0, float y0, float x1, float y1);
        sf::RenderWindow window;
        Dart dart;
        Scoreboard scoreboard;
        TextBox textBox;
        void processEvents();
        void update();
        void render();
    };
}

#endif  // DART_GAME_H
