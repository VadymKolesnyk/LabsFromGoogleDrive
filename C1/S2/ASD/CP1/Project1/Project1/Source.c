#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>
typedef struct node_tree //узел дерева
{
	int key;
	struct node_tree *l;
	struct node_tree *r;
}node;
typedef struct //структура очереди
{
	node* *array;
	int n, head, tail;
}queue;
node* add(node *tree, int k) //добавление узла в дерево
{
	node *nodeadd = (node*)malloc(sizeof(node));
	if (nodeadd)
	{
		nodeadd->key = k;
		nodeadd->l = NULL;
		nodeadd->r = NULL;
	}
	else
	{
		printf("no memory");
	}
	if (!tree)
	{
		tree = nodeadd;
		return tree;
	}
	node *t = tree;
	do
	{
		if (k <= t->key)
		{
			if (t->l)
			{
				t = t->l;
			}
			else
			{
				t->l = nodeadd;
				return tree;
			}
		}
		else
		{
			if (t->r)
			{
				t = t->r;
			}
			else
			{
				t->r = nodeadd;
				return tree;
			}
		}
	} while (t);
}
void preorder(node* tree,FILE* fo) //обход preorder
{
	node* temp = tree;
	if (temp)
	{
		fprintf(fo, "%d ", temp->key);
		preorder(temp->l,fo);
		preorder(temp->r,fo);
	}
}
void preor(node* tree,int* i) //обход preorder для подсчета листков
{
	node* temp = tree;
	if (temp)
	{
		if (!(temp->l || temp->r))
		{
			(*i)++;
		};
		preor(temp->l,i);
		preor(temp->r,i);
	}
}
void inorder(node* tree, FILE* fo) //обход inorder
{
	node* temp = tree;
	if (temp)
	{
		inorder(temp->l, fo);
		fprintf(fo, "%d ", temp->key);
		inorder(temp->r, fo);
	}
}
void postorder(node* tree, FILE* fo) //обход postorder
{
	node* temp = tree;
	if (temp)
	{
		postorder(temp->l, fo);
		postorder(temp->r, fo);
		fprintf(fo, "%d ", temp->key);
	}
}
int count(node* tree) //подсчет узлов
{
	if (tree)
		return count(tree->l) + count(tree->r) + 1;
	return 0;
}
void enqueue(queue* q, node* n) //добавление элемента в очередь
{
	(q->array)[q->tail] = n;
	q->tail = (q->tail + 1) % (q->n);
}
node* dequeue(queue* q) //удаление элемента с очереди
{
	node* key = (q->array)[q->head];
	q->head = (q->head + 1) % (q->n);
	return key;
}
int levelorder(node* tree, FILE* fo) //обход по уровням
{
	int n = count(tree) + 1;
	queue* q = NULL;
	q = (queue*)malloc(sizeof(queue));
	if (!q) return 1;
	q->array = (node**)malloc(n * sizeof(node*));
	if (!q->array) return 1;
	q->n = n;
	q->head = 0;
	q->tail = 0;
	enqueue(q, tree);
	while (q->tail != q->head)
	{
		node* temp = dequeue(q);
		fprintf(fo, "%d ", temp->key);
		if (temp->l) enqueue(q, temp->l);
		if (temp->r) enqueue(q, temp->r);
	};
	return 0;
}
int terminal(node *tree) //подсчет листков дерева
{
	int i = 0;
	preor(tree, &i);
	return i;
}
int main()
{
	SetConsoleOutputCP(1251);
	node *tree = NULL;
	int k = 0;
	FILE *fi = fopen("input.txt", "r");
	while (!feof(fi))
	{
		fscanf(fi, "%d", &k);
		tree = add(tree, k);
	}
	fclose(fi);
	printf("Файл считан удачно\n");
	int variant = -1;
	do
	{
		printf("1 - preorder\n");
		printf("2 - inorder\n");
		printf("3 - postorder\n");
		printf("4 - levelorder\n");
		printf("5 - количество листков\n");
		printf("0 - выход\n");
		scanf("%d",&variant);
		FILE *fo = fopen("output.txt", "a");
			switch (variant)
			{
			case 1: fprintf(fo, "preorder:\n");
				preorder(tree,fo);
				fprintf(fo, "\n");
				break;
			case 2: fprintf(fo, "inorder:\n");
				inorder(tree, fo);
				fprintf(fo, "\n");
				break;
			case 3: fprintf(fo, "postorder:\n");
				postorder(tree, fo);
				fprintf(fo, "\n");
				break;
			case 4: fprintf(fo, "levelorder:\n");
				levelorder(tree, fo);
				fprintf(fo, "\n");
				break;
			case 5: fprintf(fo, "amount of terminals:");
				fprintf(fo, "%d", terminal(tree));
				fprintf(fo, "\n");
				break;
			default:
				break;
			}
			system("cls");
		fclose(fo);
	} while (variant);
	return 0;
}