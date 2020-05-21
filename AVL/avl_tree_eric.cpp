#include <stdio.h>
#include <stdlib.h>

struct node{
	int key;
	int height;
	struct node *left,*right;
}*root;

int getMaxHeight(int a,int b){
	if(a > b) return a;
	else return b;
}

int getHeight(struct node *curr){
	if(curr){
		return curr->height;
	}
	else return 0;
}

int bFactor(struct node *curr){
	if(curr) return getHeight(curr->left) - getHeight(curr->right);
	else return 0;
}

struct node *newNode(int key){
	node *curr = (struct node*)malloc(sizeof(struct node));
	curr->key = key;
	curr->height = 1;
	curr->left = curr->right = NULL;
	
	return curr;
}

struct node *leftRotate(struct node *curr){
	struct node *x = curr->right;
	struct node *y = x->left;
	
	curr->right = y;
	x->left = curr;	
		
	curr->height = getMaxHeight(getHeight(curr->left),getHeight(curr->right)) + 1;
	x->height = getMaxHeight(getHeight(x->left),getHeight(x->right))+1;
	
	return x;
}

struct node *rightRotate(struct node *curr){
	struct node *x = curr->left;
	struct node *y = x->right;
	
	curr->left = y;
	x->right = curr;	
		
	curr->height = getMaxHeight(getHeight(curr->left),getHeight(curr->right)) + 1;
	x->height = getMaxHeight(getHeight(x->left),getHeight(x->right))+1;
	
	return x;
}

struct node *insert(struct node *curr,int key){
	if(!curr) return newNode(key);
	else if(key < curr->key){
		curr->left = insert(curr->left,key);
	}
	else if(key > curr->key){
		curr->right = insert(curr->right,key);
	}
	

	curr->height = getMaxHeight(getHeight(curr->left),getHeight(curr->right)) + 1;
	int b = bFactor(curr);
	

	if(b > 1){
		if(bFactor(curr->left) < 0){
			curr->left = leftRotate(curr->left);
		}
		curr = rightRotate(curr);
	
	}
	else if (b < -1){
		if(bFactor(curr->right) > 0){
			curr->right = rightRotate(curr->right);
		}
		curr = leftRotate(curr);
	}

	
	
	return curr;
}

void printAll(struct node *curr){
	if(curr){
		printAll(curr->left);
		printf("%d ",curr->key);
		printAll(curr->right);
	}
	//printf("\n");
}

struct node *deleteAll(struct node *curr){
	if(curr){
		curr->left = deleteAll(curr->left);
		curr->right = deleteAll(curr->right);
		free(curr);
		return NULL;
	}
}

node *getMaxVal(node *curr){
	if(curr){
		if(curr->right){
			getMaxVal(curr->right);
		}
		else return curr;
	}
}

node *getMinVal(node *curr){
	if(curr){
		if(curr->left){
			getMinVal(curr->left);
		}
		else return curr;
	}
}

node *Delete (node *curr,int key){
	if(curr){
		if(key< curr->key){
			curr->left = Delete(curr->left,key);
		}
		else if (key >curr->key){
			curr->right = Delete(curr->right,key);
		}
		else{
			if(!curr->left && !curr->right)
			{
				free(curr);
					if(curr == root){
						root = NULL;
					}
					return NULL;
				
			}
			else if(!curr->left){
				node *x = curr->right;
				free(curr);
				return x;
			}
			else if(!curr->right){
				node *x = curr->left;
				free(curr);
				return x;
			}
			else{
					if(curr->left){
					node *max = getMaxVal(curr->left);
					curr->key = max->key;
					curr->left = Delete(curr->left,max->key);
					}
					else if(curr->right){
						node *min = getMinVal(curr->right);
						curr->key = min->key;
						curr->right = Delete(curr->right,min->key);
					}
				}	
			}
		}
		else return NULL;
		
	curr->height = getMaxHeight(getHeight(curr->left),getHeight(curr->right)) + 1;
	int b = bFactor(curr);
	

	if(b > 1){
		if(bFactor(curr->left) < 0){
			curr->left = leftRotate(curr->left);
		}
		curr = rightRotate(curr);
	
	}
	else if (b < -1){
		if(bFactor(curr->right) > 0){
			curr->right = rightRotate(curr->right);
		}
		curr = leftRotate(curr);
	}

	return curr;
}

struct node *popAll(struct node *curr){
	if(!curr){
		return NULL;
	}
	curr->left = popAll(curr->left);
	curr->right = popAll(curr->right);
	free(curr);
	return NULL;
}

int main()
{

	root = insert(root,84);
 	root = insert(root,18);
	root = insert(root,10);
	root = insert(root,93);
	root = insert(root,70);
	root = insert(root,5);
	printAll(root);
	
	printf("\n\nAfter Delete:\n");
	//POP 1 BY 1
	root = Delete(root,84);
	root = Delete(root,18);
	root = Delete(root,10);
	root = Delete(root,93);
	root = Delete(root,70);
//	root = Delete(root,5);
	printAll(root);
	
	//POPALL
	root = popAll(root);
	
	printAll(root);
	return 0;
}
