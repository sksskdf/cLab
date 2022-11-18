#include <stdio.h>

void myFunction(char[]);
int mySecondFunction(int, int);

int main() {
    myFunction("hello");
    int result = mySecondFunction(1, 2);
    printf("%d\n", result);
    return 0;
}

void myFunction(char str[]) {
    printf("%s\n", str);
}

int mySecondFunction(int x, int y) {
    return x + y;
}
