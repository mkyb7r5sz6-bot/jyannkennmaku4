#pragma once
#include <iostream>
#include <string>
#include <array>
using namespace std;

enum class Hand { Rock = 0, Scissors = 1, Paper = 2 };
enum class Result { Draw, Win, Lose };

class Player {
private:
    string name;
    Hand currentHand; // 【変更】手を保持するメンバ変数

public:
    Player(string initialName); // 【変更】引数付きコンストラクタ
    void inputName();
    void chooseHand(); // 【変更】戻り値をvoidにし、内部で保持する
    string getName() const { return name; }
    Hand getHand() const { return currentHand; } // 【追加】保持した手を取得するゲッター
};

class Cpu {
private:
    Hand currentHand; // 【変更】手を保持するメンバ変数（private）

public:
    void chooseHand(); // 【変更】戻り値をvoidにし、内部で保持する
    Hand getHand() const { return currentHand; } // 【追加】保持した手を取得するゲッター
};

class JankenGame {
private:
    Player player;
    Cpu cpu;
    array<int, 3> score;
    int round;
    static constexpr array<const char*, 3> HandNames = { "ぐー", "チョキ", "パー" };

    Result judge(Hand playerHand, Hand cpuHand) const;
    string getHandName(Hand hand) const;

public:
    JankenGame(string playerName); // 【変更】引数付きコンストラクタ
    void play();
};
