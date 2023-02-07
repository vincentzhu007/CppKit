//
// Created by zgd on 2022/10/22.
//
#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/wait.h>
#include <thread>
#include <functional>

using namespace std;

void Fork()
{
  pid_t pid = fork();
  if (pid < 0) {
    cerr << "fork errno: " << errno << endl;
    return;
  }

  if (pid == 0) { // child process
//    system("ls /proc/self/task");
    cout << "[ child -" << getpid() << " ] exited" << endl;
    exit(10); // terminated here in child process
  }

  cout << "[ parent-" << getpid() << " ] forked child " << pid << endl;
  int status;
  pid_t pidRet = waitpid(pid, &status, 0);
  if (pidRet == -1) {
    cerr << "wait child " << pid << " errno: " << errno << endl;
    return;
  }
  if (WIFEXITED(status)) { // child normal existed
    cout << "[ parent-" << getpid() << " ] wait child " << pid << " done, child exited with ret code: " << WEXITSTATUS(status) << endl;
  } else if (WIFSIGNALED(status)) { // child terminated by signal
    cout << "[ parent-" << getpid() << " ] wait child " << pid << " done, child terminated by signal: " << WTERMSIG(status) << endl;
  } else {
    cerr << "[ parent-" << getpid() << " ] unknown type exit of child" << endl;
  }
}

class TaskThread {
 public:
  void Run() {
    cout << "construct TaskThread..." << endl;
    th_ = std::thread(std::bind(&TaskThread::RunImpl, this));
  }
  ~TaskThread() {
    cout << "destruct TaskThread..." << endl;
    if (th_.joinable()) {
      th_.join();
      cout << "thread id joined" << endl;
    }
  }
  void RunImpl() {
    sleep(3);
    cout << "run task in thread..." << endl;
  }
 private:
  std::thread th_;
};

TaskThread g_taskThread;
int main(int argc, char *argv[])
{
  g_taskThread.Run();
  Fork();
  return 0;
}
