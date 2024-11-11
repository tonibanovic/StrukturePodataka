#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>

struct Pol;

typedef struct pol* Polynom;
typedef struct pol {
    int Coeff;  
    int Exp;    
    Polynom Next;
} Polynomal;

void ReadPolynom(Polynom* p, char* ime_dat);
void PrintPolynomial(Polynom p);
void AddPolynoms(Polynom* p1, Polynom p2);
void MultiplyPolynoms(Polynom* p1, Polynom p2);
void InsertInOrder(Polynom* p, int coeff, int exp);

int main() {
    Polynom P1 = NULL, P2 = NULL;

    ReadPolynom(&P1, "Polinomi1.txt");
    ReadPolynom(&P2, "Polinomi2.txt");

    printf("Polinom 1:\n");
    PrintPolynomial(P1);

    printf("Polinom 2:\n");
    PrintPolynomial(P2);

    AddPolynoms(&P1, P2);  
    printf("\nPolinom 1 + Polinom 2:\n");
    PrintPolynomial(P1);

    MultiplyPolynoms(&P1, P2); 
    printf("\nPolinom 1 * Polinom 2:\n");
    PrintPolynomial(P1);

    return 0;
}


void ReadPolynom(Polynom* p, char* ime_dat) {
    FILE* file = fopen(ime_dat, "r");
    if (file == NULL) {
        printf("Error while opening the file\n");
        return;
    }

    int coeff, exp;
    while (fscanf(file, "%d %d", &coeff, &exp) == 2) {
        InsertInOrder(p, coeff, exp);
    }

    fclose(file);
}


void InsertInOrder(Polynom* p, int coeff, int exp) {
    Polynom newNode = (Polynom)malloc(sizeof(Polynomal));
    newNode->Coeff = coeff;
    newNode->Exp = exp;
    newNode->Next = NULL;

    if (*p == NULL || (*p)->Exp < exp) {
        
        newNode->Next = *p;
        *p = newNode;
    }
    else {
       
        Polynom temp = *p;
        while (temp->Next != NULL && temp->Next->Exp > exp) {
            temp = temp->Next;
        }

       
        if (temp->Next != NULL && temp->Next->Exp == exp) {
            temp->Next->Coeff += coeff;
            free(newNode);  
        }
        else {
            newNode->Next = temp->Next;
            temp->Next = newNode;
        }
    }
}


void PrintPolynomial(Polynom p) {
    if (p == NULL) {
        printf("Polinom je prazan\n");
        return;
    }

    while (p != NULL) {
        if (p->Coeff > 0 && p != p) {
            printf("+%d*x^%d ", p->Coeff, p->Exp);
        }
        else {
            printf("%d*x^%d ", p->Coeff, p->Exp);
        }
        p = p->Next;
    }
    printf("\n");
}


void AddPolynoms(Polynom* p1, Polynom p2) {
    Polynom temp = p2;
    while (temp != NULL) {
        InsertInOrder(p1, temp->Coeff, temp->Exp);
        temp = temp->Next;
    }
}


void MultiplyPolynoms(Polynom* p1, Polynom p2) {
    Polynom result = NULL, temp1 = *p1, temp2;

    while (temp1 != NULL) {
        temp2 = p2;
        while (temp2 != NULL) {
            int newCoeff = temp1->Coeff * temp2->Coeff;
            int newExp = temp1->Exp + temp2->Exp;
            InsertInOrder(&result, newCoeff, newExp);
            temp2 = temp2->Next;
        }
        temp1 = temp1->Next;
    }

   
    *p1 = result;
}
