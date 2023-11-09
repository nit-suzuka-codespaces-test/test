# SFMLを使ったブロック崩し

## レポート

以下のレポートを作成し、PDFファイルとしてでMoodleに提出すること

  - 実装できたところまでのブロック崩しの仕様
    何ができるゲームになっているか
  - 実装できたところのUMLクラス図（ただし、SFMLのクラスはクラス名だけでOK）
    draw.ioあるいはastahを使ってクラス図を作成する
  - 付け加える機能のアイデア（実装しなくても良い）
  - 技術、知識で足りないと感じたところ
  - 感想

### 配布したファイルの説明

  - 端末で`make`を使ってビルドする
  - 実行ファイル名は`main`
    ```
    ./main
    ```
  - マウスイベントの左右の動きに合わせて、黄色の横長の四角形が動作する。

### 解説

- Appクラス (App.h, App.cpp)

  このクラスは、アプリケーションを作るときの基本クラスを想定している。
  アプリーケーションは、初期化、イベント処理、内部状態の更新、描画、片付けの処理で構成されるとし、
  それぞれの処理をメンバ関数で記述することになる。**このファイルはいじる必要ない**。

- main関数 (main.cpp)
  このクラスはMyAppクラスのオブジェクトを作り、初期化呼び出し(init)を行ったのち、ループに入る。
  ループ内ではイベント処理(event)、内部状態の更新(update)、描画(draw)、タイミング調整(waitSync)、を
  ある条件が成立している間(isActive)続く、という流れになっている。**このファイルはいじる必要ない**。

- MyAppクラス (MyApp.h, MyApp.cpp)
  このクラスは、Appクラスを継承し、自分の動作を行うアプリケーションを記述するときに用いる。
  **このクラスにさまざまなオブジェクトや変数を作成し、実際のアプリケーションの動作を記述していく**。

- コンストラクタでバーオブジェクトの設定している(MyApp.cpp:15-17行)。
- マウスの動きに応じてイベントが発生し、onMouseMovedが呼ばれる。ここでは、左右方向のみマウス位置をバーに反映させ、上下方向には移動しないようになっている(MyApp.cppの51行目)。
- 描画処理(draw)では、ウインドウをクリアし(MyApp.cpp:35行)、バーを表示した後(MyApp.cpp:37行)、描画処理する(MyApp.cpp:39行)という流れになっている。追加するオブジェクトの描画はwindow.clear()とwindow.display()の間に記述する。

- Makefile
  コンパイルの手順を書いたもの。クラスを追加(ファイルを追加)した場合には、**Makefileに追加する必要がある**。

## [課題1] ボールの追加

ウインドウ内を跳ね返るボールを追加する。本来は画面下部にはみ出た場合はゲームオーバーとなるが、デバッグのために全範囲でウインドウの周囲に到達したら跳ね返るようにする。

### [課題1 ステップ1] Ballクラスの作成

- 新規なファイルBall.hおよびBall.cppを作成する。BallクラスはSFMLの四角形クラス(sf::RectangleShapeクラス)を継承し、速度を扱えるように変更する。

```c++:Ball.h
// Ball.h
#pragma once
#include <SFML/Graphics.hpp>

class Ball : public sf::RectangleShape {
  private:
    sf::Vector2f vel; // ボールの速度
  public:
    void setVelocity(sf::Vector2f v); // 速度を設定する
    void update(double dt);           // ボールの位置を更新する
};
```

対応するBall.c++を作成する。

```c++:Ball.cpp
// Ball.cpp
#include <cmath>
#include <iostream>
#include "Ball.h"
using namespace std;

void Ball::setVelocity(sf::Vector2f v){
    ここを実装する
}
void Ball::update(double dt){
    ここを実装する
}
```

- setVelocityの内容は、メンバ変数velに引数で受け取ったvを代入するだけ。
- updateの内容は、時間dt後のボールの位置を計算する。現在のボールの位置は、親クラスのRectangleShapeが持っているので、

  ```c++
  sf::Vector2f pos = this->getPosition();
  ```

  のようにすれば得られる。速度と時間dtを使いdt後の位置を計算し、setPositionを使って、位置を設定する。

- MyApp:クラス定義(MyApp.h))

  ボールオブジェクトをメンバ変数として作成する。Ball.hをincludeするのを忘れずに。

- MyApp:コンストラクタ(MyApp.cpp)

  コンストラクタでボールオブジェクトの大きさを(10,10)、色を白、初期位置をウインドウ中心 w_width/2, w_height/2)、速度を100,100に設定する。

- MyApp::update(MyApp.cpp)

  ボールオブジェクトのupdateメンバ関数を呼び出すようにしておく

- MyApp::draw(MyApp.cpp)

  ボールオブジェクトのdrawメンバ関数を呼び出すのを追加しておく（追加する場所に注意すること）

コンパイルするときにはMakefileのSRCにBall.cppを加えること。

```makefile
SRCS   = $(TARGET).cpp MyApp.cpp App.cpp Ball.cpp
```

ここで一旦ビルドし、動作確認する。
ボールが表示され、右下に向かって動き出せばOK。しかし、このままでは画面をはみ出してしまうので、次で対応する。

