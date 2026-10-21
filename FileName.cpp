#include "Janken.h"
#include <cstdlib>
#include <ctime>
using namespace std;

// 【変更】引数付きコンストラクタの定義
Player::Player(string initialName) : name(initialName), currentHand(Hand::Rock) {}

void Player::inputName() {
    cout << "Enter your name: ";
    cin >> name;
}

// 【変更】じゃんけんの手をメンバ変数に保持する
void Player::chooseHand() {
    int inputHand = 0;
    while (true) {
        cout << "Choose your hand (0: Rock, 1: Scissors, 2: Paper): ";
        cin >> inputHand;
        if (inputHand >= 0 && inputHand <= 2) {
            break;
        }
        cout << "Invalid choice. Please choose 0, 1, or 2.\n";
    }
    currentHand = static_cast<Hand>(inputHand); // メンバ変数に代入
}

// 【変更】じゃんけんの手をメンバ変数に保持する
void Cpu::chooseHand() {
    currentHand = static_cast<Hand>(rand() % 3); // メンバ変数に代入
}

// 【変更】Playerのコンストラクタに名前を渡す
JankenGame::JankenGame(string playerName) : player(playerName), score({ 0, 0, 0 }), round(1) {
    srand(static_cast<unsigned int>(time(nullptr)));
}

Result JankenGame::judge(Hand playerHand, Hand cpuHand) const {
    if (playerHand == cpuHand) return Result::Draw;
    if ((playerHand == Hand::Rock && cpuHand == Hand::Scissors) ||
        (playerHand == Hand::Scissors && cpuHand == Hand::Paper) ||
        (playerHand == Hand::Paper && cpuHand == Hand::Rock)) {
        return Result::Win;
    }
    return Result::Lose;
}

string JankenGame::getHandName(Hand hand) const {
    size_t index = static_cast<size_t>(hand);
    if (index < HandNames.size()) {
        return HandNames[index];
    }
    return "Unknown";
}

void JankenGame::play() {
    // コンストラクタで名前を設定するため、inputName()はコメントアウト（必要なら外してください）
    // player.inputName(); 

    cout << "Welcome, " << player.getName() << "! Let's start Janken!\n";
    cout << "First to 3 wins is the victor.\n";
    cout << "-----------------------------------------\n";

    while (score[static_cast<int>(Result::Win)] < 3 && score[static_cast<int>(Result::Lose)] < 3) {
        cout << "\n[Round " << round << "]\n";

        // 【変更】各自のクラス内で手を決定・保持させる
        player.chooseHand();
        cpu.chooseHand();

        // 【変更】ゲッター経由で保持された手を取得する
        Hand playerHand = player.getHand();
        Hand cpuHand = cpu.getHand();

        cout << player.getName() << ": " << getHandName(playerHand) << "\n";
        cout << "CPU: " << getHandName(cpuHand) << "\n";

        Result gameResult = judge(playerHand, cpuHand);

        if (gameResult == Result::Win) {
            cout << "Result: You WIN this round!\n";
            score[static_cast<int>(Result::Win)]++;
            round++;
        }
        else if (gameResult == Result::Lose) {
            cout << "Result: You LOSE this round!\n";
            score[static_cast<int>(Result::Lose)]++;
            round++;
        }
        else {
            cout << "Result: DRAW!\n";
            score[static_cast<int>(Result::Draw)]++;
        }

        cout << "Current Score -> Wins: " << score[static_cast<int>(Result::Win)]
            << ", Losses: " << score[static_cast<int>(Result::Lose)]
            << ", Draws: " << score[static_cast<int>(Result::Draw)] << "\n";
        cout << "-----------------------------------------\n";
    }

    cout << "\n=========================================\n";
    cout << "GAME OVER\n";
    cout << "=========================================\n";

    if (score[static_cast<int>(Result::Win)] == 3) {
        cout << "Congratulations, " << player.getName() << "! You won the game!\n";
    }
    else {
        cout << "Too bad, " << player.getName() << "! CPU won the game!\n";
    }

    cout << "Final Record: " << score[static_cast<int>(Result::Win)] << " Win(s), "
        << score[static_cast<int>(Result::Lose)] << " Loss(es), "
        << score[static_cast<int>(Result::Draw)] << " Draw(s)\n";
    cout << "=========================================\n";
}