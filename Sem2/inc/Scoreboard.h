#pragma once
#ifndef SFML_SAMPLE_SCOREBOARD_H
#define SFML_SAMPLE_SCOREBOARD_H
#include <SFML/Graphics.hpp>
#include "Textbox.h"
#include "gameobject.h"

namespace dg{
    class Scoreboard {
    public:
        Scoreboard();

        ~Scoreboard();

        void addScore(int score);

        int get_count();

        int get_score();

        void restart();

        void update();

        sf::Text *getShape();


        //void Reset(int x, int y, std::string score, int count);

        //void deleteMyself();

    private:
        long int s_score = 0;
        int d_s;
        int dart_count = 0;

        //TextBox *textBox;
        std::unique_ptr<TextBox> textBox;
    };
}

#endif //SFML_SAMPLE_SCOREBOARD_H
