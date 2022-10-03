#include <stdio.h>

int main(void) {
  char name[100];

  printf("Enter your name:\n");
  scanf("%99s", name);
  printf("hello, %s!\n", name);
  return 0;
}
