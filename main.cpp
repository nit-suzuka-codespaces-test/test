/*
 * Block崩し
 * main()関数(エンドポイント)の処理
 * このファイルは書き換える必要ない
 */
#include <iostream>
#include <cmath>

#include "MyApp.h"
int main()
{
  MyApp myapp;
  
  myapp.init(); // 初期化
  
  while (myapp.isActive()){ // myappがactiveな間動く
    myapp.event();    // イベント処理 
    myapp.update();   // オブジェクトの更新処理
    myapp.draw();     // オブジェクトの描画処理
    myapp.waitSync(); // タイミング調整
  }

  return 0;
}
