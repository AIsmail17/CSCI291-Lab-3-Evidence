// Q1 part 1
#include <stdio.h> 
#include <stdbool.h> 

#define SIZE 24
#define nRows 8
#define nCols 3

// PROTOTYPES
void print_array(int array[], int length);
void print_matrix(int mat[][nCols], int rows);
// ADDED
bool isValid(const int arr[], int length, int pos);
void remove_element(int arr[], int length, int pos);
void insert_element(int arr[], int length, int pos, int value);
// Check Lab3_Q1_part_2 for the rest of the functionQHews

int main()
{
    // part of original file. I prefered making my own arrays for each test to avoid this error: "Too many arguments"
    int arr[SIZE];
    int arr2d[nRows][nCols];
    print_matrix(arr2d,nRows);

    // Call to different functions
    // TEST ARRAY For remove_element
    int test_arr[] = {10, 20, 30, 40, 50};
    int test_length = sizeof(test_arr)/sizeof(test_arr[0]);
    
    // Test case 1: Testing isValid function
    printf("\nTest Case 1: isValid function testing\n");

    // Invalid, should be between 0-23
    printf("Position -1 is valid: ");
    if (isValid(arr, SIZE, -1)) {
        printf("true\n");
    } else {
        printf("false\n");
    }

    // Valid
    printf("Position 0 is valid: ");
    if (isValid(arr, SIZE, 0)) {
        printf("true\n");
    } else {
        printf("false\n");
    }

    // Valid
    printf("Position 23 is valid: ");
    if (isValid(arr, SIZE, 23)) {
        printf("true\n");
    } else {
        printf("false\n");
    }

    // 24 means 0-23, hence 24 is invalid
    printf("Position 24 is valid: ");
    if (isValid(arr, SIZE, 24)) {
        printf("true\n");
    } else {
        printf("false\n");
    }

    // Test case 2: Testing remove_element as shown in Fig 1.1
    printf("\nTest Case 2: remove_element demonstration\n");
    printf("Original array:\n");
    print_array(test_arr, test_length);
    
    printf("\nRemoving element at position 2:\n");
    remove_element(test_arr, test_length, 2);
    print_array(test_arr, test_length);

    // Test case 3: Testing remove_element with invalid position
    printf("\nTest Case 3: remove_element with invalid position\n");
    printf("Attempting to remove element at position 10:\n");
    remove_element(test_arr, test_length, 10);

    // Test case 4: Testing insert_element as shown in Fig 1.2
    printf("\nTest Case 4: insert_element demonstration\n");
    int test_insert[] = {10, 20, 30, 40, 50};
    printf("Original array:\n");
    print_array(test_insert, test_length);
    
    printf("\nInserting value 80 at position 2:\n");
    insert_element(test_insert, test_length, 2, 80);
    print_array(test_insert, test_length);

    // Test case 5: Testing insert_element with invalid position
    printf("\nTest Case 5: insert_element with invalid position\n");
    printf("Attempting to insert value at position 10:\n");
    insert_element(test_insert, test_length, 10, 100);
}

void print_array(int array[], int length){
   for(int i=0;i<length; i++)
      printf("array[%d]= %d\n", i, array[i]);
}

void print_matrix(int mat[][nCols], int rows){
   for(int i=0;i<rows; i++){
    for(int j=0;j<nCols; j++)
         printf("mat[%d][%d]= %d\n", i,j, mat[i][j]);
    puts("");     
   }     
}

//FUNCTION DEFINITIONS
// isValid function. If pos is valid, return true. Else return false
bool isValid(const int arr[], int length, int pos) {
    if (pos >= 0 && pos < length) {
        return true;
    } else {
        return false;
    }
}

// remove_element function. Shifts elements up with For loop.
void remove_element(int arr[], int length, int pos) {
    if (isValid(arr, length, pos) == false) {
        printf("Error: Invalid position %d\n", pos);
        return;
    }
    
    for (int i = pos; i > 0; i--) {
        arr[i] = arr[i-1];
    }
}

// insert_element function. Shifts elements down using for loop then inserts new value. 1st value gets removed
void insert_element(int arr[], int length, int pos, int value) {
    if (isValid(arr, length, pos) == false) {
        printf("Error: Invalid position %d\n", pos);
        return;
    }

    for (int i = 0; i < pos; i++) {
        arr[i] = arr[i+1];
    }
    // Insert the new value at the position
    arr[pos] = value;
}