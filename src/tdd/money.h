//
// Created by zgd on 2022/8/5.
//

#ifndef CPPKIT_SRC_TDD_MONEY_H_
#define CPPKIT_SRC_TDD_MONEY_H_
#include <iostream>
#include <string>
#include <memory>

namespace cppkit {
class Dollar;
class Franc;
class Money;
using MoneyPtr = std::unique_ptr<Money>;

class Expression {
 public:
  virtual ~Expression() {};
};
using ExpressionPtr = std::unique_ptr<Expression>;

class Money : Expression {
 public:
  Money(int amount, const std::string &currency)
    : amount_(amount), currency_(currency) {}
  virtual ~Money() {}
  MoneyPtr Times(int multiplier) const {
    return MoneyPtr(new Money(amount_ * multiplier, currency_));
  }
  ExpressionPtr Plus(MoneyPtr money) const {
    return ExpressionPtr(new Money(amount_ + money->amount_, currency_));
  }
  bool Equals(const MoneyPtr &obj) const {
    if (obj == nullptr) {
      return false;
    }
    std::cout << "equal() of this: " << ToString() << ", another: "
      << obj->ToString() << std::endl;
    return (amount_ == obj->amount_) && (currency_ == obj->currency_);
  }
  std::string Currency() const { return currency_; }
  std::string ToString() const {
    return std::to_string(amount_) + " " + currency_;
  };
  static MoneyPtr Dollar(int amount);
  static MoneyPtr Franc(int amount);

 protected:
  const int amount_ = 0;
  const std::string currency_ = "";
};

class Bank {
 public:
  MoneyPtr Reduce(const ExpressionPtr &expr, const std::string &currency) {
    Money *money = reinterpret_cast<Money *>(expr.get());
    return MoneyPtr(new Money(*money));
  }
};
} // cppkit
#endif //CPPKIT_SRC_TDD_MONEY_H_
