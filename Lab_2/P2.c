// Student Struct
#include<stdio.h>
struct stud{
	char regno[10];
	char name[100];
	char branch[100];
	char dob[20];
	int marks[5];
	char grade; 
};
int main(){
	struct stud student;
	printf("Enter Student RegNO : ");
	scanf("%s",student.regno);
	printf("Enter Student Name : ");
	scanf("%s",student.name);
	printf("Enter Student Branch : ");
	scanf("%s",student.branch);
	printf("Enter Student DOB :");
	scanf("%s",student.dob);
	for(int i=0;i<5;i++)
	{
		printf("Enter Marks of subject %d : ",i+1);
		scanf("%d",&student.marks[i]);
	}
	float avg;

	for(int i = 0;i<5;i++)
	{
		avg = avg + student.marks[i];
	}
	avg = avg/5;
	if(avg>90){
		student.grade = 'S';}
	else if(avg>80 && avg<90){
		student.grade = 'A';}
	else if(avg>70){
		student.grade = 'B';}
	else if(avg>60){
		student.grade = 'C';}
	else if(avg>50){
		student.grade = 'D';}
	else{
		student.grade = 'F';}

    printf("Stundet Details");
    printf("Stundet Name : %s",student.name);	 
    printf("Stundet Regno : %s",student.regno);
    printf("Stundet Branch : %s",student.branch);
    printf("Stundet Dob : %s",student.dob);
    printf("Stundet Name : %f",avg);
    printf("Stundet Name : %c",student.grade);
    }
