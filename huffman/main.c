#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "compactor.h"
#include "tree.h"
#include "heap.h"



int main()
{
    printf("bom dia\n");
    node* tree = make_tree();
    printf("na main.c\n");
    printf("(");
    print_tree(tree);
    printf(")\n");
}