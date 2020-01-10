#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "tree.h"

node* read_tree(FILE *file)
{
    node* tree;
    unsigned char ch;
    fscanf(file, "%c", &ch);
    void *item = (void *)malloc(2 * sizeof(unsigned char));
    *(unsigned char*)item = ch;
    if (ch == '\\')
    {
        fscanf(file, "%c", &ch);
        *((unsigned char*)item + 1) = ch;
    }
    if (ch == '*')
    {
        node *left = read_tree(file);
        node *right = read_tree(file);
        tree = create_tree(item, left, right);
    }
    else
    {
        tree = create_tree(item, NULL, NULL);
    }
    return tree;
}

int main()
{
    FILE *file = fopen("compacted_file", "r");
    node *tree = read_tree(file);
    print_tree(tree);
    fclose(file);
}