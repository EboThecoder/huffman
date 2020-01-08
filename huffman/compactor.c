#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "tree.h"
#include "heap.h"
#include "hash.h"

#include "compactor.h"

void read_file(unsigned char *str)
{
    int i=0;
    FILE *file_to_compact = fopen("file_to_compact.txt", "r");
    while(fscanf(file_to_compact, "%c", &str[i])!=EOF)
    {
        i++;
    }
    fclose(file_to_compact);
}

void get_trash_and_string_size(hash *map, int *trash_size, int *string_size)
{
    for (int i = 0; i < 256; i++)
    {
        if (map->table[i] != NULL)
        {
            *trash_size += map->table[i]->depth * map->table[i]->frequency;
        }
    }
    *string_size = *trash_size / 8;
    if (*trash_size % 8 != 0)
    {
        *string_size += 1;
        *trash_size = 8 - *trash_size % 8;
    }
    else *trash_size = 0;
}

unsigned char set_bit(unsigned char c, int i)
{
    unsigned char mask = 1 << 7-i;
    return mask | c;
}

int is_bit_i_set(unsigned char c, int i)
{
    unsigned char mask = 1 << i;
    return mask & c;
}

void zero_string(unsigned char *str, int size)
{
    for (int i = 0; i < size; i++)
    {
        str[i] = 0;
    }
}

void print_byte(unsigned char byte)
{
    int i;
    for (i = 7; i >= 0; --i)
    {
        if(is_bit_i_set(byte, i)) printf("1");
        else printf("0");
    }
    printf(" ");
}

void save_first_2_bytes(int *trash_size, int *tree_size, FILE *compacted_file)
{
    unsigned char ch1, ch2;
    ch1 = *trash_size;
    ch2 = *tree_size;
    ch1 <<= 5;
    *tree_size >>= 8;
    ch1 += *tree_size;
    fprintf(compacted_file, "%c%c", ch1, ch2);
}

void save_file(hash *map, int string_size, unsigned char *str, FILE *compacted_file)
{
    unsigned char compacted[string_size];
    zero_string(compacted, string_size);
    int set_bit_index = 0, compacted_index= 0, str_index = 0, bits_index = 0;
    for (str_index = 0; str_index < strlen(str); str_index++)
    {
        for(bits_index=0 ; bits_index < map->table[str[str_index]]->depth; bits_index++)
        {
            if(map->table[str[str_index]]->bits[bits_index])
            {
                printf("1");
                compacted[compacted_index] = set_bit(compacted[compacted_index], set_bit_index);
            }
            else printf("0");
            if (set_bit_index == 7)
            {
                compacted_index += 1;
                printf(" ");
            }
            set_bit_index = (set_bit_index + 1) % 8;
        }
    }
    printf("\n");
    compacted[string_size] = '\0';
    for(int i=0;i<string_size;i++)
    {
        printf("%d ", compacted[i]);
    }
    printf("\n");
    //printf("%s\n", compacted);
    fprintf(compacted_file, "%s", compacted);
}

node *build_tree(unsigned char *str)
{
    heap *heap = create_heap();
    node *nodes[10000];
    unsigned char escape_string[10000][2];
    for(int i =0 ; i< strlen(str) ; i++)
    {
        nodes[i] = create_node();
        if(str[i] == '*')
        {
            escape_string[i][0] = '\\';
            escape_string[i][1] = '*';
            nodes[i]->item = escape_string[i];
        }
        else if(str[i] == '\\')
        {

            escape_string[i][0] = '\\';
            escape_string[i][1] = '\\';
            nodes[i]->item = escape_string[i];
        }
        else
        {
            nodes[i]->item = &str[i];
        }
        enqueue(heap, nodes[i]);
    }
    //print_heap(heap);
    node *left, *right, *parent;
    while (heap->size != 1)
    {
        /*printf("estado da heap:\n");
        print_heap(heap);
        printf("\n");*/
        left = dequeue(heap);
        right = dequeue(heap);
        parent = create_node();
        unsigned char ast = '*';
        parent->item = &ast;
        parent->frequency = left->frequency + right->frequency;
        parent->left = left;
        parent->right = right;
        /*
        printf("(");
        print_tree(parent);
        printf(")\n");*/
        enqueue(heap, parent);
    }
    /*
    printf("(");
    print_tree(heap->nodes[1]);
    printf(")\n");*/
    return heap->nodes[1];
}

void compact()
{
    unsigned char str[10000];
    read_file(str);

    node *tree = build_tree(str);
    print_tree(tree);
    printf("\n\n");
    hash *map = create_hash_table();
    bool bits[MAX_DEPTH];
    build_map(tree, map, -1, bits, START_JUMP);
    

    int *tree_size, *trash_size, *string_size;
    int zero_1 = 0, zero_2 = 0, zero_3 = 0;
    tree_size = &zero_1;
    trash_size = &zero_2;
    string_size = &zero_3;
    get_tree_size(tree, tree_size);
    get_trash_and_string_size(map, trash_size, string_size);
    printf("tree size: %d, trash size: %d, string size: %d\n\n", *tree_size, *trash_size, *string_size);

    FILE* compacted_file = fopen("compacted_file.txt", "w");
    save_first_2_bytes(tree_size, trash_size, compacted_file);
    save_tree(tree, compacted_file);
    save_file(map, *string_size, str, compacted_file);
    fclose(compacted_file);
}