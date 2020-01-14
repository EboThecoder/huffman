#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "heap.h"
#include "tree.h"

int main()
{

    int i = 0;
    unsigned char str[10000];
    FILE *file_to_compact = fopen("file_to_compact.txt", "r");
    while (fscanf(file_to_compact, "%c", &str[i]) != EOF)
    {
        i++;
    }
    fclose(file_to_compact);

    heap *heap = create_heap();
    node *nodes[10000];
    unsigned char escape_string[10000][2];
    for (int i = 0; i < strlen(str); i++)
    {
        nodes[i] = create_node();
        if (str[i] == '*')
        {
            escape_string[i][0] = '\\';
            escape_string[i][1] = '*';
            nodes[i]->item = escape_string[i];
        }
        else if (str[i] == '\\')
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
    print_heap(heap);
}