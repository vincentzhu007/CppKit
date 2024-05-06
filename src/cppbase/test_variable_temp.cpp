/**
 * 测试可变模板参数函数
 */

#include <iostream>

using namespace std;

template <class... T>
void f(T... args) {
  cout << sizeof...(args) << endl;  // 获取可变参数个数
}

// 通过递归函数展开
void print() { cout << "empty" << endl; }

template <class T, class... Args>
void print(T head, Args... rest) {
  cout << "parameter " << head << endl;
  print(rest...);
}

template <class T>
T sum(T first) {
  return first;
}

template <class T, class... Args>
T sum(T first, Args... rest) {
  return first + sum(rest...);
}

// 通过逗号表达式展开

int main() {
  f();
  f(1.0);
  f(1.0, 3);
  f(1.0, 3, "hello");

  print(1, 2, 3, 4);

  cout << sum(1) << endl;
  cout << sum(1, 2) << endl;
  cout << sum(1, 2, 3) << endl;
  cout << sum(1, 2, 3, 4) << endl;
}
