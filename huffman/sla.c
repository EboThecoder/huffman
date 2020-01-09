#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

typedef struct node
{
    void* item;
    int i;
    char a;
} node;

node *create_node()
{
    node *new_node = (node *)malloc(sizeof(node));
    return new_node;
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

/*int main()
{
    char a[3] = "bom";
    int b = 8;
    node *x = create_node();
    node *y = create_node();
    x->item = a;
    x->a = 'a';
    x->i = 3;
    y->item = &b;
    swap(x, y, sizeof(node));

    printf("int: %d\nsize node: %d\n%s\n%d\n", (int)sizeof(int), (int)sizeof(node), (char*)y->item, *(int*)x->item);
}*/

int main()
{
    char ch, a[50];
    scanf("%s", a);
    FILE* file = fopen(a, "r");
    while ((ch = getc(file)) != EOF)
    {
        printf("ch: %c\n", ch);
    }
    fclose(file);

    FILE *file2 = fopen(a, "r");
    while ((ch = getc(file2)) != EOF)
    {
        printf("ch: %c\n", ch);
    }
    fclose(file2);
}