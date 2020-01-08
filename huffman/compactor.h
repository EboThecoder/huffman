#ifndef compactor_h
#define compactor_h

#include "heap.h"
#include "tree.h"

node *make_tree();

void print_tree_in_file(node *tree, FILE *compacted_file);

unsigned char set_bit(unsigned char c, int i);

void zero_string(unsigned char *str, int size);

void first_2_bytes(int *trash_size, int *tree_size, FILE *compacted_file);

void save_file(hash *map, int string_size, unsigned char *str, FILE *compacted_file);

void compact();

#endif