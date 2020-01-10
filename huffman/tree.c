#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "tree.h"

node *create_node()
{
    node *new_node = (node *)malloc(sizeof(node));
    new_node->item = (void *)malloc(2 * sizeof(unsigned char));
    *(unsigned char*)new_node->item = '*';
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
        if (*(unsigned char *)tree->item == '\\')
        {
            printf("%c%c(", *(unsigned char *)tree->item , * ((unsigned char *)tree->item + 1));
            print_tree(tree->left);
            printf(")(");
            print_tree(tree->right);
            printf(")");
        }
        else
        {
            printf("%c(", *(unsigned char *)tree->item);
            print_tree(tree->left);
            printf(")(");
            print_tree(tree->right);
            printf(")");
        }
    }
}

void save_tree(node *tree, FILE *compacted_file)
{
    if (tree != NULL)
    {
        fprintf(compacted_file, "%c", *(unsigned char *)tree->item);
        if (*(unsigned char *)tree->item == '\\') fprintf(compacted_file, "%c", *((unsigned char *)tree->item + 1));
        save_tree(tree->left, compacted_file);
        save_tree(tree->right, compacted_file);
    }
}

void get_tree_size(node *tree, int *size)
{
    if (tree != NULL)
    {
        *size+= 1;
        if (*(unsigned char *)tree->item == '\\') *size+= 1;
        if (*(unsigned char *)tree->item == '*')
        {
            get_tree_size(tree->left, size);
            get_tree_size(tree->right, size);
        }
    }
}

int *allocate_counter()
{
    int *cont = (int *)malloc(sizeof(int));
    *cont = 0;
    return cont;
}