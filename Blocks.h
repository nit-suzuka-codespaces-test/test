#pragma once
#include <iostream>
#include <list>
using namespace std;
#include <SFML/Graphics.hpp>
#include "Block.h"

class Blocks {
private:
    list<Block> blocks;
public:
    Blocks();
    ~Blocks();
    list<Block>::iterator begin();
    list<Block>::iterator end();

    void update(double dt);
};