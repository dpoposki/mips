void checkFormula(struct node *rootStruct, struct treeNode *rootFormula){
	if(rootFormula->code == '0'){
		for(int i=0;i<32;i++){
			
		}
	}
}

void findLevel(struct treeNode *subFormula[], struct treeNode *currentNodeFormula, int *numSubf, int level){
	if(currentNodeFormula->level == level){
		subFormula[*numSubf] = currentNodeFormula;
		(*numSubf)++;
	}
	if(currentNodeFormula->leftSon != NULL) findLevel(subFormula,currentNodeFormula->leftSon,numSubf,level);
	if(currentNodeFormula->rightSon != NULL) findLevel(subFormula,currentNodeFormula->rightSon,numSubf,level);
}

void checkSingleFormula(struct node *rootStruct, struct treeNode *rootFormula, int instance){
	struct treeNode *subFormula[MAXFORMULA];
	int numSubf, maxLevel;
	maxLevel = findMaxLevel(rootFormula);
	for(int i = maxLevel;i>0;i--){
		numSubf = 0;
		findLevel(subFormula,rootFormula,&numSubf,i);
		for(int j = 0;i<numSubf;j++){
			linkNode(subFormula[j],rootStruct,instance);
		}
	}
}

int findMaxLevel(struct treeNode *currentNodeFormula){
	if(currentNodeFormula->leftSon == NULL && currentNodeFormula->rightSon == NULL){
		return currentNodeFormula->level;
	}
	if(currentNodeFormula->rightSon){
		if(findMaxLevel(currentNodeFormula->rightSon) > currentNodeFormula->level) return findMaxLevel(currentNodeFormula->rightSon);
		else return currentNodeFormula->level;
	}
	if(currentNodeFormula->leftSon){
		if(findMaxLevel(currentNodeFormula->leftSon) > currentNodeFormula->level) return findMaxLevel(currentNodeFormula->leftSon);
		else return currentNodeFormula->level;
	}
}

void linkNode(struct treeNode *currentNodeFormula, struct node *rootStruct, int instance){
	struct node *currentNode = (struct node *)malloc(sizeof(struct node));
	currentNode = rootStruct;
	while(currentNode){
		if(currentNodeFormula->element >= 'a' && currentNodeFormula->element <= 'z'){
			if(currentNodeFormula->element == 'a'){
				if(currentNode->accessed[instance] == 1) currentNode->trueSubf[(currentNode->numSubf)++] = currentNodeFormula;
			}
			if(currentNodeFormula->element == 'i'){
				if(currentNode->valueSet[instance] == 1) currentNode->trueSubf[(currentNode->numSubf)++] = currentNodeFormula;
			}
		}
		if(currentNode->next != NULL) currentNode = currentNode->next;
		else currentNode = NULL;
	}
}
