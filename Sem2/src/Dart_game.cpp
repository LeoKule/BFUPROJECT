#include "Dart_game.h"

namespace dg {
    DartGame::DartGame() : window(sf::VideoMode(WIDTH, HEIGHT), "Dart Game", sf::Style::Close), dart(250, 150, 124/2, 33/2, 0, 0), scoreboard(), textBox(20, 20, "") {
    }

    float getAngle1(float x0, float y0, float x1, float y1) {
        float dy = y1 - y0;
        float dx = x1 - x0;
        float angle = atan(dy / dx);
        if (dx < 0)
            angle += acos(-1);
        if (dx == 0 && dy == 0) {
            angle = 0;
        }
        return angle;
    }

    float DartGame::getDistance(float x0, float y0, float x1, float y1) {
        // поиск расстояния между точками
        return sqrt(pow((x1 - x0), 2) + pow(y1 - y0, 2));
    }


    bool moveWhenPush(sf::RenderWindow &window, Dart &dart, Scoreboard &scoreboard){
        sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
        auto mouseX = static_cast<float>(mouse_position.x);
        auto mouseY = static_cast<float>(mouse_position.y);
        // обработка позиции мыши для проверки попадания по хитбоксу дротика для последующего перемещения
        if ((dart.getX() + dart.getWidth() >= mouseX &&
             dart.getX() - dart.getWidth() <= mouseX) &&
            (dart.getY() + dart.getWidth() >= mouseY &&
             dart.getY() - dart.getWidth() <= mouseY) && mouse_position.x <= 500) {
            dart.setPushed(true);
            // пока ЛКМ зажата происходит смена положения дротика вслед за мышью и её поворот вокруг собственной оси
            while (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                mouse_position = sf::Mouse::getPosition(window);
                // обработка выхода за ограничительную линию
                if (mouse_position.x <= 500) {
                    if (dart.getX() != mouseX && dart.getY() != mouseY)
                        dart.getShape().setRotation(
                                dg::getAngle1(dart.getX(), dart.getY(), mouseX, mouseY) *
                                (180.0 / M_PI));

                    dart.setPosition(mouseX, mouseY);
                } else {
                    sf::Mouse::setPosition(sf::Vector2i(500, mouse_position.y), window);
                }

            }
            // если пользователь попал возвращаем true
            return true;
        }
        return false;
    }


    void DartGame::run() {
        window.setFramerateLimit(144);
        while (window.isOpen()) {
            processEvents();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            }
            render();
            update();
            dart.addSelfTime(dg::D_T);
        }
    }

    void DartGame::processEvents() {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        sf::Vector2i mouse_position1 = sf::Mouse::getPosition(window);
        auto mX = static_cast<float>(mouse_position1.x);
        auto mY = static_cast<float>(mouse_position1.y);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            if (dg::moveWhenPush(window, dart, scoreboard))
                std::this_thread::sleep_for(std::chrono::milliseconds(40));
            float x0 = dart.getX();
            float y0 = dart.getY();
            float x1 = mX;
            float y1 = mY;
            dart.setStartPosition(dart.getX(), dart.getY());

            dart.setInitialSpeed(DartGame::getDistance(x0, y0, x1, y1));
            dart.setAngle(dg::getAngle1(x0,y0,x1,y1));

            dart.setSelfTime(0);
        }
    }

    void DartGame::update() {
        dart.Move(scoreboard);
        scoreboard.update();
    }

    void DartGame::render() {
        window.clear();
        sf::Sprite BackgroundSprite;
        sf::Texture BackgroundTexture;
        if(BackgroundTexture.loadFromFile("data/img/back.jpg")){
            BackgroundSprite.setTexture(BackgroundTexture);
            window.draw(BackgroundSprite);
        }

        dart.draw(window);
        scoreboard.draw(window);
        textBox.draw(window);
        window.display();
    }
}
