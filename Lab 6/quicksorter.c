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
#include "linked_list.h"
#include "memcheck.h"

node * quick_sort(node *list);

int main(int argc, char *argv[]) {
  int i, suppress = 0;
  node *sorted_list, *list = NULL;

  /* Loop through command line arguments */
  for (i = 1; i < argc; i++) {
    /* Check for optional arguments */
    if (strcmp(argv[i], "-q") == 0) {
      suppress = 1;
    } else {
      /* Add the new number to the list */
      list = create_node(atoi(argv[i]), list);
    }
  }

  /* Check for too few inputs */
  if (list == NULL) {
    fprintf(stderr, "usage: %s [-q] number1 [number2 ... ]\n", argv[0]);
    exit(1);
  }

  /* Sort the list */
  sorted_list = quick_sort(list);
  free_list(list);
  list = sorted_list;

  /* Print the array depending on the input */
  if (suppress == 0) {
    print_list(list);
  }
  free_list(list);
  print_memory_leaks();
  return 0;
}

/*
 * quick_sort: recursively sorts sublists and appends the sorted lists together
 * arguments: a linked list of numbers to be sorted
 */
node *quick_sort(node *list) {
  node *sorted_list, *n;
  node *lesser_list = NULL, *middle_node, *greater_list = NULL;

  if (list == NULL || list->next == NULL) {
    return copy_list(list);
  }

  /* Get a lone node to seperate the lists by */
  middle_node = copy_list(list);
  free_list(middle_node->next);
  middle_node->next = NULL;
  /* Loop through all the elements */
  for (n = list->next; n != NULL; n = n->next) {
    /* Add the element to the correct sub-list */
    if (n->data < middle_node->data) {
      lesser_list = create_node(n->data, lesser_list);
    } else {
      greater_list = create_node(n->data, greater_list);
    }
  }

  /* Sort the sub-lists */
  sorted_list = quick_sort(lesser_list);
  free_list(lesser_list);
  lesser_list = sorted_list;

  sorted_list = quick_sort(greater_list);
  free_list(greater_list);
  greater_list = sorted_list;

  /* Put the sorted list back together */
  sorted_list = append_lists(middle_node, greater_list);
  free_list(middle_node);
  free_list(greater_list);
  list = sorted_list;
  sorted_list = append_lists(lesser_list, list);
  free_list(lesser_list);
  free_list(list);
  list = sorted_list;

  /* Check that the array is sorted */
  assert(is_sorted(list));
  return list;
}
