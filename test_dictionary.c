#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "dictionary.h"

int comp(const void *a, const void *b) {
	char hi = *(const char *)a;
	char ih = *(const char *)b;
	return hi - ih;
}

void print_list(VNode *head){
	VNode *cur = head;
	while(cur){
		printf("%s ", cur->value);
		cur = cur->next;
	}
	printf("\n");
}

int main (int argc, char ** argv) {
	
	DNode* result;
	
	//either static or use calloc - to set all bytes initially to 0
	static DNode* dictionary [DEFAULT_HASH_SIZE]; 
	
	
	set(dictionary, DEFAULT_HASH_SIZE, "pore", "repo");
	set(dictionary, DEFAULT_HASH_SIZE, "pore", "rope");
	
	
	result = get (dictionary, DEFAULT_HASH_SIZE, "pore");
	if (result != NULL) {
		printf("Anagrams for 'pore':\n");
		print_list (result->values);
	}
	else
		printf ("'pore' not found\n");
	
	set(dictionary, DEFAULT_HASH_SIZE, "bore", "robe");
	result = get (dictionary, DEFAULT_HASH_SIZE, "bore");

	if (result != NULL) {
		printf("Anagrams for 'bore':\n");
		print_list (result->values);
	}
	else
		printf ("'bore' not found\n");
	
	free_dictionary(dictionary, DEFAULT_HASH_SIZE);
	
	char **words = malloc(1000*sizeof(char*));
	for(int i = 0; i < 1000; i++) {
		words[i] = malloc(100*sizeof(char));
	}
    FILE *f = fopen("words.txt", "r");
	int i = 0;
	while(fgets(words[i], 100, f) != NULL) {
		words[i][strlen(words[i]) - 2] = '\0';
		i++;
	}
	fclose(f);
	for(int i = 0; i < 1000; i++) {
		char sort[strlen(words[i])];
		for(int j = 0; j < strlen(words[i]); j++) {
			sort[j] = words[i][j];
		}
		sort[strlen(words[i])] = '\0';
		qsort(sort, strlen(sort), sizeof(char), comp);
		set(dictionary, DEFAULT_HASH_SIZE, sort, words[i]);
	}
	printf("\n");
	int count = 0;
	for(int i = 0; i < DEFAULT_HASH_SIZE; i++) {
		if(dictionary[i] == NULL)
		continue;
		DNode* node = dictionary[i];
		while(node != NULL) {
			if(node->values->next == NULL) {
				node = node->next;
				continue;
			}
			count++;
			print_list(node->values);
			node = node->next;
		}
	}
	printf("%d anagram lists", count);
	return 0;
}

