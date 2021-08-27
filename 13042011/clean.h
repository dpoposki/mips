void cleanString(char buf[]) {
	// The function cleanString is used to modify the string by deleting the spaces and comments from the string
    int i,j;
    for (i=0;buf[i]!='\0';i++) {
		if (isspace(buf[i])) {
			for(j=i;buf[j]!='\0';j++) buf[j]=buf[j+1];
		}
	}
	for(i=0;buf[i]!='\0';i++) {
		if(buf[i] == '#') buf[i] = '\0';
	}
}

void extractLabel(char line[], int instruction) {
	int i,j;
	if(instruction==3) {
		for(i=0;line[i]!='\0';i++) line[i]=line[i+1];		// Deleting b
		line[i-1] = ':';
        line[i] = '\0';
	}
	else {
		for(i=strlen(line);line[i]!=',';i--);
		for(j=0,i++;line[i]!='\0';j++,i++) line[j]=line[i];
		line[j] = ':';
        line[j+1] = '\0';
	}
}
