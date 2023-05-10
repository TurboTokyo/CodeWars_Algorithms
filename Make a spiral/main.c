#include <stdio.h>
#include <stdlib.h>

void generate_spiral(int size, int** spiral_matrix) {
    int starting_row = 0;
    int starting_col = 0;
    int spiral_size = size;
    int i;

    while (spiral_size > 0) {
        for (i = starting_col; i < starting_col+spiral_size; i++)
            // Drawing top border
	    spiral_matrix[starting_row][i] = 1;

        if (spiral_size > 1) 
            // Drawing right border
	    for (i = starting_row + 1; i < starting_row + spiral_size; i++)
                spiral_matrix[i][starting_col+spiral_size - 1] = 1;

        if (spiral_size > 2) 
            // Drawing bottom border
	    for (i = starting_col + spiral_size - 2; i >= starting_col; i--)
                spiral_matrix[starting_row + spiral_size - 1][i] = 1;

	if (spiral_size > 3) { 
		// Drawing left border
		for (i = starting_row + spiral_size - 2; i > starting_row; i--) {
			spiral_matrix[i][starting_col] = 1;
			if (spiral_matrix[i][starting_col] == spiral_matrix[i + 1][starting_col]) {
		    // Checking if the last symbol of the layer is not 0
		    break;
		}
		spiral_matrix[i][starting_col] = 1;

            }
        }

        // Moving inwards
        starting_row += 2; 
        starting_col += 2;
        spiral_size -= 4;
    }
}

int main() {
    int spiral_size; // Size of the spiral
    int** spiral_matrix;
    int i, j;

    printf("Enter the size of the spiral: ");
    if (scanf("%d", &spiral_size) != 1 || spiral_size < 5) {
        fprintf(stderr, "Invalid size. Size must be at least 5.\n");
        return 1;
    }

    // Allocating the matrix
    spiral_matrix = (int**)malloc(spiral_size * sizeof(int*));
    if (!spiral_matrix) {
        fprintf(stderr, "Failed to allocate memory for spiral_matrix.\n");
        return 1;
    }

    for (i = 0; i < spiral_size; i++) {
        spiral_matrix[i] = (int*)calloc(spiral_size, sizeof(int)); // Initialization of all elements with 0 value by using calloc
        if (!spiral_matrix[i]) {
            fprintf(stderr, "Failed to allocate memory for spiral_matrix row.\n");
            return 1;
        }
    }

    generate_spiral(spiral_size, spiral_matrix);

    for (i = 0; i < spiral_size; i++) {
        // Printing the matrix
        for (j = 0; j < spiral_size; j++) {
            printf("%d ", spiral_matrix[i][j]);
        }
        printf("\n");
    }

    for (i = 0; i < spiral_size; i++) {
	// Deallocating the matrix
        free(spiral_matrix[i]);
    }
    free(spiral_matrix);

    return 0;
}

