//
// Created by zgd on 2022/8/5.
//

#include "money.h"

namespace cppkit {
MoneyPtr Money::Dollar(int amount) {
  return MoneyPtr(new Money(amount, "USD"));
}

MoneyPtr Money::Franc(int amount) {
  return MoneyPtr(new Money(amount, "CHF"));
}
} // cppkit