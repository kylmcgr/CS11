/*
 * lab5_array.c: simulates cellular automata using array indicies
 * usage: ./easter population generations
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "memcheck.h"

int *update(int *population, int size);
void print(int *population, int size);

int main(int argc, char const *argv[]) {
  int *population;
  int generations, size, i;

  srand(time(0));
  if (argc != 3) {
    fprintf(stderr, "usage: %s population generations \n", argv[0]);
    exit(1);
  }
  /* Save command line arguments */
  size = atoi(argv[1]);
  generations = atoi(argv[2]);
  /* Allocate the population */
  population = (int *) calloc(size, sizeof(int));
  /* Check that the calloc call succeeded. */
  if (population == NULL) {
      fprintf(stderr, "Error! Memory allocation failed!\n");
      exit(1);
  }
  /* Initialize the population randomly to 0 or 1 */
  for (i = 1; i < size - 1; i++) {
    population[i] = rand() % 2;
  }
  /* Initialize the two endpoints to 0 */
  population[0] = 0;
  population[size - 1] = 0;
  /* Print the initial population */
  print(population, size);
  /* Iterate through each generation */
  for (i = 0; i < generations; i++) {
    /* Apply the update rule and set the population to the new population */
    population = update(population, size);
    /* Print the new population */
    print(population, size);
  }
  free(population);
  print_memory_leaks();
  return 0;
}

/*
 * Updates the current population using the update rule:
 * Sets cell to full if the cell is empty and one of its neighbors is full.
 * Otherwise sets the cell to empty.
 */
int *update(int *population, int size) {
  int *new_pop;
  int i;

  /* Allocate the new population */
  new_pop = (int *) calloc(size, sizeof(int));
  /* Iterate through the population */
  for (i = 1; i < size - 1; i++) {
    /* Check if the cell should be full or empty */
    if (population[i] == 0 && population[i - 1] != population[i + 1]) {
      new_pop[i] = 1;
    } else {
      new_pop[i] = 0;
    }
  }
  /* Evaluate the edge cases */
  new_pop[0] = 0;
  new_pop[size - 1] = 0;
  /* Free the old population, so we do not leak memory */
  free(population);
  /* Return the new population */
  return new_pop;
}

/*
 * Prints the current population.
 */
void print(int *population, int size) {
  int i;
  /* Iterate through the population */
  for (i = 0; i < size; i++) {
    /* Print . or * depending on the cell state */
    if (population[i] == 0) {
      printf(".");
    } else {
      printf("*");
    }
  }
  printf("\n");
}
