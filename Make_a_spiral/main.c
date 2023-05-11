#include <stdio.h>
#include <stdlib.h>

void generate_spiral(int, int**);

int main() {
    int spiralSize; // Size of the spiral
    int** spiralMatrix;

    printf("Enter the size of the spiral: ");
    scanf("%d", &spiralSize);

    // Allocating the matrix
    spiralMatrix = (int**)malloc(spiralSize * sizeof(int*));
    if (!spiralMatrix) {
        fprintf(stderr, "Failed to allocate memory for spiral_matrix.\n");
        return 1;
    }

    for (int i = 0; i < spiralSize; i++) {
        spiralMatrix[i] = (int*)calloc(spiralSize, sizeof(int)); // Initialization of all elements with 0 value by using calloc

        if (!spiralMatrix[i]) {
            fprintf(stderr, "Failed to allocate memory for spiral_matrix row.\n");
            return 1;
        }
    }

    generate_spiral(spiralSize, spiralMatrix);

    // Printing the matrix
    for (int i = 0; i < spiralSize; i++) {
        for (int j = 0; j < spiralSize; j++) {
            printf("%d ", spiralMatrix[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < spiralSize; i++) {
        // Deallocating the matrix
        free(spiralMatrix[i]);
    }
    free(spiralMatrix);

    return 0;
}


void generate_spiral(int spiralSize, int** spiralMatrix) {
    int top = 0;
    int left = 0;
    int bottom = spiralSize - 1;
    int right = spiralSize - 1;

    while (top <= bottom && left <= right) {
        // Drawing top border
        for (int i = left; i <= right; i++) {
            spiralMatrix[top][i] = 1;

            if (i == right && !(right <= left)) { // Checking if the current side is the last one,
                                                    // if not – drawing a beginning of the next side
                spiralMatrix[top + 1][i] = 1;
            }
        }
        top += 2;

        // Drawing right border
        for (int i = top; i <= bottom; i++) {
            spiralMatrix[i][right] = 1;

            if (i == bottom && !(bottom < top)) {
                spiralMatrix[i][right - 1] = 1;
            }
        }
        right -= 2;

        // Drawing bottom border
        if (top <= bottom) {
            for (int i = right; i >= left; i--) {
                spiralMatrix[bottom][i] = 1;

                if (i == left && !(right <= left)) {
                    spiralMatrix[bottom - 1][i] = 1;
                }
            }
            bottom -= 2;
        }

        // Drawing left border
        if (left <= right) {
            for (int i = bottom; i >= top; i--) {
                spiralMatrix[i][left] = 1;

                if (i == top && !(bottom < top)) {
                    spiralMatrix[i][left + 1] = 1;
                }
            }
            left += 2;
        }
    }
}
