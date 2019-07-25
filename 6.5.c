#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

int enqueue(struct studentqueue *q, const char *name)
{
	struct studentqueue *nextstudent = calloc(1,sizeof(struct studentqueue));
	if(!nextstudent){free(nextstudent);return 0;}
	char *nextname = calloc(strlen(name)+1,sizeof(char));
	if(!nextname){free(nextname);free(nextstudent);return 0;}
	nextname = strcpy(nextname, name);
	nextstudent->next = NULL;
	nextstudent->name = nextname;
	struct studentqueue *laststudent = q;
	while (laststudent->next){laststudent = laststudent->next;}
	laststudent->next = nextstudent;
	return 1;
}



int dequeue(struct studentqueue *q, char *buffer, unsigned int size)
{
	struct studentqueue *todel = q->next;
	if(!todel){return 0;}
	strncpy(buffer, todel->name,size-1);
	q->next = todel->next;
	free(todel->name);
	free(todel);
	return 1;
}



int main(void)
{
	struct studentqueue q = { NULL, NULL };

	int go_on = 1;
	char buffer[100];
	while(go_on) {
	    printf("Enter name of the student (\"-\" will end reading): ");
	    scanf("%99s", buffer);
	    buffer[99] = 0;
	    if (strlen(buffer) > 0 && strcmp(buffer, "-")) {
		    go_on = enqueue(&q, buffer);
	    } else {
		    go_on = 0;
	    }
	}

	while(dequeue(&q, buffer, 100)) {
	    printf("Fetching %s from queue\n", buffer);
	}

	return 0;
}