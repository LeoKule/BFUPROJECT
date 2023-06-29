#include <SFML/Graphics.hpp>
#include "Dart.h"
#include "Dart_game.h"
#include "Scoreboard.h"
#include "TextBox.h"
/*
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
*/


int main() {
    dg::Scoreboard scoreboard;
    sf::Sprite background;

    sf::Texture texture;
    if (!texture.loadFromFile("data/img/back.jpg")) {
        std::cout << "ERROR when loading back.jpg" << std::endl;
        return -1;
    }
    background.setTexture(texture);

    sf::Image icon;
    if (!icon.loadFromFile("data/img/dart.png")) {
        std::cout << "ERROR when loading dart.png" << std::endl;
        return -1;
    }

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML_Project", sf::Style::Close);
    window.setFramerateLimit(144);
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    // создание дротика с начальной позицией (250, 150) и цетром в точке (где 124 и 33 размеры изображения)
    dg::Dart dart(250., 150., 124 / 2, 33 / 2, 0, 0);

    dg::startGame(window, dart, scoreboard, background);

    return 0;
}