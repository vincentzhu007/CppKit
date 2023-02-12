/**
 * 观察者模式：加热器例子
 * 最基础的实现逻辑：当热水器加热超过60度时，显示可以洗澡；当超过95度时，显示热水可饮用。
 *
 * Created by zgd on 2023/2/12.
 */

#include <iostream>
#include <sstream>

constexpr float kLowestTemperatureForShower = 60.0f;
constexpr float kLowestTemperatureForDrink= 95.0f;

class WaterHeater {
 public:
  WaterHeater() = default;
  WaterHeater(float initial_temperature) : temperature_(initial_temperature) {}

  void HeatTo(float new_temperature) {
    temperature_ = new_temperature;

    std::stringstream message;
    message << "Water temperature has reached to " << temperature_ << "°C by heating.";

    if (temperature_ >= kLowestTemperatureForDrink) {
      message << " You can have a drink.";
      std::cout << message.str() << std::endl;
      return;
    }
    if (temperature_ >= kLowestTemperatureForShower) {
      message << " You can task a shower.";
      std::cout << message.str() << std::endl;
      return;
    }
    std::cout << message.str() << std::endl;
  }

 private:
  float temperature_ = 0.0f;
};

int main() {
  WaterHeater water_heater;
  water_heater.HeatTo(20);
  water_heater.HeatTo(65);
  water_heater.HeatTo(98);
}



