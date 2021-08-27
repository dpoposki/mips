/* 
 * File:   main.cpp
 * Author: LG
 *
 * Created on 16 de marzo de 2011, 14:42
 */

#include "inc.h"

int main(){
	struct node *root=(struct node *)malloc(sizeof(struct node));		// Allocate memory for a new node
	struct treeNode *formulaToCheck[MAXCHECK];
	int numFormula = 0, i;
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
		int temp = checkFormula(root,formulaToCheck[i]);
        if(temp != -1){
           printf("Your program is unsafe for ");
           printFormula(formulaToCheck[i]);
           printf(" for register %d\n",temp);
           system("pause");
        }
	}
    //printFile(root);system("pause");
    return 0;
}
