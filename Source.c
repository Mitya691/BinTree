#define SIZE ( 1000 )

#include <stdio.h>
#include <stdlib.h>

typedef struct _node node;
struct _node
{
	int key;
	char content[SIZE];
	node* left, *middle, * right; 
	node* parent;
};
//БЛОК ВЫВОДВ ДЕРЕВА
//-----------------------------------------------------------------------------
void View(node* root)
{
	if (!root)
		return;
	View(root->middle);
	printf("%s\n", root->content);
	View(root->left);
	View(root->right);
}
//-----------------------------------------------------------------------------

void DestroyTree(node* root)
{
	if (root != NULL) {
		DestroyTree(root->left);
		DestroyTree(root->middle);
		DestroyTree(root->right);
		free(root);
		root = NULL;
	}
}

int LenKey(int number) {
	int counter = 0;
	while (number > 0) {
		number = number / 10;
		counter++;
	}
	return counter;
}

void ComputeDepthTree(node* root, int* max)
{
	int depth;
	int key;
	if (!root)
		return max;
	key = root->key;
	depth = LenKey(key);
	printf("%i", depth);
	if (depth > max) {
		max = depth;
	}

	ComputeDepthTree(root->left, max);
	ComputeDepthTree(root->middle, max);
	ComputeDepthTree(root->right, max);
}
//БЛОК ЗАПОЛНЕНИЯ ДЕРЕВА ПО КЛЮЧУ
//-----------------------------------------------------------------------------
void ReverseArray(int* mas, int size) {
	int intermediate;
	for (int i = 0; i < size / 2; i++) {
		intermediate = mas[i];
		mas[i] = mas[size - 1 - i];
		mas[size - 1 - i] = intermediate;
	}
}

 int SplitKeyOnNum(int key, int* mas) {
	 int i = 0;
	 while (key > 0) {
		 mas[i] = key % 10;
		 key = key / 10;
		 i++;
	}
	 return i;
}

int Add(node** root, char content[], int key){
	int mas_key[100];
	int size = SplitKeyOnNum(key, mas_key); // здесь лежит количество элменетов в ключе
	node* elem; //структура с инфой об элементе
	elem = (node*)malloc(sizeof(node)); //выделяем под нее память
	elem->key = key;
	strcpy(elem->content, content); //копируем переданную строку в функцию в структуру с инфой об элементе
	elem->left = elem->middle = 0;
	elem->right = 0;
	if (key == 1) {
		(*root) = elem;
	}
	for (int i = 0; i < size; i++) {
		if (mas_key[i] == 1 && *root != 0)
			root = &((*root)->left);
		else if (mas_key[i] == 2 && *root != 0)
			root = &((*root)->middle);
		else if(mas_key[i] == 3 && *root != 0)
			root = &((*root)->right);
	}
	(*root) = elem;

}