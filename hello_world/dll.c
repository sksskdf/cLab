#include <stdio.h>

// Rust DLL에 정의된 함수 선언
extern int add(int a, int b);
extern const char* greet();

int main() {
    // Rust의 add 함수 호출
    int result = add(5, 10);
    printf("Result of add(5, 10): %d\n", result);

    // Rust의 greet 함수 호출
    const char* message = greet();
    printf("Message from Rust: %s\n", message);

    return 0;
}

