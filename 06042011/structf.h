#define MAXLINE 250
#define MAXPAST 5

int recognizeCommand(char instr[]);
void moveThrough(struct node *root, struct node *currentNode);
struct node *findLabel(struct node *root, struct node *currentNode);
void setNull(struct node *currentNode);

struct node {
	int instruction;
	char line[MAXLINE];			// Maximum number of characters in a line
	struct node *next;			// Link to the next structure
	struct node *prev;			// Link to the previous structure
	struct node *future1;		// Link to the future node, which is actually the next one
	struct node *future2;		// In case of branching instruction, link to the beginning of the label
	struct node *past[MAXPAST];	// Possible pasts of the instructions
	int numPast;				// Counter of pasts
};

void readFile(FILE *fp, struct node *currentNode) {
	char line[MAXLINE];
	while(fgets(line,MAXLINE,fp)!=NULL) {
		struct node *son=(struct node *)malloc(sizeof(struct node));
		currentNode->next=son;
		son->prev=currentNode;
		cleanString(line);	// Call the cleanString function to eliminate all characters that are not needed
		son->instruction=recognizeCommand(line); // Store the instruction of the actual line and recognize the instruction
		strcpy(son->line,line);	// Store the line
		son->future1=NULL;
		son->future2=NULL;
		son->numPast=0;
		son->next=NULL;	// Store the address of the next structure
		currentNode=son;
	}
}

void printFile(struct node *currentNode) {
	// Print the file that you've read, in order to see if everything works OK
	int i;
	if(currentNode!=NULL) {		// Print the lines until you get to the end of the file
		printf("%s ",currentNode->line);
		if(currentNode->future1!=NULL) printf("- future1: %s",currentNode->future1->line);
		if(currentNode->future2!=NULL) printf("- future2: %s",currentNode->future2->line);
		for(i=0;i<currentNode->numPast;i++) printf("- past%d: %s",i,currentNode->past[i]->line);
		printf("\n");
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
			currentNode->future1=currentNode->next;	    // Next line is the next future
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
}

int checkPrefix(char buf[],char pre[],int len) {
	// The function checkPrefix is used to take the prefix of the instruction in the actual line
    int i;
    for(i=0;(i<len)&&(buf[i]==pre[i]);i++);
    return (i==len);
}

int recognizeCommand(char instr[]) {
    char *pattern;
    pattern=strstr(instr,":");
    if(pattern)                        		return 1;
    if(checkPrefix(instr,".",1))            return 0;
    else if(checkPrefix(instr,"syscall",7)) return 2;
	else if(checkPrefix(instr,"mflo",4))    return 4;
	else if(checkPrefix(instr,"mfhi",4))	return 5;
	else if(checkPrefix(instr,"mult",4))	return 6;
	else if(checkPrefix(instr,"mul",3))     return 7;
	else if(checkPrefix(instr,"beqz",4) || checkPrefix(instr,"bgtz",4) || checkPrefix(instr,"bltz",4) || checkPrefix(instr,"blez",4) || checkPrefix(instr,"bgez",4) || checkPrefix(instr,"bnez",4))	return 8;
	else if(checkPrefix(instr,"beq",3) || checkPrefix(instr,"bgt",3) || checkPrefix(instr,"blt",3) || checkPrefix(instr,"ble",3) || checkPrefix(instr,"bge",3) || checkPrefix(instr,"bne",3))	return 9;
    else if(checkPrefix(instr,"li",2))      return 10;
	else if(checkPrefix(instr,"la",2))		return 11;
	else if(checkPrefix(instr,"lb",2))		return 12;
	else if(checkPrefix(instr,"sb",2))		return 13;
    else if(checkPrefix(instr,"mo",2))		return 14;
	else if(checkPrefix(instr,"a",1))		return 15;
	else if(checkPrefix(instr,"s",1))		return 16;
    else if(checkPrefix(instr,"b",1) && !strrchr(instr,'$'))       return 3;
   	else if(checkPrefix(instr,"di",2))     	return 17;

    return 0;
}

void recognizeRegisters(struct node *currentNode) {
	int i,j,counter=0,position;
	char reg[2];
	for(i=0;currentNode->line[i]!='\0';i++) {
		j=0;
		if(currentNode->line[i]=='$') {
			reg[j]=currentNode->line[i+1];
			reg[j+1]=currentNode->line[i+2];
			position=findPosition(reg);
			if(counter>=1) currentNode->access[position]=1;
			else currentNode->initialize[position]=1;
			counter++;
		}
	}
}

int findPosition(char reg[]) {
	if(reg[0]=='t' && reg[1]=='0') return 1;
	if(reg[0]=='t' && reg[1]=='1') return 2;
	if(reg[0]=='t' && reg[1]=='2') return 3;
}
