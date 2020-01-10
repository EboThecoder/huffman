#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "tree.h"
#include "heap.h"
#include "hash.h"
#include "compactor.h"
#include "descompactor.h"

int main()
{
    int a;
    scanf("%d", &a);
    if(a == 1) compact();
    if(!a) descompact();
    return 0;
}