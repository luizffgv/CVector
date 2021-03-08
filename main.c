#include <stdio.h>

#include <stdlib.h>
#include <vector.h>

void PrintInt(void *data);

int main(void)
{
    Vector vec = VecNew(sizeof(int));

    int cur = 1;
    VecPushBack(vec, &cur);
    cur = 2;
    VecPushBack(vec, &cur);
    cur = 4;
    VecPushBack(vec, &cur);
    cur = 8;
    VecPushBack(vec, &cur);

    printf("Size: %4zu, capacity: %4zu\n", VecSizeOfElem(vec), VecCapacity(vec));
    VecForEach(vec, PrintInt);
    putchar('\n');

    puts("Removing [2]");
    VecPopAt(vec, 2);
    printf("Size: %4zu, capacity: %4zu\n", VecSizeOfElem(vec), VecCapacity(vec));
    VecForEach(vec, PrintInt);
    putchar('\n');

    puts("Shrinking to fit");
    VecShrinkToFit(vec);
    printf("Size: %4zu, capacity: %4zu\n", VecSizeOfElem(vec), VecCapacity(vec));

    puts("Changing [2] to 3 and appending {4, 5, 6}");
    *(int*)VecAt(vec, 2) = 3;
    for (int i = 4; i <= 6; ++i)
    {
        cur = i;
        VecPushBack(vec, &cur);
    }
    printf("Size: %4zu, capacity: %4zu\n", VecSizeOfElem(vec), VecCapacity(vec));
    VecForEach(vec, PrintInt);
    putchar('\n');

    puts("Shrinking to fit");
    VecShrinkToFit(vec);
    printf("Size: %4zu, capacity: %4zu\n", VecSizeOfElem(vec), VecCapacity(vec));

    puts("Stealing the vector's data");
    size_t stolen_len = VecLength(vec);
    int *stolen_data = VecDataSteal(vec);

    puts("Stolen data:");
    for (size_t i = 0; i < stolen_len; ++i)
        printf("%d ", stolen_data[i]);
    putchar('\n');

    free(stolen_data);
    VecDelete(vec);

    puts("Done.");
    
    return 0;
}

void PrintInt(void *data)
{
    printf("%d ", *(int *)data);
}
