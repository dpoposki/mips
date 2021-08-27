#define MAXLINE 250
#define MAXPAST 10
#define MAXFORMULA 100
#define MAXCHECK 10
#define MAXREG 28

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
int checkFormula(struct node *rootStruct, struct treeNode *rootFormula);
void findLevel(struct treeNode *subFormula[], struct treeNode *currentNodeFormula, int *numSubf, int level);
int checkSingleFormula(struct node *rootStruct, struct treeNode *rootFormula, int instance);
int findMaxLevel(struct treeNode *currentNodeFormula);
void linkNode(struct treeNode *currentNodeFormula, struct node *rootStruct, int instance);
void cleanStruct(struct node *currentNode);
int findEF(struct node *currentNode, struct treeNode *currentNodeFormula);
int findAF(struct node *currentNode, struct treeNode *currentNodeFormula);
int findEU(struct node *currentNode, struct treeNode *currentNodeFormulaP, struct treeNode *currentNodeFormulaQ);
int findEG(struct node *currentNode, struct treeNode *currentNodeFormula);
int findAG(struct node *currentNode, struct treeNode *currentNodeFormula);

// tree.h function declarations
void openFile(struct treeNode *formulaToCheck, int *numFormula);
void readFormula(struct treeNode *currentTreeNode, char formula[], int *index, int level);
void printFormula(struct treeNode *currentTreeNode);

// clean.h function declarations
void cleanString(char buf[]);
void extractLabel(char line[], int instruction);

#include "clean.h"
#include "structf.h"
#include "tree.h"
#include "check.h"
