#include<stdio.h>
#include<stdlib.h>
//PRINCIPAL//
//2 log n >> minimum height of Binary Tree
//Balance factor, range level antara kiri dan kanan
// leaf = height = 1
// liat height antara kiri dan kanan, yang paling tinggi +1

//REBALANCING//
// Case 1 : Left - left   = rotate Right >> Single Rotation
// Case 2 : Right - Right = rotate Left >> Single Rotation
// Case 3 : Right - Left  = Rotate Right, Rotate Left
// Case 4 : Left - Right  = Rotate Left, Rotate Right

// kalo punya anak, tergantung, anak sebelah kiri bakal ke oper jadi anaknya-anak sebelah kiri setelah di rotate, begitupun sebaliknya
// Patokan dari atas >> liat violation pertama kali muncul >> penyebab node yang terakhir di insert
// Violation >> range of heght nya +-2 atau lebih
// V W X Y

//DELETION//
//prinsip seperti Binary Search Tree
// Setelah delete, harus check Masing2 Parent dari leaf ampe Root, Height nya berapa & Balance Factor nya, kalo belom balance, rebalancing lagi
// bisa dibilang, while (!root) cek parent trooos >> Kalo ga balance, cek yang menjadi penyebab Violation, lalu Rebalance
// Balance Factor = Height anak Kanan - Height anak Kiri

//APP = Visualgo.net/bn/bst
 
struct data {
	int value,height;
	data *left,*right;
}*root = NULL;

int main(){
	return 0;
}
