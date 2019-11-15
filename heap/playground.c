#include <stdio.h>

void print_bits(size_t n) {
    long n_bits = sizeof(size_t) * 8;
    size_t pivot = 1 << (n_bits-1);
    size_t bit;
    for (size_t i = 0; i < n_bits; i++) {
        bit = (n & pivot) >> (n_bits-1-i);
        printf("%zu", bit);
        pivot = pivot >> 1;
    }    
    printf("\n");
}

/* 
 * Returns a a number (size_t), where the only bit set to 1
 * is the msb of input n. If n is (in binary representation):
 * 0000000000000000000000000000000000000000000000000000000010011100
 * then this function will return:
 * 0000000000000000000000000000000000000000000000000000000010000000
 */
size_t get_msb(size_t n) {
    long n_bits = sizeof(size_t) * 8;
    size_t pivot = 1;
    pivot = pivot << (n_bits-1);
    size_t bit = 0;
    ssize_t i = n_bits-1;
    while (i >= 0 && bit != 1) {
        bit = (n & pivot) >> i;
        pivot = pivot >> 1;
        i--;
    }
    return (bit << (i+1));
}

int main() {
    size_t n = 289;
    size_t msb = get_msb(n);
    printf("n=%ld\n", n);
    print_bits(n);
    print_bits(msb);

    n = 1;
    msb = get_msb(n);
    printf("n=%ld\n", n);
    print_bits(n);
    print_bits(msb);

    n = 0;
    msb = get_msb(n);
    printf("n=%ld\n", n);
    print_bits(n);
    print_bits(msb);

    return 0;
}
