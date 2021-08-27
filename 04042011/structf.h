#define MAXLINE 250
#define MAXPAST 5

int recognizeCommand(char instr[]);
void moveThrough(struct node *root, struct node *currentNode);
struct node *findLabel(struct node *root, struct node *currentNode);

struct node {
	int instruction;
	char line[MAXLINE];
	struct node *next;
	struct node *prev;
	struct node *future1;
	struct node *future2;
	struct node *past[MAXPAST];
	int numPast;
};

void readFile(FILE *fp, struct node *currentNode) {
	// The function readFile is used to read the .txt or .asm file that you want to work with
	char line[MAXLINE];
	struct node *son=(struct node *)malloc(sizeof(struct node));
	son->prev=currentNode;	// Store the address of the previous structure
    if(fgets(line,MAXLINE,fp)!=NULL) {
        cleanString(line);	// eliminate all characters that are not needed
		currentNode->instruction=recognizeCommand(line); // store the instruction of the actual line
		strcpy(currentNode->line,line);	// store the line
		currentNode->next=son;	// Store the address of the next structure
		currentNode->future1=NULL;
		currentNode->future2=NULL;
		currentNode->numPast=0;
		readFile(fp,son);
    }
	else {
		currentNode->next=NULL;
	}
}

void printFile(struct node *currentNode) {
	// Print the file that you've read, in order to see if everything works OK
	int i;
	if(currentNode->next!=NULL) {
		printf("%s ",currentNode->line);
		if(currentNode->future1!=NULL) printf("- future1: %s",currentNode->future1->line);
		if(currentNode->future2!=NULL) printf("- future2: %s",currentNode->future2->line);
		for(i=0;i<currentNode->numPast;i++) printf("- past%d: %s",i,currentNode->past[i]->line);
		printf("\n");
		printFile(currentNode->next);
	}
}

void moveThrough(struct node *root, struct node *currentNode) {
	// The function moveThrough is used to move through the structures
	struct node *temp;
	if(currentNode->next!=NULL) {
		// if you find a branching instruction, then jump to findLabel
		if(currentNode->instruction==3 || currentNode->instruction==9)	{
			temp=findLabel(root,currentNode);
			currentNode->future2=temp;
			temp->past[temp->numPast]=currentNode;
			temp->numPast++;
		}
		
	moveThrough(root,currentNode->next);
	}
}

struct node *findLabel(struct node *temp, struct node *currentNode) {
	// The function findLabel is used to find the branching label
	int i;
	char line[MAXLINE];
	if(currentNode->instruction==3) {
		strcpy(line,currentNode->line);
		for(i=0;line[i]!='\0';i++) line[i]=line[i+1];
		line[i]='\0';
	}
	if(currentNode->instruction==9) {
		for(i=strlen(line);(i>0) && (line[i]!=',');i--);
		strncpy(line,currentNode->line,i);
	}
	while((temp->next)&&(strncmp(line,temp->line,strlen(line)))) temp=temp->next;
	return temp;
}

void linkNodes(struct node *currentNode) {
	if(currentNode->next!=NULL) {
		if(currentNode->instruction!=3)
			currentNode->future1=currentNode->next;
		else currentNode->future1=currentNode->future2;

	linkNodes(currentNode->next);
	}
}

int checkPrefix(char buf[],char pre[],int len) {
	// The function checkPrefix is used to take the prefix of the instruction in the actual line
    int i;
    for(i=0;(i<len)&&(buf[i]==pre[i]);i++);
    return (i==len);
}

int recognizeCommand(char instr[]) {
	// The function recognizeCommand is used to recognize the instruction in the actual line
    char *pattern;
    pattern=strstr(instr,":");
    if (pattern)                        return 1;
    if (checkPrefix(instr,".",1))            return 0;
    else if (checkPrefix(instr,"syscall",7)) return 7;
    else if (checkPrefix(instr,"l",1))       return 4;
    else if (checkPrefix(instr,"mo",2)||checkPrefix(instr,"a",1)||checkPrefix(instr,"s",1))
                                        return 2;
	else if (checkPrefix(instr,"blt",3)||checkPrefix(instr,"beq",3)) return 9;
    else if (checkPrefix(instr,"b",1))       return 3;
    else if (checkPrefix(instr,"mu",2))      return 5;
    else if (checkPrefix(instr,"di",2))      return 6;
    else if (checkPrefix(instr,"mf",2))      return 8;
    return 0;
}
