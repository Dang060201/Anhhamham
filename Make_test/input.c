#include <stdio.h>

void exampleFunction(int a, int b) {
    int c = a + b;
    printf("Result: %d\n", c);
}

int main() {
    int x = 10, y = 20;
    exampleFunction(x, y);
    return 0;
}
