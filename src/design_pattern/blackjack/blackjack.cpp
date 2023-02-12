//
// Created by zgd on 2023/1/27.
// 21点扑克牌
//

#include <iostream>
#include <string>
#include <list>
#include <vector>

using namespace std;

enum Suit {
  kSpade = 0, // 黑桃
  kHeart = 1, // 红心
  kClub = 2, // 梅花
  kDiamond = 3, // 方块
};

class Card {
 public:
  Card() = default;
  Card(int number): number_(number) {}
  int number() const { return number_; }
  string ToString() const { // 打印牌内容 花色 + 数字
    return std::to_string(number_);
  }

 private:
  int number_ = 0;
  char suite_; // 牌的花色
};

// 一次牌局
class Session {
 public:
  Card Draw() { // 发牌
    int n = rand();
    return Card(n % 9 + 1); // [1, 10]
  }

  void Sort() { // 重新洗牌

  }
};

int main() {
  int max_score = 0;
  char choice = 'n';
  Session session;
  vector<Card> hand_cards = {};
  while (1) {
    cout << "牌局开始" << endl;
    int score = 0;
    while (1) {
      Card card = session.Draw(); // 发牌
      cout << "当前发牌：" << card.ToString() << endl;
      hand_cards.push_back(card);
      cout << "当前手牌：[";
      for (auto iter = hand_cards.begin(); iter != hand_cards.end(); iter++) {
        cout << iter->ToString();
        if (iter != hand_cards.end() - 1) {
          cout << ", ";
        }
      }
      cout << "]" << endl;

      score += card.number();
      if (score > 21) {
        score = 0;
        break;
      }
      cout << "继续发牌？(y/n) ";
      cin >> choice;
      if (choice != 'y') {
        break;
      }
    }
    cout << "牌局结束，得分为" << score << endl;

    max_score = std::max(max_score, score);
    cout << "还要再玩一次吗？" << endl;
    cin >> choice;
    if (choice != 'y') {
      break;
    }
    session.Sort();
    hand_cards = {};
  }
  cout << "最高得分：" << max_score << endl;
  cout << "游戏退出" << endl;
}
