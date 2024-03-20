#include <stdio.h>
#include <math.h>

#define ALPHABET_SIZE 25

// Function to calculate the approximate number of possible keys
double calculatePossibleKeys() {
    double possibleKeys = 1;
    int i;

    // Calculate factorial of 25 (ALPHABET_SIZE)
    for (i = 1; i <= ALPHABET_SIZE; i++) {
        possibleKeys *= i;
    }

    // Approximate as a power of 2
    return log2(possibleKeys);
}

int main() {
    double keys = calculatePossibleKeys();
    printf("Approximate number of possible keys: %.0lf\n", pow(2, keys));
    
    return 0;
}
