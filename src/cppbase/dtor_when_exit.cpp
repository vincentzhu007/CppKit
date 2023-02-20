//
// 编写demo观察调用exit时对象析构的特点
//
// Created by Vincent Zhu on 2023/2/21.
//

#include <iostream>

using namespace std;

class Foo {
 public:
  Foo(const std::string &desc) : desc_(desc) {
    cout << "call Foo ctor of " << desc_ << endl;
  }
  ~Foo() {
    cout << "call Foo dtor of " << desc_ << endl;
  }
 private:
  std::string desc_;
};

class Bar {
 private:
  static Foo foo_;
};

Foo Bar::foo_("static in class");

static Foo foo01("static");
Foo foo02("global");

int main() {
  Foo foo03("local");
  static Foo foo04("local static");
  cout << endl;
  exit(0);
}

