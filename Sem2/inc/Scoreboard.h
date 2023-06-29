#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include "Drawable.h"
#include "TextBox.h"

namespace dg {
    class Scoreboard : public Drawable {
    public:
        Scoreboard();

        void addScore(int score);

        sf::Text getShape();

        void update();

        void draw(sf::RenderWindow& window) override;



    private:
        long int score;
        int deltaScore;
        TextBox textBox;
    };
}

#endif  // SCOREBOARD_H
