#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
  char name[100];
  int random;
  int i;

  srand(time(0));
  printf("Enter your name:\n");
  scanf("%99s", name);
  random = (rand() % 10) + 1;
  for (i = 0; i < random; i++) {
    if (random % 2 == 0) {
      printf("%d hello, %s!\n", random, name);
    } else {
      printf("%d hi there, %s!\n", random, name);
    }
  }
  return 0;
}
