#include <stdio.h>

//minHeap

int heap[1000];
int idx=1;

void insert(int n){
	
	/*
	1. Masukkan n ke array heap[idx]
	2. Cek parent dari heap[idx] sampai root
	3. kalau heap[idx] < parent, swap
	4. idx ++
	*/
	
	//1.
	heap[idx]=n;
	
	//2.
	int curr = idx;
	
	while(curr/2>0){
	//ngecek parent
		if(heap[curr] < heap[curr/2]){
			
			//3. swap
			int temp = heap[curr];
			heap[curr] = heap[curr/2];
			heap[curr/2] = temp;
			
			curr/=2;
			
		}
		else break;
	}
	idx++;

}



int main(){
	insert(6);
	insert(10);
	insert(11);
	insert(1);
	insert(50);	
	
	
	//
	for(int i = 1 ; i <idx ;i++){
		printf("%d ",heap[i]);
	}
	return 0;
}
