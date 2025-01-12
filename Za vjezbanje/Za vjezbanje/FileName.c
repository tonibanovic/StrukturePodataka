#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>


typedef struct Cvor* Pozicija;

typedef struct Cvor {

	int el;
	Pozicija next;
	Pozicija prev;
}Cvor; 

void Unosel(Pozicija p, int el);
void Unoseldvo(Pozicija p, int el);
void Printlist(Pozicija p);
void brisiMin(Pozicija p); 
void izbrisi(Pozicija p);
void PrebaciKraj(Pozicija p, int x);


int main() {
	Cvor head = { 0, NULL, NULL};

	/*
	Unosel(&head, 5); 
	Unosel(&head, 10); 
	Unosel(&head, 3);
	Unosel(&head, 3);
	Unosel(&head, 7);
	Unosel(&head, 4);
	Unosel(&head, 4);
	
	Printlist(head.next);  
	
	
	Unosel(&head, 5);
	Unosel(&head, 10);
	Unosel(&head, 3);
	Unosel(&head, 3);
	Unosel(&head, 7);
	Unosel(&head, 4);
	Unosel(&head, 4);
	izbrisi(&head);
	Printlist(head.next);
	
	
	brisiMin(&head);
	Printlist(head.next); 
	*/

	Unoseldvo(&head, 5);   
	Unoseldvo(&head,10);  
	Unoseldvo(&head, 3);    
	Unoseldvo(&head, 7); 
	PrebaciKraj(&head, 3);
	Printlist(head.next);
	
	return 0;
}

void Unosel(Pozicija p, int el) {
	Pozicija q;

	q = (Pozicija)malloc(sizeof(Cvor)); 
	q->el = el; 
	
	while (p->next != NULL) {
		p = p->next;
	}
	q->next = p->next; 
	p->next = q; 

}

void Printlist(Pozicija p) {
	
	Pozicija last = NULL;



	while (p != NULL) {
		printf("%d  ", p->el);
		
		p = p->next; 

	}
	printf("\n");
	
	
	
}
/*/
void brisiMin(Pozicija p) {
	int min = p->next->el;
	Pozicija pret = p;
	Pozicija temp;

	while(p->next != NULL){
		if (p->next->el < min) {
			min = p->next->el;
			pret = p;

		}
		p = p->next;

	}
	
	temp = pret->next;

	pret->next = temp->next;


	free(temp); 

}
*/

void Unoseldvo(Pozicija p, int el) {
	Pozicija q;

	q = (Pozicija)malloc(sizeof(Cvor));

	q->el = el;




	q->next = p->next;
	q->prev = p; 
	p->next = q;

	

	if (p -> next != NULL) {
		p->next->prev = q;
	}
	
}


/*
void izbrisi(Pozicija p) {
	Pozicija reset = p;
	Pozicija temp = p;
	Pozicija pret = p;
	
	while (p->next != NULL) {
		temp = reset; 
		p = p->next;
		while (temp->next != NULL) {
			if (temp->next->el == p->el && temp->next != p) {
				pret = temp->next;
				temp->next = pret->next; 

				free(pret);
			}
			else {
				temp = temp->next;
			}

		}
	

	}

}
*/

void PrebaciKraj(Pozicija p, int x) {
	Pozicija pret = p;
	Pozicija temp = p;


	while (p->next != NULL) {
		if (p->next->el == x) {
			pret = p;
			temp = p->next;
			
		}

		p = p->next;

	}


	pret->next = temp->next;
	temp->next->prev = pret;
	temp->next = p->next;
	p->next = temp;
	temp->prev = p;





}