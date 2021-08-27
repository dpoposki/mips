struct node {
	int instruction;
	char line[MAXLINE];			// Maximum number of characters in a line
	struct node *next;			// Link to the next structure
	struct node *prev;			// Link to the previous structure
	struct node *future1;		// Link to the future node, which is actually the next one
	struct node *future2;		// In case of branching instruction, link to the beginning of the label
	struct node *past[MAXPAST];	// Possible pasts of the instructions
	struct treeNode *trueSubf[MAXFORMULA];
	int numSubf;
	int numPast;				// Counter of pasts
	int accessed[32];
	int valueSet[32];
	bool random[32];
};

void readFile(FILE *fp, struct node *currentNode) {
	char line[MAXLINE];
	while(fgets(line,MAXLINE,fp)!=NULL) {
		struct node *son=(struct node *)malloc(sizeof(struct node));
		setNull(son);
		currentNode->next=son;
		son->prev=currentNode;
		cleanString(line);	// Call the cleanString function to eliminate all characters that are not needed
		son->instruction=recognizeCommand(line); // Store the instruction of the actual line and recognize the instruction
		strcpy(son->line,line);	// Store the line
		currentNode=son;
		fillRegisterArrays(currentNode);
	}
}

void printFile(struct node *currentNode) {
	// Print the file that you've read, in order to see if everything works OK
	int i;
	if(currentNode!=NULL) {		// Print the lines until you get to the end of the file
		printf("%s ",currentNode->line);
		printf("\n");
		if(currentNode->numSubf > 0){
			printf("This node satisfies ");
			for(i=0;i<currentNode->numSubf;i++){
				printFormula(currentNode->trueSubf[i]);
				printf("\n");
			}
		}
		//if(currentNode->future1!=NULL) printf("- future1: %s",currentNode->future1->line);                       //commented these 3 lines here (risto)
		//if(currentNode->future2!=NULL) printf("- future2: %s",currentNode->future2->line);
		//for(i=0;i<currentNode->numPast;i++) printf("- past%d: %s",i,currentNode->past[i]->line);
		//printf("\n valueSet:");
		//for(i = 0; i < 32; i++) printf("%d ",currentNode->valueSet[i]);
		//printf("\n accessed:");
		//for(i = 0; i < 32; i++) printf("%d ",currentNode->accessed[i]);
		//printf("\n\n");
		printFile(currentNode->next);
	}
}

void moveThrough(struct node *root, struct node *currentNode) {		// Structures as arguments to the function moveThrough
	// The function moveThrough is used to move through the structures
	struct node *temp;
	if(currentNode!=NULL) {
		// if you find a branching instruction, then jump to findLabel
		if(currentNode->instruction==3 || currentNode->instruction==9)	{
			temp=findLabel(root,currentNode);		// Find the specific label
			currentNode->future2=temp;				// Tell to the current node where is the beginning of the current label
			temp->past[temp->numPast]=currentNode;	// Tell to the future label that its past is the current node
			temp->numPast++;						// We have counted a past so increase the counter
		}
	
		if(currentNode->next!=NULL)
			moveThrough(root,currentNode->next);			// Check the next line
	}
}

struct node *findLabel(struct node *root, struct node *currentNode) {
	// findLabel is used to find the branching label
	char line[MAXLINE];
	struct node *temp=(struct node *)malloc(sizeof(struct node));
	temp=root;
	strcpy(line,currentNode->line);
	extractLabel(line,currentNode->instruction);
	while((temp->next)&&(strcmp(line,temp->line))) temp=temp->next;		// Look for the specific label in the .asm program
	return temp;
}

void linkNodes(struct node *currentNode) {
	if(currentNode!=NULL) {
		if((currentNode->instruction!=3) && (currentNode->next))			// If different than b
			currentNode->future1=currentNode->next;	// Next line is the next future
		else currentNode->future1=currentNode->future2;	// Else the future is the specific label
		
		if(currentNode->next!=NULL)
			linkNodes(currentNode->next);				// Recursive call for the next structure (node)
	}
}

