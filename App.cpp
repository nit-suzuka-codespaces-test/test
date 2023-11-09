/*
 * Block崩し
 * Appクラス実装（このファイルは書き換えなくてよい）
 */

#include <cstdlib>
#include <iostream>
#include <time.h>
#include <sys/time.h>
#ifdef __MACH__
#include <mach/clock.h>
#include <mach/mach.h>
#ifndef CLOCK_MONOTONIC
#define CLOCK_MONOTONIC 1
#endif

int clock_gettime(clock_id_t clk_id, timespec *tp){
  clock_serv_t cclock;
  mach_timespec_t mts;
  host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);
  clock_get_time(cclock, &mts);
  mach_port_deallocate(mach_task_self(), cclock);
  tp->tv_sec = mts.tv_sec;
  tp->tv_nsec = mts.tv_nsec;
  return 0;
}
#endif

#include <SFML/Graphics.hpp>

#include "App.h"

// コンストラクタ
App::App():w_width(640),w_height(480),window(sf::VideoMode(w_width,w_height), "sample")
{
  this->keyListener = NULL;
  this->mouseListener = NULL;
}
App::~App(){
}
void App::setKeyboardListener(KeyboardListener *keyListener){
  this->keyListener = keyListener;
}
void App::setMouseListener(MouseListener *mouseListener){
  this->mouseListener = mouseListener;
}
void App::init(){
}
bool App::isActive(){
  return window.isOpen();
}

void App::draw(){
  window.clear();
}

void App::event(){
  sf::Event event;
  while(window.pollEvent(event)){
    if (event.type == sf::Event::Closed) // 
      window.close();
    // キーボード
    if (event.type == sf::Event::EventType::KeyPressed)
      if(this->keyListener!=NULL)
	      this->keyListener->onKeyDown(event.key.code);
    // マウス動き
    if (event.type == sf::Event::MouseMoved)
      if(this->mouseListener!=NULL)
	      this->mouseListener->onMouseMoved(event.mouseMove);
    // マウスボタン押し
    if (event.type == sf::Event::MouseButtonPressed)
      if(this->mouseListener!=NULL)
        this->mouseListener->onClick(event.mouseButton);
    // マウスボタン離し
    if (event.type == sf::Event::MouseButtonReleased)
      if(this->mouseListener!=NULL)
	        this->mouseListener->offClick(event.mouseButton);
  }
}

void App::waitSync(){
    static timespec prev;
    timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    struct timespec ts;
    double diff_d = (now.tv_sec*1000000000 + now.tv_nsec) - (prev.tv_sec*1000000000 + prev.tv_nsec);
    double targetFPS = 60; // FPS

    double wait_d=1./targetFPS*1000000000-diff_d;
    unsigned wait = static_cast<unsigned>(wait_d);
    ts.tv_sec = 0;
    ts.tv_nsec = wait;
    nanosleep(&ts, NULL);
    prev = now;
}
