#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include "time.h"
struct node;


typedef struct node* position;
typedef struct node {

	int value;
	position right;
	position left;

} Node;

position CreateNode(int value); 
position insert(position root, int value);
int inorder(position root);
int preorder(position root);
int postorder(position root);
position search(position root, int value);
position deleteNode(position root, int value);

int main() {
	position root = NULL;
	int n, i, a, value, d, b; 

	printf("Unesite vrijednost korijena stabla: ");
	scanf("%d", &n);
	root = CreateNode(n);

	printf("Unesite koliko zelite elemenata u stablu: ");
	scanf("%d", &a);
	
	printf("Unesite elemente stabla: ");
	for (i = 0; i < a; i++) {
		scanf("%d", &value);
		insert(root, value);
	}

	inorder(root);
	printf("\n");
	preorder(root);
	printf("\n");
	postorder(root);
	printf("\n");

	printf("Unesie koji element zelite pronaci: ");
	scanf("%d", &d);

	search(root, d);

	printf("Unesie koji element zelite izbrisati: ");
	scanf("%d", &b);
	deleteNode(root, b);
	inorder(root);
	
	

	return 0;

}

position CreateNode(int value) {
	position newNode = NULL;
	newNode = (position)malloc(sizeof(Node));

	if (!newNode) {
		printf("Can't allocate memory");
		return NULL;
	}

	newNode->value = value;
	newNode->left = NULL;
	newNode->right = NULL;

	return newNode;

}

position insert(position root, int value) {
	if (root == NULL)
		return CreateNode(value);


	if (value < root->value) { 
		root->left = insert(root->left, value); 
		
	}
	else {
		root->right = insert(root->right, value);
		
	}

	return root;
}

int inorder(position root) {
	if (root) {
		inorder(root->left);
		printf("%d ", root->value);
		inorder(root->right);
	}

	return EXIT_SUCCESS;
 
}

int preorder(position root) {

	if (root) {
		printf("%d ", root->value);
		preorder(root->left);
		preorder(root->right);

	}

	return EXIT_SUCCESS;
}

int postorder(position root) {

	if (root) {
		postorder(root->left);
		postorder(root->right);
		printf("%d ", root->value);
	}

	return EXIT_SUCCESS;
}

position search(position root, int value) {

	if (root == NULL || root->value == value) {
		return root; 
	}

	if (value < root->value) {
		return search(root->left, value);
	}

	return search(root->right, value);

}

position deleteNode(position root, int value) {
	position temp = NULL; 

	if (value < root->value) {
		root->left = deleteNode(root->left, value);
	}
	else if (value > root->value) {
		root->right = deleteNode(root->right, value);
	}
	else {
		if (root->left == NULL) {
			position temp = root->right;
			free(root);
			return temp;
		}
		else if (root->right == NULL) {
			position temp = root->left;
			free(root);
			return temp;
		}

	}

	temp = root->right;
	while (temp->left != NULL)
		temp = temp->left;

	root->value = temp->value;

	root->right = deleteNode(root->right, temp->value);

	return root; 
}