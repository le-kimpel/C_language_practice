#include <stdio.h>
#include <dlfcn.h>

void fella_func()
{
  printf("I'm just a little guy!\n");
}

__attribute__((constructor))
void message_upon_load()
{
  fella_func();
}
