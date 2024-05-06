#include <pthread.h>

#include <iostream>
#include <thread>

int main() {
  std::thread t([]() {
    std::string name = "OS_MyThread";

    // 设置的线程名字不能超过15个字符。
    pthread_setname_np(pthread_self(), name.substr(0, 15).c_str());

    char new_name[128];
    pthread_getname_np(pthread_self(), new_name, 128);

    std::cout << "new thread name: " << new_name << std::endl;
    // other works
  });

  t.join();

  return 0;
}