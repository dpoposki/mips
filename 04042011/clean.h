#include <ctype.h>

void cleanString(char buf[])
{
    int i,j;
    for(i=0;buf[i]!='\0';i++) {
		if(isspace(buf[i])) {
			for(j=i;buf[j]!='\0';j++) buf[j]=buf[j+1];
		}
	}
	for(i=0;buf[i]!='\0';i++) {
       if(buf[i]=='#') buf[i]='\0';                       
       }
}
