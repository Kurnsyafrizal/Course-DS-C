#include <stdio.h>
#include <limits.h>


//maxHeap

int heap[1000];
int idx=1;

void insert(int n){
	
	/*
	1. Masukkan n ke array heap[idx]
	2. Cek parent dari heap[idx] sampai root
	3. kalau heap[idx] > parent, swap
	4. idx ++
	*/
	
	
	
	//1.
	heap[idx]=n;
	
	//2.
	int curr = idx;
	
	while(curr/2>0){
	//ngecek parent
		if(heap[curr]>heap[curr/2]){
			
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

//ekstrak -> ngambil
//ambil root dan nilai yang terbesar kedua yang bakal gantiin posisinya
//di manapun nilai terbesar kedua itu berada



int extract(){
	
	
	/*
	1. tampung root
	2. idx--
	3. ambil idx terakhir utk gantiin root
	4. looping sampe idx terakhir
	5. kita tukar child yang lebih besar dari parentnya
	*/	
	
	//1.
	int value = heap[1];
	
	//2.
	idx--;
		
	//3.
	heap[1] = heap[idx];
	
	
	int curr = 1;
	
	
	//4.
	while(curr*2<idx){
		//kenapa curr*2 ? karena buat nyari anaknya
		
		//cek anak kiri
		if(heap[curr*2] > heap[curr*2+1] && heap[curr*2] > heap[curr]){
			//swap anak kiri dan parent
			int temp = heap[curr];
			heap[curr] = heap[curr*2];
			heap[curr*2] = temp;
			
			curr*=2;
		}	
		
		//cek anak kanan
		else if(heap[curr*2+1] > heap[curr*2] && heap[curr*2+1] > heap[curr]){
			//swap anak kanan dan parent
			int temp = heap[curr];
			heap[curr] = heap[curr*2+1];
			heap[curr*2+1] = temp;
			
			curr*=2+1;
		}	
		else break;
		
	}
	return value;
	
}

int findIdx(int n){
	for(int i = 1 ; i<idx ; i++){
		if(n==heap[i]){
//			printf("%d \n\n\n",i);
		return i;
		}
	}
	printf("NOT FOUND!");
	return 0;
}

void remove(int x){
	
	int index = findIdx(x);
	
	heap[index] = INT_MAX;
	
	idx--;
	
//	heap[1] = heap[idx];
	
	
	int curr = 1;
	
	//4.
	while(curr*2<idx){
		//kenapa curr*2 ? karena buat nyari anaknya
		
		//cek anak kiri
		if(heap[curr*2] > heap[curr*2+1] && heap[curr*2] > heap[curr]){
			//swap anak kiri dan parent
			int temp = heap[curr];
			heap[curr] = heap[curr*2];
			heap[curr*2] = temp;
			
			curr*=2;
		}	
		
		//cek anak kanan
		else if(heap[curr*2+1] > heap[curr*2] && heap[curr*2+1] > heap[curr]){
			//swap anak kanan dan parent
			int temp = heap[curr];
			heap[curr] = heap[curr*2+1];
			heap[curr*2+1] = temp;
			
			curr=((curr*2)+1);
		}	
		else break;
		
	}
	
	
	extract();
	
	
}

int main(){
	insert(6);
	insert(10);
	insert(11);
	insert(23);
	insert(50);	
	insert(70);
	insert(3);
	
	
	for(int i = 1 ; i <idx ;i++){
		printf("%d ",heap[i]);
	}
	
	puts("");
//	extract();
	remove(10);
		for(int i = 1 ; i <idx ;i++){
		printf("%d ",heap[i]);
	}
	return 0;
}
