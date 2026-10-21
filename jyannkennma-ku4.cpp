#include "Janken.h"

int main() {
    // 【変更】引数付きコンストラクタでプレイヤー名を指定
    JankenGame game("Taro");
    game.play();
    return 0;
}