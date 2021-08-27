struct treeNode {
	char element;
	struct treeNode *leftSon;
	struct treeNode *rightSon;
	struct treeNode *father;
	char code;	// '0' = for all registers
	int level;
};

void openFile(struct treeNode *formulaToCheck[], int *numFormula){
	char formula[MAXFORMULA];
	FILE *fp;
    fp=fopen("formula.txt", "r");
    if(!fp) printf("File Not Found!\n");
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
        printf("Not ");
        printf("(");
        printFormula(currentTreeNode->leftSon);
        printf(")");
    }
	else if(currentTreeNode->element=='E'){
		printf("AF ");
		printf("(");
		printFormula(currentTreeNode->leftSon);
		printf(")");
	}
	else if(currentTreeNode->element=='F'){
		printf("AG ");
		printf("(");
		printFormula(currentTreeNode->leftSon);
		printf(")");
	}
	else if(currentTreeNode->element=='G'){
		printf("EF ");
		printf("(");
		printFormula(currentTreeNode->leftSon);
		printf(")");
	}
	else if(currentTreeNode->element=='H'){
		printf("EG ");
		printf("(");
		printFormula(currentTreeNode->leftSon);
		printf(")");
	}
	else if(currentTreeNode->element=='I'){
		printf("AX ");
		printf("(");
		printFormula(currentTreeNode->leftSon);
		printf(")");
	}
	else if(currentTreeNode->element=='J'){
		printf("EX ");
		printf("(");
		printFormula(currentTreeNode->leftSon);
		printf(")");
	}
	else if(currentTreeNode->element=='K'){
        printf("(");
        printFormula(currentTreeNode->leftSon);
        printf(" AU ");
        printFormula(currentTreeNode->rightSon);
        printf(")");
    }
	else if(currentTreeNode->element=='L'){
        printf("(");
        printFormula(currentTreeNode->leftSon);
        printf(" EU ");
        printFormula(currentTreeNode->rightSon);
        printf(")");
    }
	else printf("%c",currentTreeNode->element);
}

void printLeaves(struct treeNode *subFormula[], int numSubf){
	for(int i=0;i<numSubf;i++) printf("%c ",subFormula[i]->element);
}
