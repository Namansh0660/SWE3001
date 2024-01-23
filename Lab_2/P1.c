// Factorial Program
#include<stdio.h>
int fact(int n)
{
    if(n==1)
    {
        return 1;
    }
    else
    {
        return n*fact(n-1);
    }
}
void main()
{
    int n;
    printf("Enter a Number : ");
    scanf("%d",&n);
    int f = fact(n);
    printf("Factorial of %d is = %d\n",n,f);
}
