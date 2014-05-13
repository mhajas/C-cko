/*
 * Implementacny test IB002 - uloha 1. (12 bodov)
 *
 * Vyplnte nasledujuce udaje:
 * Meno:
 * UCO:
 * Skupina(v ktorej ste zapisany):
 */

// Zadani:
//
// Naimplementujte metodu 'isValid', ktora overi, ci je dany strom ternarnym vyhladavacim stromom.
// Takyto strom ma oproti binarnemu vyhladavaciemu stromu 2 hodnoty v kazdom uzle namiesto 1 hodnoty (obidve su vzdy vyplnene).
// Kriterium vyhladavacieho stromu je potom pozmenene nasledovne: leftSubtree <= key1 <= middleSubtree <= key2 <= rightSubtree.
// Strom moze obsahovat kluce z intervalu <MINIMUM_TREE_KEY, MAXIMUM_TREE_KEY>.
// [12 bodov]

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
int nodeValue1;             //! value1, > values in leftSubtree, < values in middleSubtree
int nodeValue2;             //! value2, > values in middleSubtree, < values in rightSubtree
struct Node* leftSubtree;
struct Node* middleSubtree;
struct Node* rightSubtree;
} Node;

//TO DO
int isValid(Node* tree, int minimumAllowedValue, int maximumAllowedValue) {
    if(tree==NULL){
        return 1;
    }
    if(tree->nodeValue1 < minimumAllowedValue || tree->nodeValue1 > maximumAllowedValue){
        return 0;
    }
    if(tree->nodeValue2 < minimumAllowedValue || tree->nodeValue2 > maximumAllowedValue){
        return 0;
    }

    if(tree->leftSubtree != NULL && (tree->leftSubtree->nodeValue1 > tree->nodeValue1 || tree->leftSubtree->nodeValue2 > tree->nodeValue1)){
        return 0;
    }

    if(tree->middleSubtree != NULL){
        if(tree->middleSubtree->nodeValue1 < tree->nodeValue1 || tree->middleSubtree->nodeValue2 < tree->nodeValue1){
            return 0;
        }
        if(tree->middleSubtree->nodeValue1 > tree->nodeValue2 || tree->middleSubtree->nodeValue2 > tree->nodeValue2){
            return 0;
        }
    }

    if(tree->rightSubtree != NULL && (tree->rightSubtree->nodeValue1 < tree->nodeValue2 || tree->rightSubtree->nodeValue2 < tree->nodeValue2)){
        return 0;
    }

    if(!isValid(tree->leftSubtree,minimumAllowedValue,tree->nodeValue1)){
        return 0;
    }

    if(!isValid(tree->middleSubtree,tree->nodeValue1,tree->nodeValue2)){
        return 0;
    }

    if(!isValid(tree->rightSubtree,tree->nodeValue2,maximumAllowedValue)){
        return 0;
    }
    return 1;
}

int main(void)
{
int MIN_VAL = -100;
int MAX_VAL = 100;

printf("IB002 - implementation test 1\n");

Node node5 = { 3, 4, NULL, NULL, NULL };
Node node2 = { 0, 2, NULL, NULL, &node5 };
Node node3 = { 6, 9, NULL, NULL, NULL };
Node node4 = { 11, 15, NULL, NULL, NULL };
Node node1 = { 5, 10, &node2, &node3, &node4 };

Node node10 = { 10, 10, NULL, NULL, NULL};
Node node9 = { 10, 11, NULL, &node10, NULL};
Node node8 = { 8, 10, NULL, NULL, NULL};
Node node7 = { 6, 7, NULL, NULL, NULL};
Node node6 = { 7, 10, &node7, &node8, &node9};

Node node21 = { 17, 19, NULL, NULL, NULL};
Node node20 = { 21, 22, NULL, NULL, NULL};
Node node19 = { 14, 15, NULL, NULL, NULL};
Node node18 = { 16, 20, &node19, &node21, &node20};
Node node17 = { 8, 11, NULL, NULL, NULL};
Node node16 = { 0, 3, NULL, NULL, NULL};
Node node15 = { 7, 13, &node16, &node17, &node18};

Node node30 = { 17, 19, NULL, NULL, NULL};
Node node29 = { 1, 2, NULL, NULL, NULL};
Node node28 = { 14, 15, NULL, NULL, NULL};
Node node27 = { 16, 20, &node28, NULL, &node30};
Node node26 = { 8, 11, NULL, NULL, NULL};
Node node25 = { 0, 3, NULL, &node29, NULL};
Node node24 = { 7, 13, &node25, &node26, &node27};

Node node40 = { 5, 5, NULL, NULL, NULL};

Node node47 = { 10, 11, NULL, NULL, NULL};
Node node48 = { 10, 11, &node47, NULL, NULL};
Node node49 = { 8, 10, NULL, NULL, NULL};
Node node50 = { 6, 7, NULL, NULL, NULL};
Node node51 = { 7, 10, &node50, &node49, &node48};

Node node57 = { 10, 11, NULL, NULL, NULL};
Node node58 = { 10, 11, NULL, &node57, NULL};
Node node59 = { 8, 10, NULL, NULL, NULL};
Node node60 = { 6, 7, NULL, NULL, NULL};
Node node61 = { 7, 10, &node60, &node59, &node58};

Node node75 = { 15, 19, NULL, NULL, NULL};
Node node74 = { 1, 14, NULL, NULL, &node75};
Node node73 = { 1, 14, NULL, &node74, NULL};
Node node72 = { 1, 14, NULL, &node73, NULL};
Node node71 = { 15, 20, &node72, NULL, NULL};

Node node85 = { 5, 7, NULL, NULL, NULL};
Node node84 = { 1, 4, NULL, NULL, &node85};
Node node83 = { 1, 8, NULL, &node84, NULL};
Node node82 = { 1, 12, NULL, &node83, NULL};
Node node81 = { 15, 20, &node82, NULL, NULL};

int points = 0;

int valid = isValid(&node1, MIN_VAL, MAX_VAL);
printf("Tree is valid: %d, should be 1\n",valid); // 1
if( valid ) points++;

valid = isValid(&node6, MIN_VAL, MAX_VAL);
printf("Tree is valid: %d, should be 1\n",valid); // 1
if( valid ) points++;

valid = isValid(&node15, MIN_VAL, MAX_VAL);
printf("Tree is valid: %d, should be 1\n",valid); // 1
if( valid ) points++;

valid = isValid(&node24, MIN_VAL, MAX_VAL);
printf("Tree is valid: %d, should be 0\n",valid);
if( !valid ) points++;

valid = isValid(&node40, MIN_VAL, MAX_VAL);
printf("Tree is valid: %d, should be 1\n",valid); // 1
if( valid ) points++;

valid = isValid(NULL, MIN_VAL, MAX_VAL);
printf("Tree is valid: %d, should be 1\n",valid); // 1
if( valid ) points++;

valid = isValid(&node51, MIN_VAL, MAX_VAL);
printf("Tree is valid: %d, should be 0\n",valid);
if( !valid ) points++;

valid = isValid(&node61, MIN_VAL, MAX_VAL);
printf("Tree is valid: %d, should be 1\n",valid); // 1
if( valid ) points++;

valid = isValid(&node71, MIN_VAL, MAX_VAL);
printf("Tree is valid: %d, should be 0\n",valid);
if( !valid ) points++;

valid = isValid(&node81, MIN_VAL, MAX_VAL);
printf("Tree is valid: %d, should be 1\n",valid); // 1
if( valid ) points++;

printf("Total correct answers: %d, should be 10\n", points); // 1

return 0;
}
