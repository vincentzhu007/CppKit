#define _GNU_SOURCE

#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void *thread_func(void *arg) {
  printf("Thread is running...\n");

  sleep(30);

  printf("Thread is exiting...\n");
  return NULL;
}

int main() {
  pthread_t thread;
  pthread_create(&thread, NULL, thread_func, NULL);

  int ret = pthread_setname_np(thread, "OS_MyThread123");
  if (ret != 0) {
    printf("failed to call pthread_setname_np, error:%s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }
  printf("call pthread_setname_np ok\n");

  char name[128];
  ret = pthread_getname_np(thread, name, 128);
  if (ret != 0) {
    printf("failed to call pthread_getname_np, error:%s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }
  printf("call pthread_getname_np ok, new thread name: %s\n", name);

  pthread_join(thread, NULL);
  return 0;
}