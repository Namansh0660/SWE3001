// Bubble Sorting
#include<stdio.h>
int main(){
	int n;
	printf("Enter Size of array : ");
	scanf("%d",&n);

	int arr[n];
	for(int i=0;i<n;i++){
		printf("Enter Values at index %d : ",(i+1));

		scanf("%d",&arr[i]);
		
		}
	printf("Original Arra\n");

	for(int i=0;i<n;i++){
		printf("%d ",arr[i]);
		}
	printf("\n");	
	for(int i = 0 ; i<n-1;i++){
		for(int j = n-1 ; j>=i ; j--){
			if(arr[i]<arr[j]){
				int temp = arr[i];
				arr[i]=arr[j];
				arr[j]=temp;
			}
		}
	}
	printf("Sorted Array\n");
	for(int i=0;i<n;i++){
		printf("%d ",arr[i]);
	}
	printf("\n"); 
}
