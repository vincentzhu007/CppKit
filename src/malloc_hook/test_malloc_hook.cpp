//
// Created by zgd on 2023/2/25.
//
#include <iostream>
#include <malloc.h>

static void my_init_hook();
static void *my_malloc_hook(size_t n, const void *caller);
static void my_free_hook(void *ptr, const void *caller);

void my_init_hook() {
  old_malloc_hook = __malloc_hook;
  old_free_hook = __free_hook;
  __malloc_hook = my_malloc_hook;
  __malloc_free = my_free_hook;
}

void *my_malloc_hook(size_t n, const void *caller) {
  __malloc_hook = old_malloc_hook;
  __free_hook = old_free_hook;

  void *result = malloc(n);

  old_malloc_hook = __malloc_hook;
  old_free_hook = __free_hook;

  printf("malloc (%u) returns %p\n",  n, result);

  __malloc_hook = my_malloc_hook;
  __malloc_free = my_free_hook;
  return result;
}

void my_free_hook(void *ptr, const void *caller) {
  __malloc_hook = old_malloc_hook;
  __free_hook = old_free_hook;

  free(ptr);

  old_malloc_hook = __malloc_hook;
  old_free_hook = __free_hook;

  printf("free pointer: %p\n",  ptr);

  __malloc_hook = my_malloc_hook;
  __malloc_free = my_free_hook;
}

int main() {
  my_init_hook();

  int *p = new int[10];
  char *c = new char[100];

  delete[] p;
  delete[] c;
  return 0;
}