#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct data{
	char custName[25];
	char dressName[51];
	int price;
	struct data *next;
}*head=NULL, *tail=NULL;

struct data* newNode(char custName[],char dressName[],int price){

	struct data *node = (struct data*)malloc(sizeof(struct data));
	
	strcpy(node->custName,custName);
	strcpy(node->dressName,dressName);
	node->price = price;
	node->next = NULL;

	return node;
}


void pushTail(char custName[],char dressName[],int price){
	struct data *node = newNode(custName,dressName,price);
	
	if(head==NULL){
		head = tail = node;
	}
	else{
		tail->next = node;
		tail = node;
	}
	
}
void popHead(){
	if (head!=NULL){
		struct data *curr = head;
		if (head == tail ){
			head = tail = NULL;
			free(curr);
		}else {
			head = head->next;
			free(curr);
		}
	}
}
void popAll(){
	while(head!=NULL){
		popHead();
	}
}
void printList(){
	int i = 1;
	printf ("\n\n\n\n\n\n\n\n\n\n");
	printf ("\t\t\t --- QUEUE VIEW ---\n");
	printf  ("-------+----------------------+-----------------+----------|\n");
	printf("|%-5s | %-15s | %-15s | %-15s |\n","No.", "Customer Name", "Dress Name" , "Price");
	printf  ("-------+----------------------+------------------+--------\n");	
	struct data*curr = head;
	while (curr != NULL){
		printf("|%-5d. | %-15s | %-15s | %-15d |\n",i, curr->custName, curr->dressName , curr->price);
		curr=curr->next;
		i++;
	}
		printf  ("-------+----------------------+-----------------+--------|\n");
}

int main(){
	char custName[25];
	char dressName [25];
	int price;
	int option;
	int flag =0 ;
	do {

		int option=0;
		
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		printf("BLUE DRESS SHOP CASHIER QUEUE \n");
		printf("###############################\n");
		
		printf ("1.View Queue\n");
		printf ("2.Add Customer to Queue\n");
		printf ("3.Serve Customer\n");
		printf ("4.Exit\n");
		printf (">> Input Choice : ");
		scanf("%d", &option); getchar();
		
		if (option == 1){
			printList();
			getchar();
		}
		
		else if (option == 2) {
			do {
			printf (" Input Customer Name [3..20] [must be in alphabets]: ");
			scanf ("%s",custName);
			
			for (int i=0; i<strlen(custName);i++){
				if (isalpha(custName[i]) == ' '){
					flag = 1;
				}
			}
			}while (flag ==0);
			printf ("\n");
			
			do{
			printf (" Input Dress Name [3...20]: ");
			scanf ("%s",dressName);
			}while (strlen(dressName)<3 || strlen(dressName)>20);
			printf ("\n");
			
			do{
			printf ("Input Dress Price  [$50..$999]: $ ");
			scanf("%d",&price);
			}while (price <50 || price >999);
			printf ("\n");
				
				
			printf ("\n\n  --- Success to Add Customer into Queue List---\n");
			getchar();
			
			pushTail(custName,dressName,price);
		}
		
		else if (option == 3){
			if (head=tail=NULL){
				printf("--- There is No Customer in Queue ---\n");
			}
			else {
			popHead();
			printf ("--- %s Has Been Served ---",custName);
			}
		}
		else if (option ==4){
			popAll();
			break;
		}
	}while (option >4);
	return 0;
}
