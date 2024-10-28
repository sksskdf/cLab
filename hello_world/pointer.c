#include <stdio.h>

int main() {
    int num = 1;
    int* numPtr = &num;

    printf("%d\n", num);
    printf("%p\n", numPtr);
    printf("%d\n", *numPtr);

    return 0;
}