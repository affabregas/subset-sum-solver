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
        if (a[i] == b[i]) return 0;
    }
    return 1;
}

int displayArrayOfSubset(Subset *s, int size) {
    printf("Curr subset: ");
    for(int i = 0; i < size; i++) {
        printf("%hd ", s->numbers[i]);
    }
    printf("\n");
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

#define inp 5
void main() { 
    int number_of_inputs = inp;
    int sampleSet[inp] = {1,2,3,4,5};
    int target = 5;

    // initialize first entry
    Subset *ptrTopOfStack = NULL;
    Subset *visitedSubsets = NULL;

    Subset *init = calloc(1, sizeof(Subset));
    short int *init_array = calloc(number_of_inputs, sizeof(short int));
    init->numbers = init_array;

    ptrTopOfStack = init;

    int NumberOfValidSubsets = 0;

    while(ptrTopOfStack != NULL) {
        int isTopOfStackChanged = 0;
        Subset *currentSubset = ptrTopOfStack;

        // check if already visited
        if (((currentSubset->sum) > target) && isThisSubsetVisited(visitedSubsets, currentSubset, number_of_inputs)) {
            ptrTopOfStack = ptrTopOfStack->next;
            continue;
        }

        // check if already equal
        if (target == currentSubset->sum) {
            printf("{ ");
            for(int i = 0 ; i < number_of_inputs; i++) {
                if (currentSubset->numbers[i] == 0) continue;
                printf("%hd ",currentSubset->numbers[i]);
            }
            printf("}\n");
        }

        // generate nodes 
        for(int i = 0; i < number_of_inputs; i++) {
            if(currentSubset->numbers[i] == 0 && target >= (currentSubset->sum + sampleSet[i])) {

                // creating a new node and copying the array of the topofstack subset
                Subset *new_node = calloc(1, sizeof(Subset));
                short int *init_array = calloc(number_of_inputs, sizeof(short int));
                new_node->numbers = malloc(number_of_inputs * sizeof(short int));
                memcpy(new_node->numbers, currentSubset->numbers, sizeof(short int) * number_of_inputs);
                new_node->numbers[i] = sampleSet[i];
                new_node->sum = currentSubset->sum + sampleSet[i];
                
                // check if already existing in visited OR if the sum is already greater than target
                // if not, add to stack
                if ((new_node->sum) > target) {
                    if (isThisSubsetVisited(visitedSubsets, new_node, number_of_inputs)) free(new_node);
                    continue;
                } else {
                    if(currentSubset == ptrTopOfStack) {
                        new_node->next = ptrTopOfStack->next;
                        ptrTopOfStack = new_node;
                    } else {
                        new_node->next = ptrTopOfStack;
                        ptrTopOfStack = new_node;
                    }
                    isTopOfStackChanged = 1;
                }
            }
        } 

        // add this node into visited
        if(!isTopOfStackChanged) ptrTopOfStack = ptrTopOfStack->next;
        currentSubset->next = visitedSubsets;
        visitedSubsets = currentSubset; 
    }
    
}

