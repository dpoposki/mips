/* 
 * File:   main.cpp
 * Author: LG
 *
 * Created on 16 de marzo de 2011, 14:42
 */

#include <stdlib.h>		// For malloc function
#include <stdio.h>
#include <string.h>
#include "clean.h"
#include "structf.h"
#define MAXLINE 250

using namespace std;

int main() {
	struct node *root=(struct node *)malloc(sizeof(struct node));		// Allocate memory for a new node
	setNull(root);
	strcpy(root->line,"First line");
	FILE *fp;
    fp=fopen("div.txt", "r");
    if (!fp) printf("File Not Found!\n");
	else readFile(fp,root);		// Read the file and store it in the data structures
	fclose(fp);
	moveThrough(root,root);
	linkNodes(root);
	printFile(root);
	system("pause");
    return 0;
}
