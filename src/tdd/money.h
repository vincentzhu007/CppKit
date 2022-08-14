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

class Money {
 public:
  Money(int amount, const std::string &currency)
    : amount_(amount), currency_(currency) {}
  virtual ~Money() {}
  virtual MoneyPtr Times(int multiplier) const = 0;
  virtual bool Equals(const MoneyPtr &obj) const = 0;
  std::string Currency() const {
    return currency_;
  }
  static MoneyPtr NewDollar(int amount);
  static MoneyPtr NewFranc(int amount);

 protected:
  const int amount_ = 0;
  const std::string currency_ = "";
};

class Dollar : public Money {
 public:
  Dollar(int amount, const std::string &curr) : Money(amount, curr) {}
  MoneyPtr Times(int multiplier) const override {
    return Money::NewDollar(amount_ * multiplier);
  }
  bool Equals(const MoneyPtr &obj) const override {
    return (typeid(*obj) == typeid(*this)) &&
      (this->amount_ == static_cast<const Dollar *>(obj.get())->amount_);
  }
};

class Franc : public Money {
 public:
  Franc(int amount, const std::string &curr) : Money(amount, curr) {}
  MoneyPtr Times(int multiplier) const override {
    return Money::NewFranc(amount_ * multiplier);
  }

  bool Equals(const MoneyPtr &obj) const override {
    return (typeid(*obj) == typeid(*this)) &&
        (this->amount_ == static_cast<const Franc *>(obj.get())->amount_);
  }
};
} // cppkit

#endif //CPPKIT_SRC_TDD_MONEY_H_
