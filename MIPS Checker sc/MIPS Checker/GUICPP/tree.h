#include <string>
using namespace std;
using namespace System;

std::string formulaOutput = " ";

std::string printFormula(struct treeNode *currentTreeNode);

struct treeNode {
	char element;
	struct treeNode *leftSon;
	struct treeNode *rightSon;
	struct treeNode *father;
	char code;	// '0' = for all registers
	int level;
};

void openFile(struct treeNode *formulaToCheck[], int *numFormula, char formulaPath[]){
	char formula[MAXFORMULA];
	FILE *fp;
    fp=fopen(formulaPath, "r");
	
	if(!fp) {
		System::Windows::Forms::MessageBox::Show("FORMULA FILE NOT FOUND");//error: file not found
	}
	else { 
		while(fgets(formula,MAXFORMULA,fp)!=NULL) {
			struct treeNode *rootFormula=(struct treeNode *)malloc(sizeof(struct treeNode));
			int index = 1,numSubf = 0;
			rootFormula->code = formula[0];
			rootFormula->father = NULL;
			readFormula(rootFormula,formula,&index,0);
			formulaToCheck[*numFormula] = rootFormula;
			(*numFormula)++;
		}
	}
}

void manualFormula(struct treeNode *formulaToCheck[], int *numFormula, const char TheFormula[]){
	char formula[MAXFORMULA];
	strcpy(formula,TheFormula);	
	struct treeNode *rootFormula=(struct treeNode *)malloc(sizeof(struct treeNode));
	int index = 1,numSubf = 0;
	rootFormula->code = formula[0];
	rootFormula->father = NULL;
	readFormula(rootFormula,formula,&index,0);
	formulaToCheck[*numFormula] = rootFormula;
	(*numFormula)++;
}

void readFormula(struct treeNode *currentTreeNode, char formula[], int *index, int level){
	// Binary: A = implication, B = conjunction, C = disjunction
	// Unary: D = negation, E = AF, F = AG, G = EF, H = EG, I = AX, J = EX
	// Binary; K = AU, L = EU
	currentTreeNode->level = level;
    if((formula[*index]>='a')&&(formula[*index]<='z')){
        currentTreeNode->element = formula[*index];
        currentTreeNode->rightSon = NULL;        
        currentTreeNode->leftSon = NULL;
    }
	else if((formula[*index]=='A')||(formula[*index]=='B')||(formula[*index]=='C')||(formula[*index]=='K')||(formula[*index]=='L')){
        currentTreeNode->element = formula[*index];
        struct treeNode *ls = (struct treeNode *)malloc(sizeof(struct treeNode));
		(*index)++;
        readFormula(ls,formula,index,level+1);
        currentTreeNode->leftSon = ls;
		ls->father = currentTreeNode;
        struct treeNode *rs = (struct treeNode *)malloc(sizeof(struct treeNode));  
		(*index)++;
        readFormula(rs,formula,index,level+1);
        currentTreeNode->rightSon = rs;
		rs->father = currentTreeNode;
    } 
	else if((formula[*index]=='D')||(formula[*index]=='E')||(formula[*index]=='F')||(formula[*index]=='G')||(formula[*index]=='H')||(formula[*index]=='I')||(formula[*index]=='J')){
        currentTreeNode->element = formula[*index];
        struct treeNode *s = (struct treeNode *)malloc(sizeof(struct treeNode));
		(*index)++;
        readFormula(s,formula,index,level+1);
        currentTreeNode->leftSon = s;
        currentTreeNode->rightSon = NULL;
		s->father = currentTreeNode;
    }
}

void buildFormulaOutput(string part){
	formulaOutput += part;
}


std::string printFormula(struct treeNode *currentTreeNode){

    if (currentTreeNode->element=='A'){
        buildFormulaOutput("( ");
        printFormula(currentTreeNode->leftSon);
        buildFormulaOutput(" -> ");
        printFormula(currentTreeNode->rightSon);
        buildFormulaOutput(" )");
    } 
	else if (currentTreeNode->element=='B'){
        buildFormulaOutput("( ");
        printFormula(currentTreeNode->leftSon);
        buildFormulaOutput(" And ");
        printFormula(currentTreeNode->rightSon);
        buildFormulaOutput(" )");
    } 
	else if (currentTreeNode->element=='C'){
        buildFormulaOutput("( ");
        printFormula(currentTreeNode->leftSon);
        buildFormulaOutput(" Or ");
        printFormula(currentTreeNode->rightSon);
        buildFormulaOutput(" )");
    }  
	else if (currentTreeNode->element=='D'){
        buildFormulaOutput("Not ");
        buildFormulaOutput("( ");
        printFormula(currentTreeNode->leftSon);
        buildFormulaOutput(" )");
    }
	else if(currentTreeNode->element=='E'){
		buildFormulaOutput("AF ");
		buildFormulaOutput("( ");
		printFormula(currentTreeNode->leftSon);
		buildFormulaOutput(" )");
	}
	else if(currentTreeNode->element=='F'){
		buildFormulaOutput("AG ");
		buildFormulaOutput("( ");
		printFormula(currentTreeNode->leftSon);
		buildFormulaOutput(" )");
	}
	else if(currentTreeNode->element=='G'){
		buildFormulaOutput("EF ");
		buildFormulaOutput("( ");
		printFormula(currentTreeNode->leftSon);
		buildFormulaOutput(" )");
	}
	else if(currentTreeNode->element=='H'){
		buildFormulaOutput("EG ");
		buildFormulaOutput("( ");
		printFormula(currentTreeNode->leftSon);
		buildFormulaOutput(" )");
	}
	else if(currentTreeNode->element=='I'){
		buildFormulaOutput("AX ");
		buildFormulaOutput("( ");
		printFormula(currentTreeNode->leftSon);
		buildFormulaOutput(" )");
	}
	else if(currentTreeNode->element=='J'){
		buildFormulaOutput("EX ");
		buildFormulaOutput("( ");
		printFormula(currentTreeNode->leftSon);
		buildFormulaOutput(" )");
	}
	else if(currentTreeNode->element=='K'){
        buildFormulaOutput("( ");
        printFormula(currentTreeNode->leftSon);
        buildFormulaOutput(" AU ");
        printFormula(currentTreeNode->rightSon);
        buildFormulaOutput(" )");
    }
	else if(currentTreeNode->element=='L'){
        buildFormulaOutput("( ");
        printFormula(currentTreeNode->leftSon);
        buildFormulaOutput(" EU ");
        printFormula(currentTreeNode->rightSon);
        buildFormulaOutput(" )");
    }
	else {
		char fix[2];
		fix[0] = currentTreeNode->element;
		fix[1] = '\0';
		buildFormulaOutput((string)fix);
	}

	return (formulaOutput);
}

