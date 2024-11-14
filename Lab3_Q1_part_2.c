// Q1 part 2
#include <stdio.h>
#include <stdbool.h>

// Check other functions in Lab3_Q1_part1.c

// PROTOTYPES
void reshape(const int arr[], int length, int nRows, int nCols, int arr2d[nRows][nCols]);
void trans_matrix(int nRows, int nCols, const int mat[nRows][nCols], int mat_transp[nCols][nRows]);
bool found_duplicate(int arr[], int length);

int main() {
    // Test case 6: reshape
    int arr1d[] = {1, 2, 3, 4, 5, 6, 7, 8, 9}; // Example array for reshape
    int length1d = sizeof(arr1d)/sizeof(arr1d[0]);
    int arr2d[3][3];
    reshape(arr1d, length1d, 3, 3, arr2d);

    printf("Test case 6: Reshaped 2D array:\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {   
            printf("%d ", arr2d[i][j]);
        }
        printf("\n");
    }

    // Test case 7: trans_matrix
    int mat[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}; // Example Matrix for trans_matrix
    int mat_transp[3][3];
    trans_matrix(3, 3, mat, mat_transp);

    printf("Test case 7: Transposed matrix:\n"); // For printing the trans_matrix
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", mat_transp[i][j]);
        }
        printf("\n");
    }

    // Test case 8: found_duplicate
    int arr_with_duplicate[] = {1, 2, 3, 4, 5, 2}; // Example array for found duplicate
    int length_with_duplicate = 6; // Another way of getting length is 
    bool has_duplicate = found_duplicate(arr_with_duplicate, length_with_duplicate);
    printf("Test case 8: found_duplicate:\n");
    printf("Example with duplicate. ");
    if (has_duplicate) {
        printf("found_duplicate position = true\n");
    } else {
        printf("found_duplicate position = false\n");
    }

    printf("Example without duplicate. ");
    int arr_no_duplicate[] = {1, 2, 3, 4, 5};
    int length_no_duplicate = 5;
    has_duplicate = found_duplicate(arr_no_duplicate, length_no_duplicate);
    if (has_duplicate) {
        printf("found_duplicate = true\n");
    } else {
        printf("found_duplicate = false\n");
    }
    return 0;
}


void reshape(const int arr[], int length, int nRows, int nCols, int arr2d[nRows][nCols]) {
    if (length != nRows * nCols) {
        printf("Error: Length of 1D array does not match the specified 2D array dimensions.\n");
        return;
    }

    int row = 0, col = 0;
    for (int i = 0; i < length; i++) {
        arr2d[row][col] = arr[i];
        col++;
        if (col == nCols) {
            col = 0;
            row++;
        }
    }
}

void trans_matrix(int nRows, int nCols, const int mat[nRows][nCols], int mat_transp[nCols][nRows]) {
    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nCols; j++) {
            mat_transp[j][i] = mat[i][j];
        }
    }
}

bool found_duplicate(int arr[], int length) {
    for (int i = 0; i < length; i++) {
        for (int j = i + 1; j < length; j++) {
            if (arr[i] == arr[j]) {
                return true;
            }
        }
    }
    return false;
}