/*
 * Block崩し
 * Appクラス定義（このファイルは書き換えなくてよい）
 */

// マウスリスナーのインターフェース定義
class MouseListener {
public:
  virtual void onClick(sf::Event::MouseButtonEvent mouse)=0;    // マウスボタン押したときの処理
  virtual void offClick(sf::Event::MouseButtonEvent mouse)=0;   // マウスボタン離したときの処理
  virtual void onMouseMoved(sf::Event::MouseMoveEvent mouse)=0; // マウスを動かしたときの処理
};

// キーボードリスナーのインターフェース定義
class KeyboardListener {
public:
  virtual void onKeyDown(sf::Keyboard::Key key)=0;  // キーが押された時の処理
};

// Appクラスの定義
class App {
protected:
  unsigned w_width;              // 表示するウインドウの幅
  unsigned w_height;             // 表示するウインドウの高さ
  sf::RenderWindow window;       // 表示するウインドウオブジェクト
  KeyboardListener* keyListener; // キーボードリスナー
  MouseListener* mouseListener;  // マウスリスナー
  sf::Clock clock;
public:
  App();
  virtual ~App();
  void setKeyboardListener(KeyboardListener *keyListener);
  void setMouseListener(MouseListener *mouseListener);
  virtual void init();
  virtual bool isActive();
  virtual void draw();
  virtual void update() = 0;
  virtual void event();
  virtual void waitSync();
};
