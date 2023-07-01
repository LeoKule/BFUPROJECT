#include "SFML/Graphics.hpp"
#include "../inc/Darts_game.h"
#include "Scoreboard.h"
#include "Logger.h"

namespace dg {
    float getAngle(float x0, float y0, float x1, float y1) {
        // поиск угла между точками с отсчетом от начала координат
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

    void update(sf::RenderWindow &window, Dart &dart, Scoreboard &scoreboard, sf::Sprite background) {
        // обновление содержимого экрана
        window.clear();
        window.draw(background);
        window.draw(*scoreboard.getShape());
        window.draw(*dart.getShape());
        window.display();
    }

    /*void reset(sf::RenderWindow &window, Dart &dart, Scoreboard &scoreboard){
        dart.setStartPosition(250,150);
        //scoreboard.Reset();
    }*/

    bool moveWhenPush(sf::RenderWindow &window, Dart &dart, Scoreboard &scoreboard, sf::Sprite background) {
        sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
        auto mouse_x = static_cast<float>(mouse_position.x);
        auto mouse_y = static_cast<float>(mouse_position.y);
        // обработка позиции мыши для проверки попадания по хитбоксу дротика для последующего перемещения
        if ((dart.getX() + dart.getWidth() >= mouse_x &&
             dart.getX() - dart.getWidth() <= mouse_x) &&
            (dart.getY() + dart.getWidth() >= mouse_y &&
             dart.getY() - dart.getWidth() <= mouse_y) && mouse_position.x <= 500) {
            dart.setPushed(true);
            // пока ЛКМ зажата происходит смена положения дротика вслед за мышью и её поворот вокруг собственной оси
            try{
                while (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    mouse_position = sf::Mouse::getPosition(window);
                    auto m_x = static_cast<float>(mouse_position.x);
                    auto m_y = static_cast<float>(mouse_position.y);
                    // обработка выхода за ограничительную линию
                    if (mouse_position.x <= 500) {
                        if (dart.getX() != m_x && dart.getY() != m_y)
                            dart.getShape()->setRotation(
                                    dg::getAngle(dart.getX(), dart.getY(), m_x, m_y) *
                                    (180.0 / PI));
                        dart.setPosition(m_x, m_y);
                    } else {
                        sf::Mouse::setPosition(sf::Vector2i(500, mouse_position.y), window);
                    }
                    update(window, dart, scoreboard, background);
                }
            }
            catch (const std::exception& e){
                std::cerr << "Error";
            }
            // если пользователь попал возвращаем true
            return true;
        }
        return false;
    }

    float getDistance(float x0, float y0, float x1, float y1) {
        // поиск расстояния между точками
        auto Dist = static_cast<float>(sqrt(pow((x1 - x0), 2) + pow(y1 - y0, 2)));
        return Dist;
    }

    void startGame(sf::RenderWindow &window, Dart &dart, Scoreboard& scoreboard, sf::Sprite background){
        lg::Logger::Log(lg::LogLevel::Debug,"Something happened in the game");
        while (window.isOpen()) {
            sf::Event event{};
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }
            if (scoreboard.get_count() < 5) {
                //std::cout << "knife: " << dg::dart_count << std::endl;
                // если ЛКМ была нажата, то ждем до тех пор, пока пользователь ее не отпустит
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    if (dg::moveWhenPush(window, dart, scoreboard, background)) {
                        // делаем задержку на 40мс для получения вектора движения, по которому получим угол и скорость
                        std::this_thread::sleep_for(40ms);
                        sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
                        float x0 = dart.getX();
                        float y0 = dart.getY();
                        auto mouseX = static_cast<float>(mouse_position.x);
                        auto mouseY = static_cast<float>(mouse_position.y);

                        // сбрасываем отсчет пути и выставляем новые значения, которые получили ранее
                        dart.setStartPosition(dart.getX(), dart.getY());

                        dart.setInitialSpeed(dg::getDistance(x0, y0, mouseX, mouseY));
                        dart.setAngle(dg::getAngle(x0, y0, mouseX, mouseY));

                        dart.setSelfTime(0);
                    }
                }
            }
            else{
                TextBox over(400,310,"Press 'Space' to restart" " " "Your Score: " +  std::to_string(scoreboard.get_score()));
                window.clear();
                window.draw(*over.getShape());
                window.display();
                window.waitEvent(event);
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
                    scoreboard.restart();
                    scoreboard.update();
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            }
            dart.Move(scoreboard);

            update(window, dart, scoreboard, background);
            dart.addSelfTime(dg::D_T);
        }

    }

}