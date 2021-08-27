#define MAXFORMULA 100

void readFormula(struct treeNode *currentTreeNode, char formula[], int *index);
void printFormula(struct treeNode *currentTreeNode);

struct treeNode {
	char element;
	struct treeNode *leftSon;
	struct treeNode *rightSon;
};

void openFile(){
	char formula[MAXFORMULA];
	FILE *fp;
    fp=fopen("formula.txt", "r");
    if(!fp) printf("File Not Found!\n");
	else { 
		while(fgets(formula,MAXFORMULA,fp)!=NULL) {
			struct treeNode *rootFormula=(struct treeNode *)malloc(sizeof(struct treeNode));
			int index=0;
			readFormula(rootFormula,formula,&index);
			printFormula(rootFormula);
			printf("\n");
		}
	}
}

void readFormula(struct treeNode *currentTreeNode, char formula[], int *index){
	// A = implication, B = conjunction, C = disjunction, D = negation
	// E = AF, F = AG, G = EF, H = EG
	// I = AU, J = EU, K = AS, L = ES
    if((formula[*index]>='a')&&(formula[*index]<='z')){
        currentTreeNode->element = formula[*index];
        currentTreeNode->rightSon = NULL;        
        currentTreeNode->leftSon = NULL;
    }
	else if((formula[*index]=='A')||(formula[*index]=='B')||(formula[*index]=='C')||(formula[*index]=='I')||(formula[*index]=='J')||(formula[*index]=='K')||(formula[*index]=='L')){
        currentTreeNode->element = formula[*index];
        struct treeNode *ls = (struct treeNode *)malloc(sizeof(struct treeNode));
		(*index)++;
        readFormula(ls,formula,index);
        currentTreeNode->leftSon = ls;
        struct treeNode *rs = (struct treeNode *)malloc(sizeof(struct treeNode));  
		(*index)++;
        readFormula(rs,formula,index);
        currentTreeNode->rightSon = rs;
    }
	else if((formula[*index]=='D')||(formula[*index]=='E')||(formula[*index]=='F')||(formula[*index]=='G')||(formula[*index]=='H')){
        currentTreeNode->element = formula[*index];
        struct treeNode *s = (struct treeNode *)malloc(sizeof(struct treeNode));
		(*index)++;
        readFormula(s,formula,index);
        currentTreeNode->leftSon = s;
        currentTreeNode->rightSon = NULL;
    }
}

void printFormula(struct treeNode *currentTreeNode){
    if (currentTreeNode->element=='A'){
        printf("(");
        printFormula(currentTreeNode->leftSon);
        printf(" -> ");
        printFormula(currentTreeNode->rightSon);
        printf(")");
    } 
	else if (currentTreeNode->element=='B'){
        printf("(");
        printFormula(currentTreeNode->leftSon);
        printf(" And ");
        printFormula(currentTreeNode->rightSon);
        printf(")");
    } 
	else if (currentTreeNode->element=='C'){
        printf("(");
        printFormula(currentTreeNode->leftSon);
        printf(" Or ");
        printFormula(currentTreeNode->rightSon);
        printf(")");
    }  
	else if (currentTreeNode->element=='D'){
        printf(" Not ");
        printf("(");
        printFormula(currentTreeNode->leftSon);
        printf(")");
    }
	else printf("%c",currentTreeNode->element);
}
