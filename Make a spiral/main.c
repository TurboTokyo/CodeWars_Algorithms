#include <stdio.h>
#include <stdlib.h>

void drawSpiral(int providedNumber, int** arr) {
    int top = 0;
    int left = 0;
    int bottom = providedNumber - 1;
    int right = providedNumber - 1;

    while (top <= bottom && left <= right) {
        for (int i = left; i <= right; i++) {
            arr[top][i] = 1;
            if (i == right) {
              arr[top + 1][i] = 1;
            }
        }
        top += 2;

        for (int i = top; i <= bottom; i++) {
            arr[i][right] = 1;
            if (i == bottom) {
              arr[i][right - 1] = 1;
            }
        }
        right -= 2;

        if (top <= bottom) {
            for (int i = right; i >= left; i--) {
                arr[bottom][i] = 1;
                if (i == left) {
                  arr[bottom - 1][i] = 1;
                }
            }
            bottom -= 2;
        }

        if (left <= right) {
            for (int i = bottom; i >= top; i--) {
                arr[i][left] = 1;
                if (i == top) {
                  arr[i][left + 1] = 1;
                }
            }
            left += 2;
        }
    }
}

int main() {
    int providedNumber;
    printf("Enter the size of the spiral: ");
    scanf("%d", &providedNumber);

    int** arr = (int**)malloc(providedNumber * sizeof(int*));
    for (int i = 0; i < providedNumber; i++) {
        arr[i] = (int*)calloc(providedNumber, sizeof(int));
    }

    drawSpiral(providedNumber, arr);

    for (int i = 0; i < providedNumber; i++) {
        for (int j = 0; j < providedNumber; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < providedNumber; i++) {
        free(arr[i]);
    }
    free(arr);

    return 0;
}
