// Duplicate Elements
#include<stdio.h>
int main(){
	int n;
	printf("Size of the array : ");
	scanf("%d",&n);
	
	int arr[n];
	for(int i=0;i<n;i++){
	
		printf("Enter elements at pos %d : ",(i+1));
		scanf("%d",&arr[i]);
		}
	for(int i=0;i<n-1;i++){
		for(int j=i+1;j<n;j++){
			if(arr[i]==arr[j]){


				printf("Duplicate Element Found at %d position : %d \n",(i+1),(j+1));
			}
		}
	}
} 
