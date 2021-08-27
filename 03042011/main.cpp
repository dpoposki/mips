/* 
 * File:   main.cpp
 * Author: LG
 *
 * Created on 16 de marzo de 2011, 14:42
 */

#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include "clean.h"
#include "structf.h"
#define MAXLINE 250

using namespace std;

int main() {
	struct node *root=(struct node *)malloc(sizeof(struct node));
	root->prev=NULL;
	FILE *fp;
    fp=fopen("prime.txt", "r");
    if (!fp) printf("File Not Found!\n");
	else readFile(fp,root);
	fclose(fp);
	moveThrough(root,root);
	linkNodes(root);
	printFile(root);
	system("pause");
    return 0;
}
