//
// Created by riggens on 2/12/26.
//
#include "../header/print_primes.h"


int is_prime(const int n) {
    if (n <= 1) return 0;
    if (n <= 3) return 1;
    if (n % 2 == 0) return 0;
    for (int i = 3; (long long)i * i <= n; i += 2) {
        if (n % i == 0) return 0;
    }
    return 1;
}



void print_primes(const int n) {
    printf("%d\n", n);
    printf("1\n");
    for (int i = 2; i <= n; ++i) {
        if (is_prime(i)) {
            printf("%d\n", i);
        }
    }
}
