#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "tree.h"

node *create_node()
{
    node *new_node = (node *)malloc(sizeof(node));

    new_node->frequency = 1;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

node *create_tree(void *item, node *left, node *right)
{
    node *new_tree = (node *)malloc(sizeof(node));
    new_tree->item = item;
    new_tree->left = left;
    new_tree->right = right;
    return new_tree;
}

void print_tree(node *tree)
{
    if (tree != NULL)
    {
        printf("%c(", *(char *)tree->item);
        print_tree(tree->left);
        printf(")(");
        print_tree(tree->right);
        printf(")");
    }
}