#include<stdio.h>
#include<stdlib.h>

struct tnode
{
	int data;
	struct tnode *left;
	struct tnode *right;
	int height;
};

int getHeight(struct tnode *root)
{
	//lengkapi code berikut untuk mengembalikan tinggi node
    if (root)
    {
        return root->height; 
    }
    else
    {
        return 0;
    }
}

int maxHeight(int h1, int h2)
{
	return h1>h2?h1:h2;
}

int balancefactor(struct tnode *root)
{
	//lengkapi code berikut untuk mengembalikan balance factor suatu node
	//bf=height left- height right

    // int bf = getHeight(root->left) - getHeight(root->right);

    return getHeight(root->left) - getHeight(root->right);
}

struct tnode * rotateToRight(struct tnode *T)
{
	struct tnode *S=T->left;
	struct tnode *A=S->right;
	
	//lengkapi code berikut untuk memindahkan posisi S dan T
    S->right = T;
    T->left = A;

	//lengkapi code berikut untuk memperbaiki tinggi T dan S
    S->height = maxHeight(getHeight(S->left), getHeight(S->right));
    T->height = maxHeight(getHeight(T->left), getHeight(T->right));
	
	return S;
}

struct tnode * rotateToLeft(struct tnode *T)
{
	struct tnode *S=T->right;
	struct tnode *A=S->left;
	
	//lengkapi code berikut untuk memindahkan posisi S dan T
    S->left=T;
    T->right=A;
	
	//lengkapi code berikut untuk memperbaiki tinggi T dan S
    S->height = maxHeight(getHeight(S->left), getHeight(S->right));
	T->height = maxHeight(getHeight(T->left), getHeight(T->right));

	return S;
}

void push(struct tnode **root,int data)
{
	if(*root==NULL)
	{
		struct tnode *newnode=
		(struct tnode*)malloc(sizeof(struct tnode));
		newnode->data=data;
		newnode->left=NULL;
		newnode->right=NULL;
		newnode->height=1;
		*root=newnode;
	}
	else if(data>(*root)->data)
	{
		push(&(*root)->right,data);
	}
	else
	{
		push(&(*root)->left,data);
	}
	
	(*root)->height=1+maxHeight(getHeight((*root)->left),getHeight((*root)->right));
	
	int bf=balancefactor(*root);
	
	//Case 1: node terdalam terletak pada subtree kiri dari anak kiri node
	if(bf>1 && data<((*root)->left)->data)
	{
		//LL single rotation
		*root=rotateToRight(*root);
	}
	//Case 2: node terdalam terletak pada subtree kanan dari anak kanan node
	if (bf<-1 && data>((*root)->right)->data)
	{
		//RR single rotation
		*root=rotateToLeft(*root);
	}
	//Case 3: node terdalam terletak pada subtree kanan dari anak kiri node
	if(bf>1 && data>((*root)->left)->data)
	{
		//LR double rotation
		(*root)->left=rotateToLeft((*root)->left);
		*root=rotateToRight(*root);
	}
	//Case 4: node terdalam terletak pada subtree kiri dari anak kanan node
	if (bf<-1 && data<((*root)->right)->data)
	{
		//RL double rotation
		(*root)->right=rotateToRight((*root)->right);
		*root=rotateToLeft(*root);
	}
	
}

void preorder(struct tnode *root)
{
	if(root!=NULL)
	{
		printf("%d height=%d\n",root->data,root->height);
		preorder(root->left);
		preorder(root->right);
	}
}

struct tnode* cariMax(struct tnode **root)
{
	struct tnode *curr=*root;
	
	while(curr!=NULL && curr->right!=NULL)
	{
		curr=curr->right;
	}
	
	return curr;
}

void deleteN(struct tnode **root, int data)
{
	if(*root!=NULL)
	{
		if(data<(*root)->data)
		{
			deleteN(&(*root)->left,data);
		}
		else if(data>(*root)->data)
		{
			deleteN(&(*root)->right,data);
		}
		else
		{
			if((*root)->left==NULL)
			{
				
				struct tnode *temp=(*root)->right;
				free(*root);
				*root=temp;
			}
			else if((*root)->right==NULL)
			{
					printf("tinggi del kanan %d\n",(*root)->height);
				struct tnode *temp=(*root)->left;
				free(*root);
				*root=temp;	
			}
			else{
					printf("tinggi del %d\n",(*root)->height);
				struct tnode *temp=cariMax(&(*root)->left);
				
				(*root)->data=temp->data;
				
				deleteN(&(*root)->left,temp->data);	
			}

		}
	
	}	
}

void deleteNode(struct tnode **root, int data)
{
	deleteN(&(*root),data);	
	
	(*root)->height=1+maxHeight(getHeight((*root)->left),getHeight((*root)->right));

	int bf=balancefactor(*root);
	
	//Case 1: LL rotation
	if(bf>1 && balancefactor((*root)->left) >= 0)
	{
		//lengkapi code berikut untuk melakukan LL rotation
        *root=rotateToRight(*root);
	}
	//Case 2: RR rotation
	if (bf<-1 && balancefactor((*root)->right) <= 0)
	{
		//lengkapi code berikut untuk melakukan RR rotation
        *root=rotateToLeft(*root);
	}
	//Case 3: LR rotation
	if(bf>1 && balancefactor((*root)->left) < 0)
	{
		//lengkapi code berikut untuk melakukan LR rotation
        (*root)->left=rotateToLeft((*root)->left);
		*root=rotateToRight(*root);
	}
	//Case 4: RL rotation
	if (bf<-1 && balancefactor((*root)->right)>0)
	{
		//lengkapi code berikut untuk melakukan RL rotation
        (*root)->right=rotateToRight((*root)->right);
		*root=rotateToLeft(*root);
	}		
}

void popall(struct tnode *root)
{
	if(root!=NULL)
	{
		popall(root->left);
		popall(root->right);
		free(root);
	}
}


int main()
{
	struct tnode *root=NULL;
	
	push(&root,1);
	push(&root,3);
	push(&root,2);
	push(&root,4);
	push(&root,5);
	push(&root,6);
	push(&root,7);

	printf("\nPreorder\n");
	preorder(root);
	
	deleteNode(&root,5);
	deleteNode(&root,6);
	deleteNode(&root,7);
	
	printf("\nPreorder after delete 5,6,7\n");
	preorder(root);
	
	popall(root);

	return 0;
}