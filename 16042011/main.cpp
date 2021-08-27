/*
 * MIPS Checker
 * Version: 1.0 beta
 *
 * Authors: Darko Poposki, Risto Petroski, Dimitar Stojkoski, Guido Sciavicco
 *
 */

#include "inc.h"

int main(){
	struct node *root=(struct node *)malloc(sizeof(struct node));		// Allocate memory for a new node
	struct treeNode *formulaToCheck[MAXCHECK];
	int numFormula = 0, i, temp, error[MAXREG];
	setNull(root);
	strcpy(root->line,"First line");
	FILE *fp;
    fp=fopen("test.txt", "r");
    if (!fp) printf("File Not Found!\n");
	else readFile(fp,root);		// Read the file and store it in the data structures
	fclose(fp);
	moveThrough(root,root);
	linkNodes(root);
	//printFile(root);system("pause");
	openFile(formulaToCheck,&numFormula);
	for(i=0;i<numFormula;i++) {
		temp = checkFormula(root,formulaToCheck[i],error);
        while(temp){
           printf("Your program is unsafe for ");
           printFormula(formulaToCheck[i]);
           printf(" for register %d\n",error[temp-1]);
		   temp--;
        }
	}
    //printFile(root);
	system("pause");
    return 0;
}
