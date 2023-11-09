#include "Blocks.h"

Blocks::Blocks(){
    for (int i=0; i<10; i++){ //ブロックは10個作る
        Block ablock; // 一つ作って
        ablock.setPosition(40+41*i, 10); // 位置の設定
        ablock.setSize(sf::Vector2f(40,20)); // 大きさの設定
        blocks.push_back(ablock); // 双方向リストに追加する
    }
}

Blocks::~Blocks(){
    blocks.clear();
}

list<Block>::iterator Blocks::begin() {
    return blocks.begin();
}

list<Block>::iterator Blocks::end() {
    return blocks.end();
}

void Blocks::update(double dt){
}