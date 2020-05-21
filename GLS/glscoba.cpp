#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Menu{
  char name[100];
  int type;
  int quan;
  long int price;
};

struct Node{
  Menu data;
  Node *next;
  Node *prev;
};

Node *head = NULL;
Node *tail = NULL;

int quanMenu = 0;

void add(Menu tnode){
  Node *newNode = (Node*)malloc(sizeof(Node));
  newNode->data = tnode;
  newNode->next = NULL;
  newNode->prev = NULL;
  if(head==NULL){
    head=newNode;
    tail=newNode;
  }
  else{
    tail->next = newNode;
    newNode->prev = tail;
    tail = newNode;
  }
}

void tempMenuCoffee(){

  Menu tnode[5];
  char tmpNode[100];

  strcpy(tnode[0].name,"Americano");
  tnode[0].type = 1;
  tnode[0].quan = 24;
  tnode[0].price = 19000;

  strcpy(tnode[1].name,"Chocolate Baked");
  tnode[1].type = 0;
  tnode[1].quan = 15;
  tnode[1].price = 24000;

  strcpy(tnode[2].name,"Alberto");
  tnode[2].type = 1;
  tnode[2].quan = 7;
  tnode[2].price = 44000;

  int i=0;
  while(i<3){
    add(tnode[i]);
    quanMenu++;
    i++;
  }
}

void display(){
  if(head==NULL)printf("No data\n");
  else{
    Node *curr = head;
    while(curr!= NULL){
      printf("%s\n,curr->data.name");
      if(curr->data.type==1){
        printf("Coffee\n");
      }
      else printf("Non Coffee\n");

      printf("%d\n",curr->data.quan);
      printf("%d\n",curr->data.price);
      curr= curr->next;
    }
  }
}

void Admin(char adm){

}
void Client(){
  display();
  int index=0;
  int qty;
  printf("Jumlah dibeli : ");
  scanf("%d",&qty);
  Node *curr=head;
  int i=0;
  while(i<quanMenu){
    if(i==(index-1))break;
    curr = curr->next;
    i++;
  }
  curr->data.quan = curr->data.quan-qty;
}


int main(){
  char nama[100];

  printf("Enter Your Name : ");

  scanf("%s",nama);
  tempMenuCoffee();
  int temp = strcmp(nama,"admin");

  if(temp==0){
    printf("Admin\n");
  }
  else{
    printf("Client\n");
  }
}
