#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

struct data
{
    char menu[25];
    char type[20];
    int qty;
    int price;
    int status;
    struct data *next;
}*head=NULL, *tail=NULL;

struct data* newNode(char menu[],char type[], int price, int qty){

	struct data *node = (struct data*)malloc(sizeof(struct data));
	
	strcpy(node->menu,menu);
	strcpy(node->type,type);
	node->price = price;
    node->qty=qty;
	node->next = NULL;

	return node;
}

void pushHead(char menu[],char type[],int price, int qty)
{
    struct data *node = newNode(menu,type,price,qty);

     if (head==NULL)
     {
        head =node;
        tail = node;
     }else
     {
        node->next=head;
        head = node;
     } 
}

void pushTail(char menu[],char type[],int price, int qty)
 {
     struct data *node = newNode(menu,type,price,qty);

     if (head==NULL)
     {
        head = tail =node;
     }else
     {
        tail->next=node;
        tail = node;
     } 
 }

void priceList()
{
    int i = 1;
    printf ("\n\n\n\n");
	printf ("\t\t --- Brew Coffe Shop  ---\n");
	printf  ("-------+----------------------+-----------------+--------|\n");
	printf("|%s | %s | %s | %s | %s |\n","No.", "Menu", "Type" ,"Quantity", "Price");
	printf  ("-------+----------------------+------------------+-------|\n");	
	struct data*curr = head;
	while (curr != NULL){
		printf("|%d. | %s | %s | %d | %d |\n",i, curr->menu, curr->type , curr->qty, curr->price);
		curr=curr->next;
		i++;
	}
	printf  ("-------+----------------------+-----------------+--------|\n");
}

void popHead()
{
    if (!head)
    {
        struct data *curr = head;
        if (head == tail)
        {
            head = tail = NULL;
            free(curr);
        }
        else
        {
            head =tail->next;
            free(curr);
        }
        
    }
}

void exitPopAll()
{
    while (!head)
    {
        popHead();
    }
    
}

int main(){

    int option =0;
    int flag =0 ;
    int qty;
    int price;
    char name[25];
    char type[20];
    int status;

    int number;
    do
    {
        int option =0;
        priceList();

        printf ("1.Add Item\n");
		printf ("2.Remove Item\n");
        printf ("3.Show Menu\n");
		printf ("4.Exit\n");
        printf("Input Choose : ");
        scanf("%d", &option); getchar;

        if (option == 1)
        {   
            do
            {
                printf("Input item name : ");
                scanf("%s",name);
                for (int i = 0; i < strlen(name); i++)
                {
                    if (isalpha(name[i]) == ' ')
                    {
                        flag =1;
                    }
                }
            } while (flag=0);
            

           
            printf("Type of Coffe [yes/no] : ");
            scanf("%s",&type);

            int status =  strcmp(type,"yes");
            if (status == 0)
            {
                printf("Coffe");
            }
            else
            {
                printf("Non-Coffe");
            }
            
            
            do
            {
                printf("Insert the quantity of the item : ");
                scanf("%d",&qty);getchar();

            } while (qty <1 || qty > 100);
            
            do
            {
                printf("Insert the price of the item :  ");
                scanf("%d",&price);
            } while (price < 10000 || price > 200000);
			
            
			pushTail(name,type, qty , price);

        }else if(option == 2)
        {
            
        }
        else if (option == 3)
        {
            priceList();
            getchar();
        }
        
        else if (option == 4)
        {
            printf("Thanks the using program..  \n");
            break;
        }
        
        
        

    } while (option > 3);
    


    return 0 ;
}