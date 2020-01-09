#ifndef compactor_h
#define compactor_h

#include "heap.h"
#include "tree.h"

void get_trash_size(hash *map, int *trash_size, int *string_size);

void print_tree_in_file(node *tree, FILE *compacted_file);

unsigned char set_bit(unsigned char c, int i);

int is_bit_i_set(unsigned char c, int i);

int *allocate_counter();

void save_first_2_bytes(int *trash_size, int *tree_size, FILE *compacted_file);

void save_file(hash *map, FILE *compacted_file);

node *build_tree();

void compact();

#endif