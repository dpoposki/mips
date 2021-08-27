#define MAXLINE 250
#define MAXPAST 10
#define MAXFORMULA 100
#define MAXCHECK 10

#include <stdlib.h>		// For malloc function
#include <stdio.h>
#include <string.h>
#include <ctype.h>		// isspace is a function from this library

// structf.h function declarations
int recognizeCommand(char instr[]);
void moveThrough(struct node *root, struct node *currentNode);
struct node *findLabel(struct node *root, struct node *currentNode);
void setNull(struct node *currentNode);
int recognizeRegister(char registerID[]);
void fillRegisterArrays(struct node *currentNode);

// check.h function declarations
void checkFormula(struct node *rootStruct, struct treeNode *rootFormula);
void findLevel(struct treeNode *subFormula[], struct treeNode *currentNodeFormula, int *numSubf, int level);
int findMaxLevel(struct treeNode *currentNodeFormula);
void linkNode(struct treeNode *currentNodeFormula, struct node *rootStruct, int instance);

// tree.h function declarations
void openFile(struct treeNode *formulaToCheck, int *numFormula);
void readFormula(struct treeNode *currentTreeNode, char formula[], int *index, int level);
void printFormula(struct treeNode *currentTreeNode);
void printLeaves(struct treeNode *leaves[], int numLeaves);

// clean.h function declarations
void cleanString(char buf[]);
void extractLabel(char line[], int instruction);

#include "clean.h"
#include "structf.h"
#include "tree.h"
#include "check.h"
