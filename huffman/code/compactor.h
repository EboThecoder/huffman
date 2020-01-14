#ifndef compactor_h
#define compactor_h

#include "heap.h"
#include "tree.h"

void get_trash_size(hash *map, unsigned short *trash_size);

void print_tree_in_file(node *tree, FILE *compacted_file);

unsigned char set_bit(unsigned char c, int i);

void save_first_2_bytes(unsigned short *trash_size, unsigned short *tree_size, FILE *compacted_file);

void save_file(hash *map, FILE *compacted_file);

node *build_tree();

void compact();

#endif