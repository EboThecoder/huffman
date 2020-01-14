#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX 1000

int cont = 0;

typedef struct node
{
    void *item;
    unsigned frequency;
    struct node *left;
    struct node *right;
} node;

typedef struct heap
{
    unsigned size;
    node *nodes[MAX];
} heap;

node *create_node()
{
    node *new_node = (node *)malloc(sizeof(node));

    new_node->frequency = 1;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

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

node *create_tree(void *item, node *left, node *right)
{
    node *new_tree = (node *)malloc(sizeof(node));
    new_tree->item = item;
    new_tree->left = left;
    new_tree->right = right;
    return new_tree;
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

/*void swap(void *u, void *v)
{
    unsigned char *p = u, *q = v, tmp;
    tmp = *p;
    *p = *q;
    *q = tmp;
}*/

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

void print_estado_atual(heap *heap)
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

void test_heap()
{
    heap *heap = create_heap();
    char a[1000];
    node *nodes[1000];
    int i = 0;
    while (scanf("%c", &a[i]) != EOF)
    {
        nodes[i] = create_node();
        nodes[i]->item = &a[i];
        enqueue(heap, nodes[i]);
        i++;
    }
    print_estado_atual(heap);
}

void print_arquivo(node *tree)
{
    if (tree != NULL)
    {
        FILE *compacted = fopen("compacted.txt", "w");
        fprintf(compacted, "%c", *(char *)tree->item);
        fclose(compacted);

        print_arquivo(tree->left);
        print_arquivo(tree->right);
    }
}

void print_tree(node *tree)
{
    if (tree != NULL)
    {
        printf("%c(", *(char *)tree->item);
        print_tree(tree->left);
        printf(")(");
        print_tree(tree->right);
        printf(")");
    }
}

node *make_tree()
{
    heap *heap = create_heap();
    unsigned char a[1000];
    node *nodes[1000];
    int i = 0;
    while (scanf("%c", &a[i]) != EOF)
    {
        nodes[i] = create_node();
        nodes[i]->item = &a[i];
        enqueue(heap, nodes[i]);
        i++;
    }
    print_estado_atual(heap);

    node *left, *right, *parent;
    while (heap->size != 1)
    {
        printf("estado da heap:\n");
        print_estado_atual(heap);
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
    printf("na funçao:\n");
    printf("(");
    print_tree(heap->nodes[1]);
    printf(")\n");
    return heap->nodes[1];
}

int is_bit_i_set(unsigned char c, int i)
{
    unsigned char mask = 1 << i;
    return mask & c;
}

unsigned char set_bit(unsigned char c, int i)
{
    unsigned char mask = 1 << i;
    return mask | c;
}

int get_trash_size(unsigned char ch1)
{
    int trash_size = 0;

    if (is_bit_i_set(ch1, 5))
        trash_size += pow(2, 0);
    if (is_bit_i_set(ch1, 6))
        trash_size += pow(2, 1);
    if (is_bit_i_set(ch1, 7))
        trash_size += pow(2, 2);

    return trash_size;
}

int get_tree_size(unsigned char ch1, unsigned char ch2)
{
    int tree_size = 0;
    if (is_bit_i_set(ch1, 0))
        tree_size += pow(2, 8);
    if (is_bit_i_set(ch1, 1))
        tree_size += pow(2, 9);
    if (is_bit_i_set(ch1, 2))
        tree_size += pow(2, 10);
    if (is_bit_i_set(ch1, 3))
        tree_size += pow(2, 11);
    if (is_bit_i_set(ch1, 4))
        tree_size += pow(2, 12);
    return tree_size + ch2;
}

node *ler_arvore(int size)
{
    if (cont != size)
    {
        unsigned char ch;
        node *tree;
        FILE *compacted = fopen("compacted.txt", "r");
        fscanf(compacted, "%c", &ch);
        fclose(compacted);
        cont++;
        if (ch == '*')
        {
            node *left = ler_arvore(size);
            node *right = ler_arvore(size);
            unsigned char ast = '*';
            tree = create_tree(&ast, left, right);
        }
        else
        {
            tree = create_tree(&ch, NULL, NULL);
        }
        return tree;
    }
    else
        return NULL;
}

void descompactar(node *tree)
{
    unsigned char ch1, ch2;
    scanf("%hhu%hhu", &ch1, &ch2);
    int trash_size = 0, tree_size = 0;
    trash_size = get_trash_size(ch1);
    tree_size = get_tree_size(ch1, ch2);

    int i;
    tree = ler_arvore(tree_size);
    printf("arvore lida: \n");
    print_tree(tree);
}

int main()
{
    // test_heap();
    node *tree = make_tree();
    FILE *compacted = fopen("compacted.txt", "w");
    char ch = 11;
    printf("OIA O CHAR: %c", 11);
    fprintf(compacted, "%c%c", 'a', ch);
    fclose(compacted);
    print_arquivo(tree);

    descompactar(tree);
    return 0;
}