#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "book.h"


int init_book(struct book *p_book, const char *p_id, const char *p_title, const char *p_author, struct date p_release)
{
	if (strlen(p_id) >9){ return 0;}
	else{
		strcpy(p_book->id,p_id);
		size_t titlesize = strlen(p_title)+1;
		size_t authorsize = strlen(p_author) + 1;
		char *b_author = malloc(authorsize);
		char *b_title = malloc(titlesize);
		if ((!b_title) || (!b_author))
		{
			free(b_title);
			free(b_author);
			return 0;
		}
		else
		{
			memset(b_title,'\0', titlesize);
			memset(b_author,'\0', authorsize);
			strcpy(b_title, p_title);
			strcpy(b_author, p_author);
			
			p_book->title = b_title;
			p_book->author = b_author;
			p_book->release_date = p_release;
			return 1;
			
		}
	}
}

struct book *add_to_collection(struct book *collection, unsigned int size, struct book new_book)
{
	unsigned int required_size = (size+1)*sizeof(struct book);
	struct book *array = realloc(collection, required_size);
	struct book addition;
	init_book(&addition,new_book.id,new_book.title,new_book.author,new_book.release_date);
	array[size] = addition;
	return array;
}


//test

void delete_collection(struct book *collection, unsigned int size)
{
    for (unsigned int i = 0; i < size; i++) {
        free(collection[i].title);
        free(collection[i].author);
    }
    free(collection);
}

int main(void)
{
    /* Feel free to modify */

    struct book a1;
    struct date a1date = {26, 6, 1997};
    if (init_book(&a1, "000000009", "Harry Potter and the Philosopher's Stone", "J. K. Rowling", a1date )) {
        printf("Initialization succeeded\n");
    } else {
        printf("Initialization failed\n");
    }
    
    free(a1.title);
    free(a1.author);
    
    struct book collection[] = {
        { "001020304", "Harry Potter and the Chamber of Secrets", "J. K. Rowling", {2,7,1998} },
        { "555566666", "Harry Potter and the Prisoner of Azkaban", "J. K. Rowling", {8,7,1999} },
        { "773466889", "Harry Potter and the Goblet of Fire", "J. K. Rowling", {8, 7, 2000} },
        { "000000000", "Something For Testing", "Testing author", {1, 2, 3456} }
    };
    
    struct book *array = NULL;
    unsigned int len = 0;

    for (unsigned int i = 0; i < 4; i++) {
        struct book *newarray = add_to_collection(array, len, collection[i]);
        if (!newarray) {
            printf("ERROR - New collection is NULL\n");
            return 1;
        }
        len++;
        array = newarray;
    }

    for (unsigned int i = 0; i < len; i++) {
      printf("%s: %s (%s)\n", array[i].id, array[i].title, array[i].author);
    }

    delete_collection(array, len);

    return 0;
}