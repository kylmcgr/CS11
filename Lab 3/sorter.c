/*
 * sorter.c: sorts the number inputed at the command line
 * usage: ./easter [-b] [-q] number1 [number2 ... ]
 * -b: optional argument to sort using a bubble sort
 * -q: optional argument to suppress output
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_NUMBERS 32

void min_sort(int array[], int num_elements);
void bubble_sort(int array[], int num_elements);

int main(int argc, char *argv[]) {
  int i, array[MAX_NUMBERS];
  int num_elements = 0;
  int bubble = 0;
  int suppress = 0;

  char[] usage = "usage: %s [-b] [-q] number1 [number2 ... ]"
                    "(maximum 32 numbers)\n";
  /* Loop through command line arguments */
  for (i = 1; i < argc; i++) {
    /* Check for optional arguments */
    if (strcmp(argv[i], "-b") == 0) {
      bubble = 1;
    } else if (strcmp(argv[i], "-q") == 0) {
      suppress = 1;
    } else {
      /* Check for too many inputs */
      if (num_elements >= MAX_NUMBERS) {
        fprintf(stderr, usage, argv[0]);
        exit(1);
      }
      /* Add the new number to the array */
      array[num_elements] = atoi(argv[i]);
      num_elements++;
    }
  }

  /* Check for too few inputs */
  if (num_elements == 0) {
    fprintf(stderr, usage, argv[0]);
    exit(1);
  }

  /* Sort the array depending on the input */
  if (bubble == 0) {
    min_sort(array, num_elements);
  } else {
    bubble_sort(array, num_elements);
  }

  /* Print the array depending on the input */
  if (suppress == 0) {
    for (i = 0; i < num_elements; i++) {
      fprintf(stderr, "%d\n", array[i]);
    }
  }
  return 0;
}

/*
 * min_sort: sorts an array of num_elements size using a min element sort
 * arguments: array of elements to sort and number of elements to be sorted
 */
void min_sort(int array[], int num_elements) {
  int start, smallest, i, temp;

  /* Sort the elemets by repeatedly finding the smallest element */
  /* Loop through all the elements */
  for (start = 0; start < num_elements; start++) {
    smallest = start;
    /* Find the smallest element left in the array */
    for (i = start; i < num_elements; i++) {
      if (array[i] < array[smallest]) {
        smallest = i;
      }
    }
    /* Swap the current element with the smallest */
    temp = array[start];
    array[start] = array[smallest];
    array[smallest] = temp;
  }

  /* Check that the array is sorted */
  for (i = 1; i < num_elements; i++) {
    assert(array[i] >= array[i - 1]);
  }
}

/*
 * bubble_sort: sorts an array of num_elements size using a bubble sort
 * arguments: array of elements to sort and number of elements to be sorted
 */
void bubble_sort(int array[], int num_elements) {
  int swap, i, temp;
  int end = num_elements;

  /* Sorts the elemets by "bubbling" the largest element to the top */
  /* While there are still elements to be sorted, do the sort */
  while (end > 1) {
    swap = 0;
    /* Go through the unsorted part of the array */
    for (i = 1; i < end; i++) {
      /* If the current element smaller than the previous, swap them */
      if (array[i - 1] > array[i]) {
        temp = array[i - 1];
        array[i - 1] = array[i];
        array[i] = temp;
        swap = i;
      }
    }
    /* Set the end of the unsorted region */
    end = swap;
  }

  /* Check that the array is sorted */
  for (i = 1; i < num_elements; i++) {
    assert(array[i] >= array[i - 1]);
  }
}
