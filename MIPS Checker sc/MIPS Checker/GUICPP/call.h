#include "inc.h"
#include <stdio.h>
#include <string>
#include <cstring>
using namespace System::Runtime::InteropServices; //Jas go dodadov ova zaradi Marshal, konverzija od System::String vo char[]


string func(String ^ ProgramPath, String ^ TheFormula){
	char* cProgramPath = (char*)(void*)Marshal::StringToHGlobalAnsi(ProgramPath).ToPointer();
	char* cTheFormula = (char*)(void*)Marshal::StringToHGlobalAnsi(TheFormula).ToPointer();
	string outputString = "";
	struct node *root=(struct node *)malloc(sizeof(struct node));		// Allocate memory for a new node
	struct treeNode *formulaToCheck[MAXCHECK];
	int numFormula = 0, i, temp, error[MAXREG];
	setNull(root);
	strcpy(root->line,"First line");
	FILE *fp;
	fp=fopen(cProgramPath, "r");
	if (!fp) {

		System::Windows::Forms::MessageBox::Show("MIPS PROGRAM FILE NOT FOUND");
		exit(15);//error exit, file not found
	}
	else readFile(fp,root);		// Read the file and store it in the data structures
	fclose(fp);
	moveThrough(root,root);
	linkNodes(root);
	manualFormula(formulaToCheck,&numFormula,cTheFormula); //Calling manualFormula instead of openFile
		temp = checkFormula(root,formulaToCheck[i],error);
        while(temp){
			formulaOutput = " ";
			outputString += (string)"Unsafe for [" + (string)printFormula(formulaToCheck[i]) + (string)" ] for register " + (string)codeToRegister(error[temp-1])+(string)".\r\n";
		    temp--;
        }
	if (outputString == "") outputString = "Your program satisfies all formulas.\r\n";

    return outputString;
}