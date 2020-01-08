#include "hash.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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
    for (int i = 1; i <= size; i++)
    {
        if (bits[i])
            printf("1");
        else
            printf("0");
    }
    printf("\n");
    printf("depth : %d\n", size);
}

void put(hash *hash, void *key, int depth, int frequency, bool *bits)
{
    if (hash->size >= MAX_TABLE_SIZE)
    {
        //printf("hash table overflow\n");
    }
    else
    {
        int h;
        if(*(unsigned char *)key != '\\') h = *(unsigned char *)key;
        else h = *((unsigned char *)key + 1);
        while (hash->table[h] != NULL)
        {
            h = (h + 1) % MAX_TABLE_SIZE;
        }

        hash_node *new_hash_node = (hash_node *)malloc(sizeof(hash_node));
        new_hash_node->key = key;
        new_hash_node->depth = depth;
        new_hash_node->frequency = frequency;
        for (int i = 0; i < depth; i++)
        {
            new_hash_node->bits[i] = bits[i];
        }
        hash->table[h] = new_hash_node;
        hash->size++;
    }
}

void build_map(node *tree, hash *map, int depth, bool *bits, int jump)
{
    if (jump != START_JUMP)
        bits[depth] = jump;
    if (*(unsigned char *)tree->item == '*')
    {
        build_map(tree->left, map, depth + 1, bits, LEFT_JUMP);
        build_map(tree->right, map, depth + 1, bits, RIGHT_JUMP);
    }
    else
    {
        put(map, tree->item, depth + 1, tree->frequency, bits);
    }
}

void get(hash *hash, void *key)
{
    int h = *(unsigned char *)key;
    while (hash->table[h] != NULL)
    {
        if (*(unsigned char *)key == '\\' && *(unsigned char *)hash->table[h]->key == '\\')
        {
            if (*((unsigned char *)hash->table[h]->key + 1) == *((unsigned char *)key + 1))
                print_bits(hash->table[h]->bits, hash->table[h]->depth);
        }
        if (*(unsigned char *)hash->table[h]->key == *(unsigned char *)key)
        {
            print_bits(hash->table[h]->bits, hash->table[h]->depth);
        }
        h = (h + 1) % MAX_TABLE_SIZE;
    }
}