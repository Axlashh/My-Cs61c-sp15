#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

void set_bit(uint16_t * x,
             unsigned n,
             unsigned v) {
    // YOUR CODE HERE
    unsigned a = ~0;
    a = a ^ (1 << n);
    *x = *x & a;
    *x = *x | (v << n);
}

void lfsr_calculate(uint16_t *reg) {

    int n = *reg & 1;
    n ^= (*reg >> 2) & 1;
    n ^= (*reg >> 3) & 1;
    n ^= (*reg >> 5) & 1;
    *reg = *reg >> 1;
    set_bit(reg, 15, n);
}

int main() {
  int8_t *numbers = (int8_t*) malloc(sizeof(int8_t) * 65535);
  if (numbers == NULL) {
    printf("Memory allocation failed!");
    exit(1);
  }

  memset(numbers, 0, sizeof(int8_t) * 65535);
  uint16_t reg = 0x1;
  uint32_t count = 0;
  int i;

  do {
    count++;
    numbers[reg] = 1;
    if (count < 24) {
      printf("My number is: %u\n", reg);
    } else if (count == 24) {
      printf(" ... etc etc ... \n");
    }
    for (i = 0; i < 32; i++)
      lfsr_calculate(&reg);
  } while (numbers[reg] != 1);

  printf("Got %u numbers before cycling!\n", count);

  if (count == 65535) {
    printf("Congratulations! It works!\n");
  } else {
    printf("Did I miss something?\n");
  }

  free(numbers);

  return 0;
}
