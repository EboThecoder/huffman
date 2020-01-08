#include "hash.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX_TABLE_SIZE 256
#define MAX_DEPTH 13
#define LEFT_JUMP 0
#define RIGHT_JUMP 1
#define START_JUMP -1

typedef struct hash_node
{
    void* key;
    int depth;
    bool bits[MAX_DEPTH];
} hash_node;

typedef struct hash_table
{
    hash_node *table[MAX_TABLE_SIZE];
    int size;
} hash;

hash *create_hash_table()
{
    hash *new_hash = (hash *)malloc(sizeof(hash));
    int i;
    for (i = 0; i < MAX_TABLE_SIZE; i++)
    {
        new_hash->table[i] = NULL;
    }
    new_hash->size = 0;
    return new_hash;
}

void print_bits(bool *bits, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (bits[i])
            printf("1");
        else
            printf("0");
    }
    printf("\n");
}

void put(hash *hash, void *key, int depth, bool *bits)
{
    if (hash->size >= MAX_TABLE_SIZE)
    {
        //printf("hash table overflow\n");
    }
    else
    {
        int h = *(unsigned char *)key;
        while (hash->table[h] != NULL)
        {
            h = (h + 1) % MAX_TABLE_SIZE;
        }

        hash_node *new_hash_node = (hash_node *)malloc(sizeof(hash_node));
        new_hash_node->key = key;
        new_hash_node->depth = depth;
        for (int i = 0; i < depth; i++)
        {
            new_hash_node->bits[i] = bits[i];
        }
        hash->table[h] = new_hash_node;
        hash->size++;
    }
}

void build_map(node* tree, hash* map, int depth, bool *bits, int jump)
{
    if(jump != START_JUMP) bits[depth] = jump;
    if(*(unsigned char*)tree->item == '*')
    {
        build_map(tree->left, map, depth+1, bits, LEFT_JUMP);
        build_map(tree->right, map, depth+1, bits, RIGHT_JUMP);
    }
    else
    {
        put(map, tree->item, depth+1, bits);
    }
    
}



void get(hash *hash, void* key)
{
    int h = *(unsigned char *)key;
    while (hash->table[h] != NULL)
    {
        if (*(unsigned char *)hash->table[h]->key == *(unsigned char *)key)
        {
            print_bits(hash->table[h]->bits, hash->table[h]->depth);
        }
        h = (h + 1) % MAX_TABLE_SIZE;
    }
}

int main()
{
    hash *hash = create_hash_table();
    put(hash, 35, 1);
    put(hash, 3, 2);
    printf("%d ", get(hash, 35));
    put(hash, 35, 4);
    printf("%d ", get(hash, 35));
    remove_hash_node(hash, 35);
    printf("%d ", get(hash, 35));
}