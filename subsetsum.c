#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Subset Subset;
struct Subset {
    short int *numbers;  
    int sum;
    Subset *next;                    
};

int checkIfTwoArraysAreEqual(short int *a, short int *b, int size) {
    for(int i = 0; i < size; i++) {
        if (a[i] != b[i]) return 0;
    }
    return 1;
}

int isThisSubsetVisited(Subset* visitedSubsets, Subset* subsetInQuestion, int size) {
    Subset *temp = visitedSubsets;
    while(temp != NULL) {
        if (checkIfTwoArraysAreEqual(temp->numbers, subsetInQuestion->numbers, size)) {
            return 1;
        } 
        temp = temp->next;
    }
    return 0;
}

void subsetSum(int *sampleSet, int target, int number_of_inputs) {
    int noOfSubsets = 0;
    Subset *ptrTopOfStack = NULL;
    Subset *visitedSubsets = NULL;

    // initialize first entry
    Subset *init = calloc(1, sizeof(Subset));
    short int *init_array = calloc(number_of_inputs, sizeof(short int));
    init->numbers = init_array;
    init->sum = 0;
    init->next = NULL;

    ptrTopOfStack = init;

    while(ptrTopOfStack != NULL) {
        Subset *currentSubset = ptrTopOfStack;
        ptrTopOfStack = ptrTopOfStack->next;

        // Check if the current subset sum is equal to the target
        if (currentSubset->sum == target) {
            noOfSubsets++;
            printf("{ ");
            for(int i = 0 ; i < number_of_inputs; i++) {
                if (currentSubset->numbers[i] == 0) continue;
                printf("%hd ", currentSubset->numbers[i]);
            }
            printf("}\n");
        }

        // Generate nodes by including each unprocessed element
        for(int i = 0; i < number_of_inputs; i++) {
            if(currentSubset->numbers[i] == 0 && target >= (currentSubset->sum + sampleSet[i])) {

                // Create a new subset
                Subset *new_node = calloc(1, sizeof(Subset));
                short int *new_array = calloc(number_of_inputs, sizeof(short int));
                memcpy(new_array, currentSubset->numbers, sizeof(short int) * number_of_inputs);
                new_array[i] = sampleSet[i];
                new_node->numbers = new_array;
                new_node->sum = currentSubset->sum + sampleSet[i];
                new_node->next = NULL;

                // Check if the new subset has already been visited
                if (!isThisSubsetVisited(visitedSubsets, new_node, number_of_inputs)) {
                    // Add new subset to the top of the stack
                    new_node->next = ptrTopOfStack;
                    ptrTopOfStack = new_node;
                } else {
                    // free the node
                    free(new_node->numbers);
                    free(new_node);
                }
            }
        }

        // Add current subset to the visited list
        currentSubset->next = visitedSubsets;
        visitedSubsets = currentSubset;
    }
    printf("Total number of valid subsets: %d\n",noOfSubsets);

    while (visitedSubsets != NULL) {
        Subset *temp = visitedSubsets;
        visitedSubsets = visitedSubsets->next;
        free(temp->numbers);
        free(temp);
    }
}

void main() { 
    // Reading the file
    FILE *fp;
    fp = fopen("input.in", "r");
    if (!fp) return;
    int iteration = 0;              // number of times this code has to iterate

    fscanf(fp, "%d\n", &iteration);

    

    

    for(int i = 0; i < iteration; i++) {
        char buffer[100];
        int input_set[100];
        int input_size = 0;
        int target;

        fscanf(fp, "%d", &target);
        printf("Target: %d\n",target);
        while(fgets(buffer, sizeof(buffer), fp)){ 
            printf("\nLine: %s\n", buffer);
        }
        
        // subsetSum(input_set, target, input_size);
    }

    // int number_of_inputs = inp;
    // int sampleSet[inp] = {1, 3, 5, 7, 2, 9, 11};
    // int target = 23;
}