void setNull(struct node *currentNode) {
	currentNode->next=NULL;
	currentNode->prev=NULL;
	currentNode->future1=NULL;
	currentNode->future2=NULL;
	currentNode->instruction=0;
	strcpy(currentNode->line,"");
	currentNode->numPast=0;
	
	for(int i = 0; i < 32; i++){
		currentNode->valueSet[i] = 0;
		currentNode->accessed[i] = 0;
		//random[i]=0;
	}
}

int checkPrefix(char buf[],char pre[],int len) {
	// The function checkPrefix is used to take the prefix of the instruction in the actual line
    int i;
    for(i=0;(i<len)&&(buf[i]==pre[i]);i++);
    return (i==len);
}

void fillRegisterArrays(struct node *currentNode){
	int i, j, position, register_counter;
	char registerID[3];
	for(j = 0, register_counter = 0; j <= strlen(currentNode->line); j++){           // (currentNode->line[j] != '\0') was not working
		if(recognizeCommand(currentNode->line) == 5)
			currentNode->accessed[2] = 1; // $v0 was accessed

		if(currentNode->line[j]=='$'){
			register_counter++;
			registerID[0] = currentNode->line[j+1];
			registerID[1] = currentNode->line[j+2];
			registerID[2] = '\0';
			position = recognizeRegister(registerID);
	
	
		/* One register commands */
			for(i = 11; i <= 15; i++){
				if(recognizeCommand(currentNode->line) == i){
					currentNode->valueSet[position] = 1;
					currentNode->accessed[position] = 0;
					//currentNode->random[position] = ;
				}

			}
		/* One register branches */
			for(i = 16; i < 20; i++){
				if(recognizeCommand(currentNode->line) == i){
					currentNode->valueSet[position] = 0;
					currentNode->accessed[position] = 1;
					//currentNode->random[position = ;
				}
			}
		/* Two register commands */
			for(i = 21; i < 25; i++){
				if(recognizeCommand(currentNode->line) == i){
					if(register_counter == 1){ //What will happen to the first register in the line is not same with what will happen to the second
						currentNode->valueSet[position] = 1;
						currentNode->accessed[position] = 0;
					}
					else if(register_counter == 2){
						currentNode->valueSet[position] = 0;
						currentNode->accessed[position] = 1;
					}
				}
			}
		/* Two register branches */
			for(i = 25; i < 30; i++){
				if((register_counter == 1) || (register_counter == 2)){
					if(recognizeCommand(currentNode->line) == i){
						currentNode->valueSet[position] = 0;
						currentNode->accessed[position] = 1;
					}
				}
			}
		/* Three register commands */
			for(i = 31; i < 40; i++){
				if(recognizeCommand(currentNode->line) == i){
					if(register_counter == 1){
						currentNode->valueSet[position] = 1;
						currentNode->accessed[position] = 0;
					}
					else if(register_counter == 2){
						currentNode->valueSet[position] = 0;
						currentNode->accessed[position] = 1;
					}
					else if(register_counter == 3){
						currentNode->valueSet[position] = 0;
						currentNode->accessed[position] = 1;
					}
				}
			}
		/* Mult and div commands that change lo and hi */
			for(i = 41; i <= 45; i++){
				if(recognizeCommand(currentNode->line) == i){
					currentNode->valueSet[30] = 1; // lo was set
					currentNode->valueSet[31] = 1; // hi was set
					if(register_counter == 1){
						currentNode->valueSet[position] = 0;
						currentNode->accessed[position] = 1;
					}
					else if(register_counter == 2) {
						currentNode->valueSet[position] = 0;
						currentNode->accessed[position] = 1;					
					}
				}
			}

		/* Commands that move from hi */
			if(recognizeCommand(currentNode->line) == 46){
				currentNode->accessed[31] = 1; //hi was accessed
				if(register_counter == 1){
					currentNode->valueSet[position] = 1;
					currentNode->accessed[position] = 0;
				}
			}

		/* Commands that move from lo */
			if(recognizeCommand(currentNode->line) == 47){
				currentNode->accessed[30] = 1; //lo was accessed
				if(register_counter == 1){
					currentNode->valueSet[position] = 1;
					currentNode->accessed[position] = 0;
				}
			}
		}
	}
}
int recognizeRegister(char registerID[]){

	if(!strcmp(registerID,"ze")) return 0; // the full name of the register is "zero"
	if(!strcmp(registerID,"at")) return 1;
	if(!strcmp(registerID,"v0")) return 2;
	if(!strcmp(registerID,"v1")) return 3;
	if(!strcmp(registerID,"a0")) return 4;
	if(!strcmp(registerID,"a1")) return 5;
	if(!strcmp(registerID,"a2")) return 6;
	if(!strcmp(registerID,"a3")) return 7;
	if(!strcmp(registerID,"t0")) return 8;
	if(!strcmp(registerID,"t1")) return 9;
	if(!strcmp(registerID,"t2")) return 10;
	if(!strcmp(registerID,"t3")) return 11;
	if(!strcmp(registerID,"t4")) return 12;
	if(!strcmp(registerID,"t5")) return 13;
	if(!strcmp(registerID,"t6")) return 14;
	if(!strcmp(registerID,"t7")) return 15;
	if(!strcmp(registerID,"t8")) return 16;
	if(!strcmp(registerID,"t9")) return 17;
	if(!strcmp(registerID,"s0")) return 18;
	if(!strcmp(registerID,"s1")) return 19;
	if(!strcmp(registerID,"s2")) return 20;
	if(!strcmp(registerID,"s3")) return 21;
	if(!strcmp(registerID,"s4")) return 22;
	if(!strcmp(registerID,"s5")) return 23;
	if(!strcmp(registerID,"s6")) return 24;
	if(!strcmp(registerID,"s7")) return 25;
	if(!strcmp(registerID,"k0")) return 26;
	if(!strcmp(registerID,"k1")) return 27;
	if(!strcmp(registerID,"gp")) return 28;
	if(!strcmp(registerID,"sp")) return 29;
	if(!strcmp(registerID,"lo")) return 30;
	if(!strcmp(registerID,"hi")) return 31;

}



