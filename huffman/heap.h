#ifndef heap_h
#define heap_h

#include "tree.h"

#include <stdlib.h>
#include <limits.h>


typedef struct heap
{
    int size; 
    node *nodes[256];
} heap;

heap *create_heap();

int get_parent_index(heap *heap, int i);

int get_left_index(heap *heap, int i);

int get_right_index(heap *heap, int i);

void swap(void *u, void *v, size_t len);

void print_heap(heap *heap);
 
void min_heapify(heap *heap, int i);

int is_in_heap(heap *heap, void *item);

void enqueue(heap *heap, node *new_node);

node *dequeue(heap *heap);

#endif