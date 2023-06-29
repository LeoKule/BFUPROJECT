#include "Scoreboard.h"

namespace dg {
    Scoreboard::Scoreboard() : score(0), deltaScore(0), textBox(20, 20, "Number of points: 0") {}

    void Scoreboard::addScore(int Score) {
        deltaScore = Score;
        this->score += Score;
        update();
    }

    sf::Text Scoreboard::getShape() {
        return textBox.getShape();
    }

    void Scoreboard::update() {
        textBox.setText("Number of points: " + std::to_string(score) + " (added " + std::to_string(deltaScore) + " points)");
    }

    void Scoreboard::draw(sf::RenderWindow& window) {
        textBox.draw(window);
    }
}
