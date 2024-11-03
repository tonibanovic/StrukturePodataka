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
int AddAfter(position head, char* name, char* surname, int by, char* lastname);
int AddPervious(position head, char* name, char* surname, int by, char* lastname);
void Sort(position head);
int PrintInFile(position head);
int ReadingFromFile(position head);

int main() {

	Person head = {
			.name = {0},
			.lastname = {0},
			.birthYear = 0,
			.next = NULL
	};


	Prependlist(&head, "Ivan", "Ivic", 1983);
	Appendlist(&head, "Matea", "Buric", 2000);
	Appendlist(&head, "Toni", "Banovic", 2004);
	Appendlist(&head, "Andro", "Vukovic", 2004);

	printlist(head.next);


	FindByLastname(head.next, "Buric");

	AddAfter(&head, "Toma", "Skugor", 2004, "Buric");
	printlist(head.next); 

	AddAfter(&head, "Bepo", "Klarin", 2004, "Banovic");
	printlist(head.next); 

	AddPervious(&head, "Antun", "Barcot", 2004, "Buric");
	printlist(head.next);


	Sort(&head);
	printlist(head.next);

	Appendlist(&head, "Ivica", "Ivic", 2003); 
	PrintInFile(head.next);

	

	ReadingFromFile(head.next);
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
	newPerson = CreatePerson(name, lastname, by);

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
		
	}
	return NULL;  
	
}

position findPrevious(position head, char* lastname) {
	position current = NULL;
	current = head;
	while (current->next != NULL) {
		if (strcmp((current->next)->lastname, lastname) == 0) {
			return current;
		}
		else {
			current = current->next;
		}
	
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

int AddAfter(position head, char* name, char* surname, int by, char* lastname) {
	position newPerson = CreatePerson(name, surname, by);
	position p; 

	if (newPerson == NULL) {
		printf("Error occured while creating a person!");
		return EXIT_FAILURE;
	}

	p = FindByLastname(head, lastname);

	if (p == NULL) {
		printf("The person was not found.");
		free(newPerson);
		EXIT_FAILURE;
	}
	

	Insertafter(p, newPerson);  


	return EXIT_SUCCESS;  


}

int AddPervious(position head, char* name, char* surname, int by, char* lastname) {
	position newPerson = CreatePerson(name, surname, by);
	position p; 

	if (newPerson == NULL) { 
		printf("Error occured while creating a person!");
		return EXIT_FAILURE;
	}

	p = findPrevious(head, lastname);


	Insertafter(p, newPerson);


	return EXIT_SUCCESS;


}

void Sort(position head) {
	position j, j_perv, temp, end;

	end = NULL;
	while (head->next != end) {
		j_perv = head;
		j = head->next;

		while (j->next != end) {
			if (strcmp(j->lastname, j->next->lastname) > 0) {
				temp = j->next;
				j_perv->next = temp;
				j->next = temp->next;
				temp->next = j;

				j = temp; 
			}

			j_perv = j; 
			j = j->next;
		}
		
		end = j;

	}

}

int PrintInFile(position head) {
	
	FILE* list;

	list = fopen("Namelist.txt", "w");

	if (list == NULL) {
		printf("Error while opening the file");
		return -1;
	}

	while (head != NULL) {
		fprintf(list, "%-10s %-10s %-10d\n", head->name, head->lastname, head->birthYear);
		head = head->next;
	}

	fclose(list);
	return 0;
}

int ReadingFromFile(position head) {
	FILE* open;
	

	open = fopen("Namelist.txt", "r");

	if (open == NULL) {
		printf("Error while opening the File.");
		return -1;
	}
	
	while (!feof) {
		char name[50];
		char surname[50];
		int birthYear;
		fscanf(open,"%s %s %d", name, surname, &birthYear); 
		
		position newPerson = CreatePerson(name, surname, birthYear);
		
		if (newPerson == NULL) {
			printf("Error while writning the name in the list!");
			return -1;
		}
		Appendlist(head, name, surname, birthYear);
		
	}

	fclose(open);
	return 0;
}