#include<stdio.h>
#include<stdlib.h>

#define t 3
#define MAX_KEY t*2

int height = 1;

struct node{
	int keys[MAX_KEY];
	node *nodes[MAX_KEY];
	int n; //jumlah key
	int childCount; //jumlah anak
	int height;
	node *parent;
	int isLeaf;
	//1 = berarti leaf
	//0 = bukan leaf
};

node *root;

struct node *newNode(node* parent, int isLeaf)
{
	node *temp = (node*)malloc(sizeof(node));
	temp->parent = parent;
	temp->isLeaf = isLeaf;
	temp->height = height;
	temp->n = 0;
	temp->childCount = 0;
	
	for(int a = 0; a < t+2; a++)
	{
		temp->keys[a] = 0;
		temp->nodes[a] = NULL;
	}
	
	return temp;
}

void insertNonRoot(node* curr, int key, int flag);

void insert(int key)
{
	if(root == NULL)
	{
		root = newNode(NULL, 1);
		root->keys[0] = key;
		root->n = 1;
	}
	else
	{
		insertNonRoot(root, key, 0);
	}
}

void insertNonRoot(node *curr, int key, int flag)
{
	if(curr->isLeaf == 1 || flag == 1)
	{
		//tinggal masukin aja
		int i = curr->n-1;
		
		while(i >= 0 && curr->keys[i] > key)
		{
			curr->keys[i+1] = curr->keys[i];
			i--;
		}
		
		curr->keys[i+1] = key;
		curr->n++;
	}
	else
	{
		//cari tempat buat doi
		while(curr->isLeaf == 0)
		{
			int i = curr->n-1;
			
			while(i >= 0 && curr->keys[i] >= key)
			{
				i--;
			}
			
			curr = curr->nodes[i+1];
		}
		
		int i = curr->n-1;
		
		while(i >= 0 && curr->keys[i] > key)
		{
			curr->keys[i+1] = curr->keys[i];
			i--;
		}
		
		curr->keys[i+1] = key;
		curr->n++;
	}
	
	if(curr->n == t)
	{
		if(curr->parent == NULL)
		{
			node *split = newNode(NULL, curr->isLeaf);
			
			height++;
			root = newNode(NULL, 0);
			root->keys[0] = curr->keys[t/2];
			root->n = 1;
			root->childCount = 2;

			split->n = 0;
			
			split->parent = root;
			curr->parent = root;
			
			int b = 0;
			for(int a = t/2+1; a < t; a++)
			{
				split->keys[b] = curr->keys[a];
				split->n++;
				curr->n--;
				b++;	
			}
			
			curr->n--;
			
			root->nodes[0] = curr;
			root->nodes[1] = split;	
			
			if(curr->isLeaf == 0)
			{
				b = 0;
				for(int a = t/2+1; a < t+1; a++)
				{
					split->nodes[b] = curr->nodes[a];
					split->nodes[b]->parent = split;
					curr->nodes[a] = NULL;
					split->childCount++;
					curr->childCount--;
					b++;
				}
			}
			
		}
		else
		{
			node *split = newNode(NULL, curr->isLeaf);
			split->parent = curr->parent;
			split->height = curr->height;
			
			split->n = 0;
			
			int b = 0;
			for(int a = t/2+1; a < t; a++)
			{
				split->keys[b] = curr->keys[a];
				split->n++;
				curr->n--;
				b++;	
			}
			
			curr->n--;
			
			int i = curr->parent->childCount-1;
			
			while(i >= 0 && curr->parent->nodes[i]->keys[0] > split->keys[0])
			{
				curr->parent->nodes[i+1] = curr->parent->nodes[i];
				i--;
			}
			
			curr->parent->nodes[i+1] = split;
			curr->parent->childCount++;
			
			if(curr->isLeaf == 0)
			{
				b = 0;
				for(int a = t/2+1; a < t+1; a++)
				{
					split->nodes[b] = curr->nodes[a];
					split->nodes[b]->parent = split;
					curr->nodes[a] = NULL;
					split->childCount++;
					curr->childCount--;
					b++;
				}
			}
			
			insertNonRoot(curr->parent, curr->keys[t/2], 1);
		}
	}
}

void traverse(node* curr)
{
	for(int a = 0; a < curr->height; a++)
	{
		printf("-");
	}
	for(int a = 0; a < curr->n; a++)
	{
		printf("%d ", curr->keys[a]);
	}
	
	if(curr->isLeaf == 0)
	{
		for(int a = 0; a < t+1; a++)
		{
			if(curr->nodes[a] != NULL)
			{
				printf("\n");
				traverse(curr->nodes[a]);
			}
		}
	}
}

int main()
{
	insert(1);
	insert(2);
	insert(3);
	insert(4);
	insert(5);
	insert(6);
	insert(7);
	insert(8);
	insert(9);
	insert(20);
	insert(11);
	insert(13);
	insert(12);
	insert(21);
	insert(22);
	traverse(root);
}
