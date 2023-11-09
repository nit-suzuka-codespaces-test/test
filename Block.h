#pragma once
#include <SFML/Graphics.hpp>

class Block : public sf::RectangleShape {
    private:
        bool remove; // ブロックを消すか否か
    public:
        Block():remove(false){ // コンストラクタ
            this->setFillColor(sf::Color(0,0,255));
        }
        void erase();           // ブロックを消す処理
        bool isRemove(){return remove;} // 消すかどうかを返す
};