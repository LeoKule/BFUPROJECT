#include "Dart.h"
#include "Dart_game.h"
#include "Logger.h"

namespace dg {
    Dart::Dart(float X, float Y, float W, float H, float Angle, float V0){
        s_x = X; s_y = Y; s_w = W; s_h = H; s_angle = Angle; s_v0 = V0; s_t = 0; isPushed = false; s_x0 = X; s_y0 = Y;
        uploadTexture();
        m_shape.setPosition(s_x, s_y);
        m_shape.setOrigin(sf::Vector2f(s_w, s_h));
        m_shape.setTexture(m_texture);
    }

    bool Dart::uploadTexture() {
        if (!m_texture.loadFromFile("data/img/drotic.png")) {
            std::cout << "ERROR when loading drotic.png" << std::endl;
            return false;
        }
        m_texture.setSmooth(true);
        return true;
    }

    sf::Sprite &Dart::getShape() {
        return m_shape;
    }

    void Dart::setPushed(bool put) {
        isPushed = put;
    }

    void Dart::setStartPosition(float X0, float Y0) {
        this->s_x0 = X0;
        this->s_y0 = Y0;
        s_x = s_x0;
        s_y = s_y0;
        m_shape.setPosition(0, 0);
    }

    void Dart::setAngle(float Angle) {
        this->s_angle = Angle;
    }

    void Dart::setInitialSpeed(float V0) {
        this->s_v0 = V0;
    }

    void Dart::setSelfTime(float Time) {
        s_t = Time;
    }

    void Dart::addSelfTime(float time) {
        s_t += time;
    }

    void Dart::setPosition(float X, float Y) {
        if (X - s_w + 30 < 0)
            s_x = s_w - 30;
        else if (X + s_w - 30 > WIDTH)
            s_x = WIDTH - s_w + 30;
        else
            s_x = X;
        if (Y - s_h < 0)
            s_y = s_h;
        else if (Y + s_h > HEIGHT)
            s_y = HEIGHT - s_h;
        else
            s_y = Y;
        m_shape.setPosition(s_x, s_y);
    }

    void Dart::Move(Scoreboard &scoreboard) {
        if (s_x + s_w - 30 >= WIDTH && (s_y < 64 || s_y > 414) ||
            (s_x + s_w - 10 >= WIDTH) && !(s_y < 64 || s_y > 414)) {
            scoreboard.addScore(getPoints());
            std::this_thread::sleep_for(500ms);
            this->s_v0 = 5;
            this->s_angle = M_PI / 2;
            this->setPosition(250, 150);
            this->setStartPosition(250, 150);
            s_t = 0;
            isPushed = false;
            std::cout << s_x << std::endl;
        } else if ((!isPushed && s_y + s_h <= 400) ||
                   (isPushed && s_x - s_w + 30 > 0 && s_y - s_h > 0 && s_y + s_h < HEIGHT)) {
            std::cout << s_x << std::endl;
            // Perform dart movement based on the elapsed time and initial velocity
            float x = s_x0 + s_v0 * cos(s_angle) * s_t;
            float y = s_y0 + s_v0 * sin(s_angle) * s_t + G * s_t * s_t / 2;
            m_shape.setPosition(x, y);
            m_shape.setRotation(dg::getAngle(s_x0, s_y0, s_x, s_y) * (180.0 / M_PI));
        } else if (isPushed) {
            std::cout << s_x << std::endl;
            scoreboard.addScore(-10);
            std::this_thread::sleep_for(500ms);
            this->s_v0 = 5;
            this->s_angle = M_PI / 2;
            this->setPosition(240, 150);
            this->setStartPosition(240, 150);
            s_t = 0;
            isPushed = false;
        }

    }

    float Dart::getX() const {
        return s_x;
    }

    float Dart::getY() const {
        return s_y;
    }

    float Dart::getHeight() const {
        return s_h;
    }

    float Dart::getWidth() const {
        return s_w;
    }

    void Dart::draw(sf::RenderWindow &window) {
        window.draw(m_shape);
    }

    int Dart::getPoints() const {
        if (64 <= s_y && s_y <= 139 || 339 <= s_y && s_y <= 414) {
            return 1;
        } else if (139 < s_y && s_y <= 189 || 289 <= s_y && s_y < 339) {
            return 3;
        } else if (189 < s_y && s_y <= 224 || 254 <= s_y && s_y < 289) {
            return 5;
        } else if (224 <= s_y && s_y <= 254) {
            return 10;
        } else
            return -5;
    }

}
