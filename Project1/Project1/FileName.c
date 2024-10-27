#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX 1024
#include <stdlib.h> 
#include <string.h>

typedef struct _struct* position; 

typedef struct _struct {

	char name[50];
	char lastname[50];
	int birthYear;
	position next;

}Person;

int Prependlist(position head, char* name, char* lastname, int by);
int Appendlist(position head, char* name, char* lastname, int by);
position Findlast(position head);
int Insertafter(position pervious, position newPerson);
position CreatePerson(char* name, char* lastname, int by);
int printlist(position first); 
position FindByLastname(position head, char* lastname);

int main() {

	Person head = {
			.name = {0},
			.lastname = {0},
			.birthYear = 0,
			.next = NULL
	};

	
	Prependlist(&head, "Ivan", "Ivic", 1983);
	printlist(head.next); 

	Appendlist(&head, "Matea", "Buric", 2000);
	printlist(head.next); 

	FindByLastname(head.next, "Buric");
	printlist(head.next); 
	
	return 0; 
}


position CreatePerson(char* name, char* lastname, int by) {
	
	position newPerson = NULL;

	newPerson = (position)malloc(sizeof(Person));
	
	if (newPerson == NULL) {
		printf("Error while creating a person!");
		return NULL;
	}

	strcpy(newPerson->name, name);
	strcpy(newPerson->lastname, lastname);
	newPerson->birthYear = by; 
	newPerson->next = NULL;

	
	
	
	return newPerson;

}

int Prependlist(position head, char* name, char* lastname, int by) {
	position newPerson = NULL;
	newPerson = CreatePerson(name,lastname, by);

	if (newPerson == NULL) {
		printf("Error occured while creating the person");
		return EXIT_FAILURE;
	}
	
	newPerson->next = head->next;
	head->next = newPerson;

	return 0;
}

int printlist(position first) {
	position temp = NULL;
	temp = first;

	printf("\n");

	while (temp != NULL) {
		printf("%s %s %d\n", temp->name, temp->lastname, temp->birthYear);
		temp = temp->next;
	}

	
	
	return EXIT_SUCCESS;
}

int Appendlist(position head, char* name, char* lastname, int by) {
	 
	position newPerson = NULL; 
	position last;
	newPerson = CreatePerson(name, lastname, by); 

	if (newPerson == NULL) { 
		printf("Error occured while creating the person"); 
		return EXIT_FAILURE; 
	}

	last = Findlast(head);

	Insertafter(last, newPerson);  
	

	return 0;

}

position Findlast(position head) {
	position last = NULL;

	last = head;

	while (last->next != NULL) {
		last = last->next;
	}

	return last;
}

int Insertafter(position pervious, position newPerson) {

	newPerson->next = pervious->next;
	pervious->next = newPerson;

	return 0;


}

position FindByLastname(position head, char* lastname) {
	position temp = NULL;
	temp = head;

	while (temp != NULL) {
		if (strcmp(temp->lastname, lastname) == 0) {
			return temp;
		}
		else {
			temp = temp->next;
		}
		return NULL;
	}
}

position findPrevious(position head, char* name) {
		position current = NULL;
		current = head;
		while (current->next != NULL) {
			if (strcmp((current->next)->name, name) == 0) return current; 
		}
		return NULL; 
}


int Delete(position head, char* name) {  
		position previous = findPrevious(head, name); 
		position current = previous->next; 
		previous->next = current->next; 
		free(current); 
		return EXIT_SUCCESS; 
}

