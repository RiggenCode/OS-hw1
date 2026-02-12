#include <stdio.h>

void print_fib(int n);


int main(void) {
    printf("Hello, World!\n");

    int n = 10;
    print_fib(n);
    return 0;
}

void print_fib(int n) {
    if (n < 1) {
        printf("Invalid number of terms\n");
        return;
    }
    int prev1 = 1;
    int prev2 = 0;
    for (int i = 0; i <= n; i++) {
        if (i > 1) {
            int curr = prev1 + prev2;
            printf("%d\n", curr);
            prev2 = prev1;
            prev1 = curr;
        }
        else if (i == 0) {
            printf("%d\n", prev2);
        } else if (i == 1) {
            printf("%d\n", prev1);
        }

    }
}