#include <stdio.h>

int heap[100];
int count = 0;

int parentIdx(int index)
{
    return index/2;
}

int anaKanan(int index)
{
    return index*2+1;
}

int anaKiri(int index)
{
    return index*2;
}

void upMin(int index)
{
    if (index <=1)
    {
        return;
    }
    int parent = parentIdx(index);
    if (heap[index] < heap[parent])
    {
        int temp = heap[index];
        heap[index] = heap[parent];
        heap[parent]= temp;
        upMin(parent);
    }
    
    
}

void printHeap()
{   
    int i=1;
    while (i<=count)
    {
        printf("%2d ", heap[i]);
        i++;
    }
    printf("\n");
}

void Insert(int val)
{
    count++;
    heap[count] = val;
    upMin(count);
}

void downHeap(int index)
{
    if(index*2 > count){
        return;
    }
    int kiri = anaKiri(index);
    int kanan = anaKanan(index);

    int small = index;
    if (kiri <=count && heap[kiri] < heap[small])
    {
        small=kiri;
    }
    if (kanan <=count && heap[kanan] < heap[small])
    {
        small=kanan;
    }

    if(small == index)return;
    int temp =heap[index];
    heap[index] = heap[small];
    heap[small]= temp;

    downHeap(small);
}

void hapusHeap()
{
    if (count==0)
    {
        return;
    }
    heap[1]=heap[count];
    count--;
    downHeap(1);
    
}

int main()
{
    Insert(10);
    Insert(20);
    Insert(8);
    Insert(1);

    printHeap();
    hapusHeap();

    printHeap();

}