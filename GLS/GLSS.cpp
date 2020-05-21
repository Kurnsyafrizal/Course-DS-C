#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Menu
{
    char namaMenu[100];
    int type;
    int qty;
    long int price;
};

struct Node
{
    Menu tmp;
    Node *next;
    Node *prev;
};

Node *head = NULL;
Node *tail = NULL;

void add(Menu tmp)
{

    Node *tnode = (Node*)malloc(sizeof(struct Node));

    tnode->data = tmp;
    tnode->next = NULL;
    tnode->prev = NULL;

    if (head == NULL)
    {
        head = tnode;
        tail=tnode;
    }
    else
    {
        tail->next = tnode;
        tnode->prev = tail;
        tail = tnode;
    }
    
}

void menuCof()
{
    Menu tmp [5];
    char tmpNam [100];

    strcpy(tmp[0].namaMenu, "Americano");
    tmp[0].type = 1;
    tmp[0].qty = 24;
    tmp[0].price = 19000;

    strcpy(tmp[1].namaMenu, "Americano");
    tmp[1].type = 0;
    tmp[1].qty = 24;
    tmp[1].price = 19000;

    strcpy(tmp[2].namaMenu, "Americano");
    tmp[2].type = 1;
    tmp[2].qty = 24;
    tmp[2].price = 19000;

    int i=0;
    while (i<3)
    {
        add(tmp[i]);
        i++;
    }
    
}

void see()
{

}

void funAdmin(char loginUser[])
{
    printf("Admin \n");
    printf("Selamat datang %s\n", loginUser);

    see();
}
void funClient(char loginUser[])
{
    printf("Client \n");
    printf("Selamat datang %s\n", loginUser);

    see();

}

int main()
{
    char name[100];

    printf("Masukan Nama Anda : ");
    scanf("%s", name);

    int tmpNam = strcmp(name,"admin");
    if (tmpNam == 0)
    {
        funAdmin(name);
    }
    else
    {
        funClient(name);
    }
    
    
}