### [課題1 ステップ2] Ballクラスをウインドウ内で反射させる
#### ボールが枠の外にはみ出たかどうかを判定する機能を追加する

- Ballクラスに以下のメンバ関数を追加する。
  ```c++
  void Ball::boundaryCheck(double dt, unsigned w_width, unsigned w_height)
  ```

  内容は、「dt後の位置」がウインドウの範囲外に出てしまったら、速さの方向を反対にして、位置を範囲内に戻すという処理にする。
  dt後の位置が範囲外に出る前に反射させるのがポイント。

- MyApp::update
  ボールのupdateの前に boundaryCheck を呼び出す。

#### ボールがバーに当たったときに反射するようにする

- BallクラスとRectangleShapeの当たり判定
  以下のメンバ関数を追加する
  ```c++
  bool Ball::collision(double dt, const sf::RectangleShape& rect)
  ```
  内容は、もし、dt後にボールとrectが衝突していたら、x,y方向を共に反射させ、trueを返却する。衝突していなければfalseを返却する。
  基本的に四角形同士の衝突なので、二つの四角形の位置と幅、高さで計算できる（図を書いて考えてみよ）
  boundaryCheckの時と同様に、dt後のボール位置がrectと衝突する前にあたり判定を行い反射させるのがポイント(余裕がある場合は現在時刻でもやってみて比較すると良い)。

- MyApp::update
  ボールのupdateの前に collision を呼び出す

ここで一旦ビルドし、動作確認する。
ボールが表示され、右下に向かって動き出し、範囲外に出るときに反射していればOK。

## [課題2] ブロックを作る

###  [課題２ ステップ2] ブロッククラス

ブロックもSFMLのRectangleShapeクラスを継承して作成する。メンバ変数として消すかどうかのフラグを追加し、その値の設定、と値の確認ができるようにする。以下のBlock.hとBlock.cppの二つのファイルを作成する。
  ```c++:Block.h
  // Block.h
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
  ```

  ```c++:Block.cpp
  // Block.cpp
  #include "Block.h"

  void Block::erase(){
      remove = true;
  }
  ```
ここで一旦ビルドする。ビルドできることだけ確認しておく。

###  [課題２ ステップ2]  ブロック管理クラス

ブロック管理クラスは、複数のブロックを持ち、それを管理するクラスである。

複数のブロックを保持するためには、何らかのデータ構造が必要となる。これまでの講義の範囲では配列を使うしか方法はない。しかし、配列はいろいろと面倒なので、後期に学習するSTL(Standard Template Library)からlistクラスを使うことにする。

listは双方向リストというデータ構造を提供するクラスである。配列とは異なり、後から動的に保持するオブジェクトの数を変えられる(追加したり減らしたりできる)。

- メンバ変数はBlockクラスのオブジェクトを要素に持つlist。listの詳細はSTLのlistを検索すること。
- メンバ関数としてコンストラクタ、begin(), end()を作る。begin(), end()は、MyAppで利用するときに範囲forを使うため。(範囲forはc++11で追加された機能。これも詳細は各自で調べる)

  ```c++:Blocks.h
  // Blocks.h
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
  ```

- コンストラクタでは、10個のブロックを作成し、並べている。ここは各自で適当に変更できる。
- デストラクタは、リストに連なっている全てのブロックオブジェクトをdeleteする。
- begin, endは単にlistのbegin, endを返却するだけ

  ```c++:Blocks.cpp
  // Blocks.cpp
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

  list<Block*>::iterator Blocks::end() {
      return blocks.end();
  }

  void Blocks::update(double dt){
  }
  ```

ここで一旦ビルドする。ビルドできることだけ確認しておく。

### [課題２ ステップ3] MyApp

- MyApp.hでメンバ変数としてBlocksオブジェクトを1つ追加する。
- MyApp:updateでは、ボールとバーの衝突判定の後で、ボールとブロック群との衝突判定を行う。以下のように、範囲forを使って、ブロック群から一つずつブロックを取り出し、衝突判定して、衝突していたらブロックに消すマークをつける。その後、blocksのupdate関数を呼び出しておく。

  ```c++:myApp.cpp
    for (auto& block:blocks){
      bool collision = ball.collision(dt, *block);
      if (collision){
        block->erase();
      }
    }
  ```

- MyApp::draw 上記のupdateのように範囲forを使って、
一つ一つのブロックが消去対象でないもの(isRemove()がfalseなもの)に対して、ブロックを描画(draw)する。ブロック一つ一つはRectangleShapeを継承していることに注意する。

  ```c++:myApp.cpp
    for (auto block:blocks){
      if (!block->isRemove()){
        window.draw(*block);
      }
    }
  ```

以上で、バーの操作、ボールの動き、ブロックの表示、ボールとバー/ブロックの衝突判定と、ブロックの消去、までが行える。あとは、ゲームオーバの処理や得点計算などを行えば、一通り遊べるものができる。

また、複数のボールを使ったり、Blockクラスを継承してブロックに固さの概念を導入した新しいクラスを作り、ポリモーフィズムを使って拡張することが可能である。（基本クラスのポインタをリストに入れておけば、オブジェクト作成時にどんな種類のブロックを作るかだけ考えれば良くなる）。
夏休みにヒマな人は、これをベースに遊びながらコーディングすると良いでしょう。
