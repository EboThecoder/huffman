#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

#include "tree.h"
#include "heap.h"
#include "hash.h"

#include "descompactor.h"

int is_bit_i_set(unsigned char c, int i)
{
    unsigned char mask = 1 << 7 - i;
    return mask & c;
}


void read_first_two_bytes(FILE *file, unsigned short *trash_size, unsigned short *tree_size)
{
    unsigned char ch[2];
    fscanf(file, "%c%c", &ch[0], &ch[1]);
    printf("chars %d %d\n", ch[0], ch[1]);
    if (is_bit_i_set(ch[0], 0)) *trash_size += 4;
    if (is_bit_i_set(ch[0], 1)) *trash_size += 2;
    if (is_bit_i_set(ch[0], 2)) *trash_size += 1;
    ch[0] <<= 3;
    *tree_size += ch[0];
    *tree_size <<= 5;
    *tree_size += ch[1];
}

node *read_tree(FILE *file)
{
    node *tree;
    unsigned char ch;
    fscanf(file, "%c", &ch);
    void *item = (void *)malloc(2 * sizeof(unsigned char));
    *(unsigned char *)item = ch;
    if (ch == '\\')
    {
        fscanf(file, "%c", &ch);
        *((unsigned char *)item + 1) = ch;
    }
    if (*(unsigned char *)item == '*')
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

void read_file(node* tree, unsigned short trash_size, FILE *file)
{
    node* aux = tree;
    unsigned char ch, next_ch;
    FILE *descompacted_file = fopen("../files/descompacted_file", "w");
    fscanf(file, "%c", &ch);
    while (fscanf(file, "%c", &next_ch) != EOF)
    {
       for(int j=0; j< 8;j++)
       {
           if(is_bit_i_set(ch, j)) aux = aux->right;
           else aux = aux->left;
           if (*(unsigned char *)aux->item != '*')
           {
               if(*(unsigned char *)aux->item == '\\') fprintf(descompacted_file, "%c", *((unsigned char *)aux->item + 1));
               else fprintf(descompacted_file, "%c", *(unsigned char *)aux->item);
               aux = tree;
           }
       }
       ch = next_ch;
    }
    for (int j = 0; j < 8- trash_size; j++)
    {
        if (is_bit_i_set(ch, j)) aux = aux->right;
        else aux = aux->left;
        if (*(unsigned char *)aux->item != '*')
        {
            if (*(unsigned char *)aux->item == '\\') fprintf(descompacted_file, "%c", *((unsigned char *)aux->item + 1));
            else fprintf(descompacted_file, "%c", *(unsigned char *)aux->item);
            aux = tree;
        }
    }
    fclose(descompacted_file);
}

void descompact()
{
    FILE *file = fopen("../compacted_files/compacted_file", "r");
    unsigned short *trash_size = allocate_counter(), *tree_size = allocate_counter();
    read_first_two_bytes(file, trash_size, tree_size);
    node *tree = read_tree(file);
    printf("trash size: %d\ntree size: %d\n", *trash_size, *tree_size);
    print_tree(tree);
    printf("\n");
    read_file(tree, *trash_size, file);
    fclose(file);
}