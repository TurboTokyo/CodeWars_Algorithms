#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char* sumOfDivided(int*, int);
int countPrimes(int);
bool isPrime(int);

int main(int argc, char** argv) {
    int listLength;
    int* inputList;
    char* result;

    // Check if the number of arguments is less than 2
    if (argc <= 2) {
        printf("Usage: %s num1 num2 ... \n", argv[0]);
        return 1;
    }

    listLength = argc - 1; // Get the length of the input list
    inputList = malloc(sizeof(int) * listLength); // Allocate memory for the input list

    // Iterate through the command line arguments and store them in the input list
    for (int i = 0; i < listLength; i++) {
        inputList[i] = atoi(argv[i + 1]);
    }

    // Call the sumOfDivided function and store the result
    result = sumOfDivided(inputList, listLength);
    printf("%s\n", result);

    free(result);
    free(inputList);

    return 0;
}

char* sumOfDivided(int* lst, int listLength) {
    // Find the maximum absolute value in the array
    int maxVal = abs(lst[0]);
    char* resultString;

    for (int i = 1; i < listLength; i++)
        if (abs(lst[i]) > maxVal)
            maxVal = abs(lst[i]);

    resultString = calloc(countPrimes(maxVal) * 12, sizeof(char));

    // Iterate through numbers from 2 to maxVal
    for (int i = 2; i <= maxVal; i++) {
        int sum = 0;
        bool isFactor = false;

        // Check if the number is not prime, then skip to the next iteration
        if (!isPrime(i)) continue;

        // Iterate through the array again
        for (int j = 0; j < listLength; j++) {
            // Check if the current number is divisible by i
            if (lst[j] % i == 0) {
                sum += lst[j]; // Add the current number to the sum
                isFactor = true;
            }
        }

        // If i is a factor of at least one number in the array
        if (isFactor) {
            char buffer[20];

            // Store the formatted string in buffer
            sprintf(buffer, "(%d %d)", i, sum);

            // Append the buffer to the result string
            strcat(resultString, buffer);
        }
    }

    return resultString;
}

// Function to calculate the number of primes up to num
int countPrimes(int num) {
    int count = 0;

    for (int i = 2; i <= num; i++)
        // Increase the counter if the number is prime
        if (isPrime(i))
            count++;

    return count;
}

bool isPrime(int num) {
    // Special cases
    if (num <= 1) return false; // numbers less than or equal to 1 are not prime
    if (num == 2 || num == 3) return true; // 2 and 3 are prime numbers

    // Check divisibility by 2 or 3
    if (num % 2 == 0 || num % 3 == 0) return false;

    // Check divisibility by numbers up to sqrt(num)
    for (int i = 5; i * i <= num; i += 6)
        if (num % i == 0 || num % (i + 2) == 0)
            return false;

    return true; // if no divisor found, the number is prime
}
