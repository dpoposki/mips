#include "inc.h"
#include <string>

string func(string ProgramPath, string TheFormula){

	string outputString = "";
	struct node *root=(struct node *)malloc(sizeof(struct node));		// Allocate memory for a new node
	struct treeNode *formulaToCheck[MAXCHECK];
	int numFormula = 0, i, temp, error[MAXREG];
	setNull(root);
	strcpy(root->line,"First line");
	FILE *fp;
	fp=fopen(ProgramPath, "r");
    if (!fp) MessageBox(NULL, L"PROGRAM FILE NOT FOUND", L"ERROR", MB_OK);
	else readFile(fp,root);		// Read the file and store it in the data structures
	fclose(fp);
	moveThrough(root,root);
	linkNodes(root);
	manualFormula(formulaToCheck,&numFormula,TheFormula); //Calling manualFormula instead of openFile
	
	for(i=0;i<numFormula;i++) {
		temp = checkFormula(root,formulaToCheck[i],error);
        while(temp){
			formulaOutput = " ";
			outputString += (string)"Unsafe for [" + (string)printFormula(formulaToCheck[i]) + (string)" ] for register " + (string)codeToRegister(error[temp-1])+(string)".%";
		   temp--;
        }
	}
	if (outputString == "") outputString = "Your program satisfies all formulas.%";
	const char *sOut;
	sOut = outputString.c_str();
	BSTR output;
	output = SysAllocStringByteLen(sOut, strlen(sOut));
    return output;
}