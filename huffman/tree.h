#ifndef tree_h
#define tree_h

#include <stdio.h>

typedef struct node
{
    void *item;
    int frequency;
    struct node *left;
    struct node *right;
} node;

node *create_node();

node *create_tree(void *item, node *left, node *right);

void print_tree(node *tree);

void save_tree(node *tree, FILE *compacted_file);

void get_tree_size(node *tree, int *size);

int *allocate_counter();

#endif