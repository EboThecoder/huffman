#ifndef tree_h
#define tree_h

typedef struct node
{
    void *item;
    unsigned frequency;
    struct node *left;
    struct node *right;
} node;

node *create_node();

node *create_tree(void *item, node *left, node *right);

void print_tree(node *tree);

#endif