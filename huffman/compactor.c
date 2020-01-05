#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "compactor.h"
#include "tree.h"
#include "heap.h"

node *make_tree()
{
    heap *heap = create_heap();
    unsigned char a[1000];
    node *nodes[1000];
    int i = 0;
    FILE* file_to_compact = fopen("file_to_compact.txt", "r");
    while (fscanf(file_to_compact, "%c", &a[i]) != EOF)
    {
        nodes[i] = create_node();
        nodes[i]->item = &a[i];
        enqueue(heap, nodes[i]);
        i++;
    }
    fclose(file_to_compact);
    print_heap(heap);

    node *left, *right, *parent;
    while (heap->size != 1)
    {
        printf("estado da heap:\n");
        print_heap(heap);
        printf("\n");
        left = dequeue(heap);
        right = dequeue(heap);
        parent = create_node();
        unsigned char ast = '*';
        parent->item = &ast;
        parent->frequency = left->frequency + right->frequency;
        parent->left = left;
        parent->right = right;

        enqueue(heap, parent);
    }
    printf("no compactor.c:\n");
    printf("(");
    print_tree(heap->nodes[1]);
    printf(")\n");
    return heap->nodes[1];
}