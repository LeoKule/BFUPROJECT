#include <SFML/Graphics.hpp>
#include "Dart.h"
#include "Dart_game.h"
#include "Scoreboard.h"
#include "TextBox.h"

int main() {
    //sf::RenderWindow window(sf::VideoMode(800, 600), "Dart Game");

   //dg::Dart dart(250, 150, 20, 20, M_PI / 2, 5);
   // dg::Scoreboard scoreboard;
    //dg::TextBox textBox(20, 20, "Number of points: 0");
    dg::DartGame game;
    game.run();
    sf::Clock clock;

    return 0;
}
