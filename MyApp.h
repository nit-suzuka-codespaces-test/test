/*
 * Block崩し
 * MyAppクラス定義（このファイルに処理を追加していく）
 */

#pragma once
#include <SFML/Graphics.hpp>
#include "App.h"
#include "Ball.h"
#include "Blocks.h"

class MyApp : public App, public KeyboardListener, public MouseListener {
private:
  sf::RectangleShape bar;  // バーオブジェクト
  Ball ball;
  Blocks blocks;

public:
  MyApp();
  ~MyApp();
  void update();
  void draw();
  void onKeyDown(sf::Keyboard::Key key);
  void onMouseMoved(sf::Event::MouseMoveEvent mouse);
  void onClick(sf::Event::MouseButtonEvent mouse);
  void offClick(sf::Event::MouseButtonEvent mouse);
};
