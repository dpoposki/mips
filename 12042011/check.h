int checkFormula(struct node *rootStruct, struct treeNode *rootFormula){
	if(rootFormula->code == '0'){
		for(int i=0;i<MAXREG;i++){
			if(checkSingleFormula(rootStruct,rootFormula,i) == 1) return i;                                                
			//printFile(rootStruct);
			//system("pause");
			cleanStruct(rootStruct);
		}
		return -1;
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

int checkSingleFormula(struct node *rootStruct, struct treeNode *rootFormula, int instance){
	struct treeNode *subFormula[MAXFORMULA];
	int numSubf, maxLevel;
	maxLevel = findMaxLevel(rootFormula);
	int i;
    for(i = maxLevel;i>=0;i--){
		numSubf = 0;
		findLevel(subFormula,rootFormula,&numSubf,i);
		for(int j = 0;j<numSubf;j++){
			linkNode(subFormula[j],rootStruct,instance);
		}
	}
	for(i = 0;(i<rootStruct->numSubf) && (rootStruct->trueSubf[i] != rootFormula);i++);
	if(i < rootStruct->numSubf) return 1;
	else return 0;
}

int findMaxLevel(struct treeNode *currentNodeFormula){
	if(currentNodeFormula->leftSon == NULL && currentNodeFormula->rightSon == NULL){
		return currentNodeFormula->level;
	}
	if(currentNodeFormula->rightSon){
        int temp1 = findMaxLevel(currentNodeFormula->rightSon);
        int temp2 = findMaxLevel(currentNodeFormula->leftSon);
		if(temp1 > temp2) return temp1;
		else return temp2;
	}
	else return findMaxLevel(currentNodeFormula->leftSon);
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
			else{
				if(currentNode->future1){
					while((i<currentNode->future1->numSubf) && (end == 0)){
						if(currentNode->future1->trueSubf[i] != currentNodeFormula->leftSon) end = 1;
						i++;
					}
				}
				if(end == 1){
					if(currentNode->future2 == NULL)
						currentNode->trueSubf[(currentNode->numSubf)++] = currentNodeFormula;
					else{
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
		if(currentNodeFormula->element == 'G'){
           if(currentNode->future1 != NULL){
              if(findSometimeInTheFuture(currentNode->future1,currentNodeFormula->leftSon) == 1) 
                 currentNode->trueSubf[(currentNode->numSubf)++] = currentNodeFormula;
              else{
                 if(currentNode->future2 != NULL){
                    if(findSometimeInTheFuture(currentNode->future2,currentNodeFormula->leftSon) == 1)
                       currentNode->trueSubf[(currentNode->numSubf)++] = currentNodeFormula;
                 }
              }                        
           } 
        }
        if(currentNodeFormula->element == 'E'){
           if(currentNode->future1 != NULL){
              if(findAlwaysInTheFuture(currentNode->future1,currentNodeFormula->leftSon) == 1){
                 if(currentNode->future2 != NULL){
                    if(findAlwaysInTheFuture(currentNode->future2,currentNodeFormula->leftSon) == 1)
                       currentNode->trueSubf[(currentNode->numSubf)++] = currentNodeFormula;                          
                 }
                 currentNode->trueSubf[(currentNode->numSubf)++] = currentNodeFormula;                                                                           
              }                       
           }
           else currentNode->trueSubf[(currentNode->numSubf)++] = currentNodeFormula;                         
        }
        if(currentNodeFormula->element == 'L'){
           if(currentNode->future1 != NULL){
              if(findSometimeUntil(currentNode->future1,currentNodeFormula->leftSon,currentNodeFormula->rightSon) == 1){
                 int i;
                 for(i = 0;(i < currentNode->numSubf) && (currentNode->trueSubf[i] != currentNodeFormula->leftSon);i++);
                 if(i < currentNode->numSubf) currentNode->trueSubf[(currentNode->numSubf)++] = currentNodeFormula;                                                                                                    
              }
              else{
                 if(currentNode->future2 != NULL){
                    if(findSometimeUntil(currentNode->future1,currentNodeFormula->leftSon,currentNodeFormula->rightSon) == 1){
                       int i;
                       for(i = 0;(i < currentNode->numSubf) && (currentNode->trueSubf[i] != currentNodeFormula->leftSon);i++);
                       if(i < currentNode->numSubf) currentNode->trueSubf[(currentNode->numSubf)++] = currentNodeFormula;                                                                                                    
                    }
                 }
              }                        
           } 
        }
		currentNode = currentNode->next;
	}
}

int findSometimeInTheFuture(struct node *currentNode, struct treeNode *currentNodeFormula){
    int temp = 0, i;
    if(!currentNode->mark){
       for(i = 0;(i < currentNode->numSubf) && (currentNode->trueSubf[i] != currentNodeFormula);i++);
       if(i < currentNode->numSubf) return 1; 
       if(currentNode->future1 != NULL){
          currentNode->mark = 1;
          temp = findSometimeInTheFuture(currentNode->future1,currentNodeFormula);
          currentNode->mark = 0;                        
       }    
       if((temp == 0) && (currentNode->future2 != NULL)){
          currentNode->mark = 1;
          temp = findSometimeInTheFuture(currentNode->future2,currentNodeFormula); 
          currentNode->mark = 0; 
       }
    }
    return temp;
}

int findAlwaysInTheFuture(struct node *currentNode, struct treeNode *currentNodeFormula){
    int temp = 0, i;
    if(!currentNode->mark){
       for(i = 0;(i < currentNode->numSubf) && (currentNode->trueSubf[i] != currentNodeFormula);i++);
       if(i < currentNode->numSubf) return 1; 
       if(currentNode->future1 != NULL){
          currentNode->mark = 1;
          temp = findAlwaysInTheFuture(currentNode->future1,currentNodeFormula);
          currentNode->mark = 0;                        
       }    
       if((temp == 1) && currentNode->future2 != NULL){
          currentNode->mark = 1;
          temp = findAlwaysInTheFuture(currentNode->future2,currentNodeFormula); 
          currentNode->mark = 0; 
       }
    }
    return temp;
}

int findSometimeUntil(struct node *currentNode, struct treeNode *currentNodeFormulaP, struct treeNode *currentNodeFormulaQ){
    int temp = 0, i;
    if(!currentNode->mark){
       for(i = 0;(i < currentNode->numSubf) && (currentNode->trueSubf[i] != currentNodeFormulaQ);i++);
       if(i < currentNode->numSubf) return 1; 
       if(currentNode->future1 != NULL){
          currentNode->mark = 1;
          for(i = 0;(i < currentNode->numSubf) && (currentNode->trueSubf[i] != currentNodeFormulaP);i++);
          if(i < currentNode->numSubf){
             temp = findSometimeUntil(currentNode->future1,currentNodeFormulaP,currentNodeFormulaQ);   
          }
          currentNode->mark = 0;                        
       }    
       if((temp == 0) && (currentNode->future2 != NULL)){
          currentNode->mark = 1;
          for(i = 0;(i < currentNode->numSubf) && (currentNode->trueSubf[i] != currentNodeFormulaP);i++);
          if(i < currentNode->numSubf){
             temp = findSometimeUntil(currentNode->future2,currentNodeFormulaP,currentNodeFormulaQ);   
          } 
          currentNode->mark = 0; 
       }
    }
    return temp;
}

void cleanStruct(struct node *currentNode){
	currentNode->numSubf = 0;
	if(currentNode->next) cleanStruct(currentNode->next);
}
