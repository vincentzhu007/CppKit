#include <atomic>
#include <iostream>

using namespace std;

int main() {
  atomic_bool a_bool(true);

  atomic_int a_int(100);

  atomic_flag a_flag = ATOMIC_FLAG_INIT;
  a_flag.clear();

  std::cout << "atomic bool, lock free: " << a_bool.is_lock_free() << std::endl;
  std::cout << "atomic int, lock free: " << a_int.is_lock_free() << std::endl;
  std::cout << "atomic flag, value: " << a_flag.test_and_set() << std::endl;
}