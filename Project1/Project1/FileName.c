#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX 1024
#include <stdlib.h> 

typedef struct {
	
	char ime[10];
	char prezime[10];
	double bodovi;

}studenti;

int ReadRows(const char* fileopen);
studenti* zapis(const char* fileopen, int n);
void ispis(studenti* s, int);

int main() {
	int numberofrows = 0, i;
	studenti* s = NULL;

	numberofrows = ReadRows("studenti.txt");
	
	s = zapis("studenti.txt", numberofrows);
	 
	if (numberofrows < 0) {
		printf("Greska u otvaranju datoteke!");
		return 1;
	}

	printf("Datoteka ima %d retka.\n", numberofrows); 

	ispis(s, numberofrows); 
	free(s);
	
	return 0;
}

int ReadRows(const char* filename) {
	int numberofrows = 0;
	FILE* fp = NULL; 
	char buffer[MAX] = { '\0' };
	
	fp = fopen(filename, "r");
	
	if (!fp) {
		return -1;
	}

	while (!feof(fp)) {
		fgets(buffer, MAX, fp);
		numberofrows++;
	}

	rewind(fp);

	return numberofrows; 
}

studenti *zapis(const char* filename, int n) {
	FILE* fp = NULL;
	studenti* zapis;
	int i; 

	fp = fopen(filename, "r");

	if (!fp) {
		return -1;
	}

	zapis = (studenti*)malloc(n * sizeof(studenti)); 
	
	for (i = 0; i < n; i++) {
		fscanf(fp, "%s %s %lf", zapis[i].ime, zapis[i].prezime, &zapis[i].bodovi); 
		
	}

	fclose(fp);
	return zapis;


}

void ispis(studenti* s, int n) {
	double* relativno = NULL;
	int i; 

	relativno = (double*)malloc(n * sizeof(double));
	printf("Podaci za studente:\n");
	for (i = 0; i < n; i++) {
		relativno[i] = (s[i].bodovi / 50) * 100; 
		printf("%s %s %0.2lf\n", s[i].ime, s[i].prezime, relativno[i]); 

	}
	
	free(relativno);
}