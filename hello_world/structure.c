
#include <stdio.h>
#include <string.h>

struct MyStructure {
    int myNum;
    char myLetter;
    char myString[30];
};

struct HarryStructure {
    int age;
    char name[10];
    char sex;
};

int main() {
    struct MyStructure s1;
    s1.myNum = 1;
    s1.myLetter = 'A';
    strcpy(s1.myString, "Hello World");

    struct HarryStructure s2 = {27, "Harry", 'M'};

    printf("%c\n", s1.myLetter);
    printf("%s\n", s1.myString);

    printf("\n\n");
    printf("age : %d\nname : %s\nsex : %c\n", s2.age, s2.name, s2.sex);
}