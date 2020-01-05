#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cont = 0;

typedef struct node
{
    void *item;
    unsigned frequency;
    struct node *left;
    struct node *right;
} node;

node *create_node()
{
    node *new_node = (node *)malloc(sizeof(node));
    new_node->frequency = 1;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

node *create_tree(void *item, node *left, node *right)
{
    node *new_tree = (node *)malloc(sizeof(node));
    new_tree->item = item;
    new_tree->left = left;
    new_tree->right = right;
    return new_tree;
}

void swap(void *u, void *v, size_t len)
{
    unsigned char *p = u, *q = v, tmp;
    for (size_t i = 0; i < len; i++)
    {
       // printf("%hhu ", q[i]);
        tmp = p[i];
        p[i] = q[i];
        q[i] = tmp;

    }
}

void print_pre_order(node *tree)
{
    if (tree != NULL)
    {
        printf("%d(", *(unsigned char *)tree->item);
        print_pre_order(tree->left);
        printf(")(");
        print_pre_order(tree->right);
        printf(")");
    }
}

/*int main()
{
    char str1[10] = "primeira";
    char str2[10] = "segunda";
    swap(&str1, &str2, 10*sizeof(char));
    printf("\n%s %s\n", str2, str1);
    int i1 = 1;
    int i2 = 2;
    char ch1 = 'a';
    char ch2 = 'b';
    swap(&ch1, &ch2, sizeof(char));
   // swap(&i1, &i2, sizeof(int));
  //  printf("\n%d %d\n", i2, i1);
    printf("\n%c %c\n", ch2, ch1);
    void *v1;
    void *v2;
    v1 = &i2;
    v2 = &i1;
    swap(v1, v2, sizeof(void));
    printf("\n%d %d\n", *(int *)v2, *(int *)v1);
    printf("tamanho do void %zd\n", sizeof(void));
    unsigned char ast = 42;
    printf("%c", ast);
    return 0;
}*/

/*int main()
{
    node* n1 = create_node();
    node *n2 = create_node();
    node *f1 = create_node();
    char a1 = 42;
    char a2 = 'a';
    char a3 = 'b';
    n1->item = &a1;
    n2->item = &a2;
    f1->item = &a3;
    n1->left = f1;
    swap(n1, n2, sizeof(node));
    printf("n1: %c %d\nn2: %c %d\n", *(char *)n1->item, n1->frequency, *(char *)n2->item, n2->frequency);
    printf("%c\n", *(char*)n2->left->item);
    return 0;
}*/

node *ler_arvore(FILE* compacted, int size)
{
    if (cont != size)
    {
        unsigned char ch;
        node *tree;
        fscanf(compacted, "%c", &ch);
        cont++;
        if (ch == '*')
        {
            printf("ast: %d\n", ch);
            node *left = ler_arvore(compacted, size);
            node *right = ler_arvore(compacted, size);
            unsigned char ast = '*';
            tree = create_tree(&ast, left, right);
            printf("(");
            print_pre_order(tree);
            printf(")\n");
        }
        else
        {
            tree = create_tree(&ch, NULL, NULL);
            printf("char: %d\n", ch);
            printf("(");
            print_pre_order(tree);
            printf(")\n");
        }
        return tree;
    }
    else
        return NULL;
}

node *ler_arvore(FILE *compacted, int size)
{
    unsigned char ch;
    for(int i=0; i<size;i++)
    {
        fscanf(comapcted, "%c", &ch);
    }
}

int main()
{
    FILE *compacted = fopen("compacted.txt", "r");
    node* tree = ler_arvore(compacted, 11);
    fclose(compacted);
    printf("final\n");
    printf("(");
    print_pre_order(tree);
    printf(")\n");
    return 0;
}