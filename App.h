#pragma once

#include<SFML/Graphics.hpp>
#include <stack>
#include "cint.h"
#include <vector>
#include <iostream>

class App {
public:
    void show();
    App();

private:
    sf::RenderWindow *window;
    std::stack <std::pair<cint, cint>> *conditions;

    cint *cur_left;
    cint *cur_right;

    sf::Texture texture;

    int scale = 4;
    int mode;
    cint c_;

    int mondelbrot_check(cint c);
    int zhulia_check(cint z);
    void draw();
    void update();
    void window_update(sf::RectangleShape &rect);
    void returning();
    void animation();

};
