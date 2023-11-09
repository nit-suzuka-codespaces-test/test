/*
 * Block崩し
 * MyAppクラス実装（このファイルに処理を追加していく）
 */

#include <cstdlib>
#include <iostream>
#include <time.h>
#include <sys/time.h>

#include "MyApp.h"

MyApp::MyApp()
{
  // bar
  bar.setSize(sf::Vector2f(50, 10));
  bar.setFillColor(sf::Color(255, 255, 0));
  bar.setPosition(sf::Vector2f(100, w_height - bar.getSize().y));

  ball.setSize(sf::Vector2f(10, 10));
  ball.setFillColor(sf::Color(255, 255, 255));
  ball.setPosition(sf::Vector2f(w_width / 2, w_height / 2));
  ball.setVelocity(sf::Vector2f(100, 100));

  setKeyboardListener(this);
  setMouseListener(this);
}

MyApp::~MyApp()
{
}

// オブジェクトの更新処理
void MyApp::update()
{
  sf::Time elapsed = clock.restart();
  float dt = elapsed.asSeconds(); // dtは微小時間、これを使ってオブジェクトを少し動かしたりする
  ball.boundaryCheck(dt, w_width, w_height);
  ball.collision(dt, bar);
  for (auto &block : blocks)
  {
    if (!block.isRemove())
    {
      bool collision = ball.collision(dt, block);
      if (collision)
      {
        block.erase();
      }
    }
  }
  ball.update(dt);
}

// オブジェクトの描画処理
// すべてのオブジェクトはwindow.clear()とwindow.display()の間で描画する
void MyApp::draw()
{
  window.clear(); //　ウインドウ(window)をクリアする

  window.draw(bar); // バーオブジェクトをwindowに描画する

  window.draw(ball);

  for (auto &block : blocks)
  {
    if (!block.isRemove())
    {
      window.draw(block);
    }
  }

  window.display(); // windowを表示する
}

// キーボードが押された時の処理
void MyApp::onKeyDown(sf::Keyboard::Key key)
{
  if (key == sf::Keyboard::Escape)
  {                 // Escキーが押されたら
    window.close(); // windowをクローズする(終了する)
  }
}

// マウスが動いたときの処理
void MyApp::onMouseMoved(sf::Event::MouseMoveEvent mouse)
{
  bar.setPosition(mouse.x, w_height - bar.getSize().y); // マウスのx位置をバーのx位置にする y画面下部
}

// マウスボタンが押された時の処理
void MyApp::onClick(sf::Event::MouseButtonEvent mouse)
{
}

// マウスボタンが離された時の処理
void MyApp::offClick(sf::Event::MouseButtonEvent mouse)
{
}
