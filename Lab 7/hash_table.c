/*
 * CS 11, C Track, lab 7
 *
 * FILE: hash_table.c
 *     Implementation of the hash table functionality.
 *
 */

/*
 * Include the declaration of the hash table data structures
 * and the function prototypes.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"
#include "memcheck.h"


/*** Hash function. ***/

int hash(char *s) {
  int i, sum = 0;

  /* Loop through the string */
  for (i = 0; i < strlen(s); i++) {
    /* Add the character to the sum */
    sum += s[i];
  }
  /* return the sum */
  return sum % NSLOTS;
}


/*** Linked list utilities. ***/

/* Create a single node. */
node *create_node(char *key, int value) {
  /* Malloc space for a new node */
  node *new_node = malloc(sizeof(node));
  /* Check that memory was allocated */
  if (new_node == NULL) {
      fprintf(stderr, "Fatal error: out of memory. "
              "Terminating program.\n");
      exit(1);
  }
  /* Set the key and value, and initialize next to NULL */
  new_node->key = key;
  new_node->value = value;
  new_node->next = NULL;
  return new_node;
}


/* Free all the nodes of a linked list. */
void free_list(node *list) {
  node *curr;
  /* Loop through all the nodes in the list */
  while (list != NULL) {
    /* Set the current node to the head of the list */
    curr = list;
    /* Set the head of the list to the next node in the list */
    list = list->next;
    /* Free the current node and it's key */
    free(curr->key);
    free(curr);
  }
}


/*** Hash table utilities. ***/

/* Create a new hash table. */
hash_table *create_hash_table() {
  node **slot;

  /* Malloc space for a hash table */
  hash_table *ht = malloc(sizeof(hash_table));
  /* Check that memory was allocated */
  if (ht == NULL) {
      fprintf(stderr, "Fatal error: out of memory. "
              "Terminating program.\n");
      exit(1);
  }
  /* Malloc space for a NSLOTS length list of node pointers */
  slot = calloc(NSLOTS, sizeof(node *));
  /* Check that memory was allocated */
  if (slot == NULL) {
      fprintf(stderr, "Fatal error: out of memory. "
              "Terminating program.\n");
      exit(1);
  }
  /* Set the hash table's slot */
  ht->slot = slot;
  return ht;
}


/* Free a hash table. */
void free_hash_table(hash_table *ht) {
  int i;

  /* Loop through all the linked lists in the hash table's slot */
  for (i = 0; i < NSLOTS; i++) {
    /* Free each linked list */
    free_list(ht->slot[i]);
  }
  /* Free the slot and the hash table */
  free(ht->slot);
  free(ht);
}


/*
 * Look for a key in the hash table.  Return 0 if not found.
 * If it is found return the associated value.
 */
int get_value(hash_table *ht, char *key) {
  int key_hash;
  node *curr;

  /* Computes the hash of the key */
  key_hash = hash(key);
  /* Loop through all the nodes in the slot at the hash */
  for (curr = ht->slot[key_hash]; curr != NULL; curr = curr->next) {
    /* If the node has the same key, return the node's value */
    if (strcmp(curr->key, key) == 0) {
      return curr->value;
    }
  }
  /* If the key isn't found, return 0 */
  return 0;
}


/*
 * Set the value stored at a key.  If the key is not in the table,
 * create a new node and set the value to 'value'.  Note that this
 * function alters the hash table that was passed to it.
 */
void set_value(hash_table *ht, char *key, int value) {
  int key_hash;
  node *curr;

  /* Computes the hash of the key */
  key_hash = hash(key);
  /* Loop through all the nodes in the slot at the hash */
  for (curr = ht->slot[key_hash]; curr != NULL; curr = curr->next) {
    /* If the node has the same key, set the node's value to the new value */
    if (strcmp(curr->key, key) == 0) {
      curr->value = value;
      /* If the key isn't put into the hash table, free it */
      free(key);
      /* Return out of the function */
      return;
    }
  }
  /* Make a new node and put it at the head of the list */
  curr = create_node(key, value);
  curr->next = ht->slot[key_hash];
  ht->slot[key_hash] = curr;
}


/* Print out the contents of the hash table as key/value pairs. */
void print_hash_table(hash_table *ht) {
  int i;
  node *curr;

  /* Loop through all the slots in the hash table */
  for (i = 0; i < NSLOTS; i++) {
    /* Loop through all the nodes in the list at the slot */
    for (curr = ht->slot[i]; curr != NULL; curr = curr->next) {
      /* Print the key value pair */
      printf("%s %d\n", curr->key, curr->value);
    }
  }
}
