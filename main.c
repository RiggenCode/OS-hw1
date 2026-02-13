#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void print_fib(int n);
int is_prime(int n);
void print_primes(int n);

int main(int argc, char *argv[]) {
    int n = 10; // default

    if (argc > 1) {
        if (strcmp(argv[1], "-") == 0) {
            if (scanf("%d", &n) != 1) {
                fprintf(stderr, "expected integer on stdin\n");
                return 1;
            }
        } else {
            char *endptr = NULL;
            long parsed = strtol(argv[1], &endptr, 10);
            if (endptr != NULL && *endptr == '\0') {
                n = (int)parsed;
            } else {
                FILE *f = fopen(argv[1], "r");
                if (!f) {
                    perror("open");
                    return 1;
                }
                if (fscanf(f, "%d", &n) != 1) {
                    fprintf(stderr, "expected integer in file %s\n", argv[1]);
                    fclose(f);
                    return 1;
                }
                fclose(f);
            }
        }
    }

    print_primes(n);
    return 0;
}


}