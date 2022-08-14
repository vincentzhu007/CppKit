//
// Created by zgd on 2022/8/5.
//

#include "money.h"

namespace cppkit {
MoneyPtr Money::NewDollar(int amount) {
  return MoneyPtr(new Dollar(amount, "USD"));
}

MoneyPtr Money::NewFranc(int amount) {
  return MoneyPtr(new Franc(amount, "CHF"));
}
} // cppkit