/**
 * 观察者模式：加热器例子
 *
 * 当热水器加热超过60度时，显示可以洗澡；当超过95度时，显示热水可饮用。
 * 这里加热的行为和洗澡、喝水的行为是可以解耦到不同的类的。
 * 1. 为什么要解耦，什么需求驱动我们去做解耦？
 *    考虑再加一项，超过40度可以洗车，那就需要修改原本热水器的代码，不符合开闭原则。我们希望的是，每增加一个温度观察项，只需要调用一个接口，去
 *    声明一下它对温度的观察关系，然后它就直接加入到现有的加热器系统中，当温度发生变化时，触发它检查是否满足条件，打印提示。反过来，不希望看到
 *    的是，每增加一个观察项，就修改加热器对象代码逻辑，支持这条新加入的项，这样显然会导致加热器代码被不断修改，而且是和自己关系不大的原因的触
 *    发的。加热器对象的核心定位是：通过加热动作来改变加热温度。其它周边逻辑最好不要影响它的代码。这里也体现了单一原则（有且只有一个被修改的原
 *    因）。
 *
 * 2. 怎么解耦？
 *    解耦是通过分离概念（对象），来把功能需求的变更点调整到对象的交互边界位置。当需求发生变化时，就可以像重新拼积木一样，只对现有的对象进行拼
 *    接来完成需求，来达到最低成本的目标。针对热水器的例子，"新增超过40度可以洗车"的新观察需求，显示出：每一个观察项就是一个关键变更点，那我们
 *    试着把所有观察逻辑从加热器中分离出去，作为独立的概念（对象）来思考。
 *    把判断是否到达不同项目温度边界值的的逻辑放到各自的项目中，这样可以拆分出
 *
 * Created by zgd on 2023/2/12.
 */

#include <iostream>
#include <sstream>

constexpr float kLowestTemperatureForWashingCar = 40.0f;
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