int recognizeCommand(char instr[])
{
    char *pattern;
    pattern=strstr(instr,":");
	if(pattern)																						return  1;
	if(checkPrefix(instr,".",1))																	return  0;
	if(checkPrefix(instr,"syscall",7))																return	5;

	/*Commands that take 1 registers */
	
	if(checkPrefix(instr,"lui",3))																	return 13;	
	if(checkPrefix(instr,"la",2))																	return 14;
	if(checkPrefix(instr,"li",2))																	return 15;
	/* one register branches */
	if(checkPrefix(instr,"beqz",4) || checkPrefix(instr,"bgtz",4) || checkPrefix(instr,"bltz",4))	return 16;
	if(checkPrefix(instr,"blez",4) || checkPrefix(instr,"bgez",4) || checkPrefix(instr,"bnez",4))	return 16;
	if(checkPrefix(instr,"bgz",3))																	return 17;

	/*Commands that take 2 registers */	
	if(checkPrefix(instr,"move",4))																	return 23;
	/* two register branches */
	if(checkPrefix(instr,"beq",3) || checkPrefix(instr,"bgt",3) || checkPrefix(instr,"blt",3))		return 26;
	if(checkPrefix(instr,"ble",3) || checkPrefix(instr,"bge",3) || checkPrefix(instr,"bne",3))		return 26;

	if(checkPrefix(instr,"lb",4))																	return 28; // Will we include lb & sb also ?
	if(checkPrefix(instr,"sb",2))																	return 29;

	/*Commands that take 3 registers */
	if(checkPrefix(instr,"add",3))																	return 31;
	if(checkPrefix(instr,"sub",3))																	return 32;
    if(checkPrefix(instr,"mul",3) && !checkPrefix(instr,"mult",4))									return 33;

	/* Commands that change lo & hi */
	if(checkPrefix(instr,"div",3))																	return 41;
	if(checkPrefix(instr,"mult",4))																	return 42;
	/* Commands that access lo & hi */
	if(checkPrefix(instr,"mfhi",4))																	return 46;
	if(checkPrefix(instr,"mflo",4))																	return 47;


	/* branches */
	if(checkPrefix(instr,"b",1))																	return 3;

	return 666; // :-[

}
