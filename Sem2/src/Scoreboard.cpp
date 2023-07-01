#include "../inc/Scoreboard.h"


namespace dg {
    Scoreboard::Scoreboard() {
        d_s = 0;
        //textBox = new TextBox(20,20, "Number of points: " + std::to_string(s_score));
        //textBox = new TextBox(20, 20, "Number of points: " + std::to_string(s_score),"Darts: " + std::to_string(dart_count));
        textBox = std::make_unique<TextBox>(20, 20, "Number of points: " + std::to_string(s_score) + " " + "Darts: " + std::to_string(dart_count));
    }

    int Scoreboard::get_count() {
        return dart_count;
    }

    int Scoreboard::get_score() {
        return s_score;
    }

    void Scoreboard::restart() {
        s_score = 0;
        dart_count = 0;
        d_s = 0;
    }

    Scoreboard::~Scoreboard() = default;

    //void Scoreboard::Reset(int x, int y, std::string Score, int count) {
        //textBox = std::make_unique<TextBox>(20, 20, "Number of points: " + std::to_string(s_score)+ " " " " "Darts: " + std::to_string(dart_count));
    //}

    void Scoreboard::addScore(int score) {
        dart_count ++;
        d_s = score;
        s_score += score;
        update();
    };

    void Scoreboard::update() {
        textBox->setText("Number of points: " + std::to_string(s_score) + " (added " + std::to_string(d_s) + " points)" + " " + "Darts: " + std::to_string(dart_count));
    }
   // " " " ""Darts: " + std::to_string(dart_count)
    sf::Text *Scoreboard::getShape() {
        return textBox->getShape();
    }

    /*void Scoreboard::deleteMyself() {
        delete textBox->getShape();
        //delete textBox;
    }*/

}