#include <stdlib.h>
#include <stdio.h>




int get_sum_from_bounds(int max, int* arrayInput) {
    int sum = 0;

    for(int i = 0; i < max+1; i++) {
        sum = sum + arrayInput[i];
    }

    return sum;
}



int or(int a, int b) {
    if(a == 1 || b == 1) {
        return 1;
    } else {
        return 0;
    }
}



int fill_cell(int **matrix, int *subset_list, int r, int c) {

    int a = 0;
    int b = 0;

    if(r == 0) {
        if (c == subset_list[0]) return 1;
        return 0;
    }

    a = matrix[r-1][c];

    if ((c - subset_list[r]) >= 0) b = matrix[r-1][c - subset_list[r]];
    return or(a,b);
}


int displayTable(int** matrix, int* subset_list, int max_r, int max_c) {
    for(int r = 0; r < max_r; r++) {
        printf("[%d] ",subset_list[r]);
        for(int c = 0; c < max_c; c++) {
            printf("%d ", matrix[r][c]);
        }
        printf("\n");
    }
}



int min(int a, int b) {
    if (a < b) return a;
    return b;
}


// backtracking
void checkIfHasSubset(int **matrix, int* subset_list, int max_r, int max_c) {
    printf("%d %d\n", max_r, max_c);
    int* valid_subset = calloc(1000, sizeof(int));
    int i = 0;
    if(matrix[max_r][max_c] == 1) {
        printf("\nThere is a subset that has a sum equal to k.\n");
        printf("The solution subset is: { ");

        int col = max_c;

        // go upwards from bottom right
        for (int row = max_r; row > -1; row--){
                // check if we reached the first col or we are on a 1 
                if (col != 0 && matrix[row][col] == 1) {
                    // check if we are the highest 1. if not, then go upwards.
                    // if we are at row == 0, we are already the highest 1.
                    if( (row == 0) || matrix[row-1][col] == 0 ) {
                        valid_subset[i] = subset_list[row];                     // add to valid subset
                        i++;                                                    // increment the size of subset list
                        printf("%d ",subset_list[row]);                         // print the member of the subset
                        col = col - subset_list[row];                           // go left S blocks where s is the value of the subset member
                        if (col < 0) break;                                     
                    }
                } else {
                    break;
                }
            
            }

        printf("}");

    } else {
        printf("\nThere is no subset that has a sum equal to k.\n");
    }
}


int main() {
    // Read input file
    FILE *fp;

    // "set_size" is the size of the set. "sum" is the value of "k"
    // set_size dictates the number of rows in the 2D array, while k+1 dictates the nmber of columns.   
    int set_size = 0, val = 0, sum = 0;
    
    char *buffer = calloc(50, sizeof(char));

    // "subsetList" contains the numbers inside the set
    int *subsetList = calloc(1000, sizeof(int));


    // Reading from file
    fp = fopen("input.txt", "r");
    fscanf(fp, "%d\n", &sum);

    printf("k = %d\n",sum);

    printf("Set: { ");
    while(1){     
        if (fscanf(fp, "%d\n", &val) == -1) {
            break;
        }
        subsetList[set_size] = val;
        printf("%d ", subsetList[set_size]);
        set_size++;
    }
    printf("}\n");


    // Creating the 2D array                                                    r
    int **matrix = malloc((set_size+1) * sizeof(int*));   // matrix -------->   0 -> [1,2,3,4]
    for(int row = 0; row < set_size+1; row++) {                             //  1 -> [1,2,3,4]
        matrix[row] = calloc(sum+1, sizeof(int));                           //  2 -> [1,2,3,4]
    }                                                                       //  3 -> [1,2,3,4]

    // Solving for each subproblem
    for(int row = 0; row < set_size; row++) {
        matrix[row][0] = 1;
        for(int col = 1; col < min(get_sum_from_bounds(row, subsetList)+1, sum+1); col++) {
            matrix[row][col] = fill_cell(matrix, subsetList, row, col);
        }

    }


    displayTable(matrix, subsetList, set_size, sum+1);
    checkIfHasSubset(matrix, subsetList, set_size-1, sum);
    return 0;
}