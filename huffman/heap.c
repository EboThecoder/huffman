#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "heap.h"


heap *create_heap()
{
    heap *new_heap = (heap *)malloc(sizeof(heap));
    new_heap->size = 0;
    for (int i = 1; i < MAX; i++)
    {
        new_heap->nodes[i] = create_node();
    }
    return new_heap;
}

unsigned get_parent_index(heap *heap, unsigned i)
{
    return i / 2;
}
unsigned get_left_index(heap *heap, unsigned i)
{
    return 2 * i;
}
unsigned get_right_index(heap *heap, unsigned i)
{
    return 2 * i + 1;
}

void swap(void *u, void *v, size_t len)
{
    unsigned char *p = u, *q = v, aux;
    for (size_t i = 0; i < len; i++)
    {
        // printf("%hhu ", q[i]);
        aux = p[i];
        p[i] = q[i];
        q[i] = aux;
    }
}

void print_heap(heap *heap)
{
    unsigned i;
    printf("\nheap size: %d\n", heap->size);
    for (i = 1; i <= heap->size; i++)
    {
        if (i == heap->size)
            printf("%c %d\n", *(unsigned char *)heap->nodes[i]->item, heap->nodes[i]->frequency);
        else
            printf("%c %d| ", *(unsigned char *)heap->nodes[i]->item, heap->nodes[i]->frequency);
    }
    printf("\n");
}

void min_heapify(heap *heap, unsigned i)
{
    unsigned smaller_index;
    unsigned left_index = get_left_index(heap, i);
    unsigned right_index = get_right_index(heap, i);
    if (left_index <= heap->size && heap->nodes[left_index]->frequency < heap->nodes[i]->frequency)
    {
        smaller_index = left_index;
    }
    else
    {
        smaller_index = i;
    }
    if (right_index <= heap->size && heap->nodes[right_index]->frequency < heap->nodes[smaller_index]->frequency)
    {
        smaller_index = right_index;
    }
    if (i != smaller_index)
    {
        // printf("antes do swap - NODES[i]: %c NODES[smaller_index]: %c\n", *(char *)heap->nodes[i]->item, *(char *)heap->nodes[smaller_index]->item);
        swap(heap->nodes[i], heap->nodes[smaller_index], sizeof(node));
        //  printf("depois do swap - NODES[i]: %c NODES[smaller_index]: %c\n", *(char *)heap->nodes[i]->item, *(char *)heap->nodes[smaller_index]->item);
        min_heapify(heap, smaller_index);
    }
}

int is_in_heap(heap *heap, void *item)
{
    unsigned i;
    if (*(char *)item == '*')
        return 0;
    for (i = 1; i <= heap->size; i++)
    {
        if (*(unsigned char *)heap->nodes[i]->item == *(unsigned char *)item)
            return i;
    }
    return 0;
}

void enqueue(heap *heap, node *new_node)
{
    int i;
    i = is_in_heap(heap, new_node->item);
    if (heap->size >= MAX)
    {
        //printf("Heap overflow");
    }
    else if (i)
    {
        heap->nodes[i]->frequency++;
        min_heapify(heap, i);
    }
    else
    {
        heap->size++;
        heap->nodes[heap->size] = new_node;
        unsigned key_index = heap->size;
        unsigned parent_index = get_parent_index(heap, heap->size);
        while (parent_index >= 1 && heap->nodes[key_index]->frequency < heap->nodes[parent_index]->frequency)
        {
            swap(heap->nodes[key_index], heap->nodes[parent_index], sizeof(node));
            key_index = parent_index;
            parent_index = get_parent_index(heap, key_index);
        }
    }
    //print_estado_atual(heap);
}

node *dequeue(heap *heap)
{
    if (heap->size == 0)
    {
        //printf("Heap underflow");
        return NULL;
    }
    else
    {

        node *dequeued = heap->nodes[1];
        heap->nodes[1] = heap->nodes[heap->size];
        heap->size--;
        min_heapify(heap, 1);
        return dequeued;
    }
}