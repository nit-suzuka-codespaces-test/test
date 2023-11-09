#pragma once
#include <SFML/Graphics.hpp>

class Ball : public sf::RectangleShape {
  private:
    sf::Vector2f vel; // ボールの速度
    sf::Vector2f positionAfter(double dt);

  public:
    void setVelocity(sf::Vector2f v); // 速度を設定する
    void update(double dt);           // ボールの位置を更新する

    void boundaryCheck(double dt, unsigned w_width, unsigned w_height);

    bool collision(double dt, const sf::RectangleShape& rect);
};