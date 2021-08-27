void checkFormula(struct node *rootStruct, struct treeNode *rootFormula){
	if(rootFormula->code == '0'){
		for(int i=0;i<MAXREG;i++){
			checkSingleFormula(rootStruct,rootFormula,i);
			printFile(rootStruct);
			system("pause");
			cleanStruct(rootStruct);
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
	for(int i = maxLevel;i>=0;i--){
		numSubf = 0;
		findLevel(subFormula,rootFormula,&numSubf,i);
		for(int j = 0;j<numSubf;j++){
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
		if(currentNodeFormula->element == 'A'){
			int i = 0, end = 0;
			while((i<currentNode->numSubf) && (end == 0)){
				if(currentNode->trueSubf[i] != currentNodeFormula->leftSon || currentNode->trueSubf[i] == currentNodeFormula->rightSon) end = 1;
				i++;
			}
			if(end == 1 || currentNode->numSubf == 0) currentNode->trueSubf[(currentNode->numSubf)++] = currentNodeFormula;
		}
		if(currentNodeFormula->element == 'B'){
			int i = 0, end = 0;
			while((i<currentNode->numSubf) && (end == 0)){
				if(currentNode->trueSubf[i] == currentNodeFormula->leftSon) end = 1;
				i++;
			}
			if(end == 1){
				i = 0;
				while((i<currentNode->numSubf) && (end == 1)){
					if(currentNode->trueSubf[i] == currentNodeFormula->rightSon) end = 2;
					i++;	
				}
			} 
			if(end == 2) currentNode->trueSubf[(currentNode->numSubf)++] = currentNodeFormula;
		}
		if(currentNodeFormula->element == 'C'){
			int i = 0, end = 0;
			while((i<currentNode->numSubf) && (end == 0)){
				if(currentNode->trueSubf[i] == currentNodeFormula->leftSon || currentNode->trueSubf[i] == currentNodeFormula->rightSon) end = 1;
				i++;
			}
			if(end == 1) currentNode->trueSubf[(currentNode->numSubf)++] = currentNodeFormula;
		}
		if(currentNodeFormula->element == 'D'){
			int i = 0, end = 0;
			while((i<currentNode->numSubf) && (end == 0)){
				if(currentNode->trueSubf[i] == currentNodeFormula->leftSon) end = 1;
				i++;
			}
			if(end == 0) currentNode->trueSubf[(currentNode->numSubf)++] = currentNodeFormula;
		}
		if(currentNodeFormula->element == 'I'){
			int i = 0, end = 0;
			if(currentNode->future1 == NULL && currentNode->future2 == NULL)
				currentNode->trueSubf[(currentNode->numSubf)++] = currentNodeFormula;
			else {
				if(currentNode->future1){
					while((i<currentNode->future1->numSubf) && (end == 0)){
						if(currentNode->future1->trueSubf[i] != currentNodeFormula->leftSon) end = 1;
						i++;
					}
				}
				if(end == 1){
					if(currentNode->future2 == NULL)
						currentNode->trueSubf[(currentNode->numSubf)++] = currentNodeFormula;
					else {
						i = 0;
						while((i<currentNode->future2->numSubf) && (end == 1)){
							if(currentNode->future2->trueSubf[i] == currentNodeFormula->leftSon) end = 2;
							i++;
						}
						if(end == 2) currentNode->trueSubf[(currentNode->numSubf)++] = currentNodeFormula;
					}
				}
			}
		}
		if(currentNodeFormula->element == 'J'){
			int i = 0, end = 0;
			if(currentNode->future1){
				while((i<currentNode->future1->numSubf) && (end == 0)){
					if(currentNode->future1->trueSubf[i] == currentNodeFormula->leftSon) end = 1;
					i++;
				}
			}
			i = 0;
			if((currentNode->future2) && (end == 0)){
				while((i<currentNode->future2->numSubf) && (end == 0)){
					if(currentNode->future2->trueSubf[i] == currentNodeFormula->leftSon) end = 1;
					i++;			
				}
			}
			if(end == 1) currentNode->trueSubf[(currentNode->numSubf)++] = currentNodeFormula;
		}
		currentNode = currentNode->next;
	}
}

void cleanStruct(struct node *currentNode){
	currentNode->numSubf = 0;
	if(currentNode->next) cleanStruct(currentNode->next);
}
