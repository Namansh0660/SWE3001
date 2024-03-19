/*
1. Consider a ticket counter in a railway station where the people waits in a queue for booking the ticket. 
   The person who arrives first in the queue can buy the ticket first and then the next person, this continues 
   until the queue becomes empty.The order of arrival of a person in the queue decides their chance to buy the 
   ticket.Write a program in C to implement an appropriate scheduling algorithm to calculate the average waiting 
   time and average turn around time,taken by the person in the queue for the booking process. Display the ghant 
   chart to represent the order of the person in the queue and also waiting time and turnaround time for each person.
*/

//First Come First Serve

#include<stdio.h>
 
 int main()
 
{
    int n,bt[20],wt[20],tat[20],at[20],i,j;
    float avwt = 0.0,avtat = 0.0;                             //bt = burst out time 
    printf("Enter total number of people:");                 //wt = waiting time
    scanf("%d",&n);                                          //tat = turn around time
                                                             //avwt = average turn around time
    printf("Enter Process Burst Time\n");                    //avtat = average turn around time
    for(i=0;i<n;i++)
    {
        printf("P[%d]:",i+1);
        scanf("%d",&bt[i]);
    }
    
    printf("\nEnter the Arrival Time\n");
    for(i=0;i<n;i++){
        printf("P[%d]:",i+1);
        scanf("%d",at+i);
    }
    //bubble sort for arrival time ordering
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-i-1;j++){
            if(at[i] > at[j]){
                int temp = at[i];
                at[i] = at[j];
                at[j] = temp;
            }
        }
    }
    
    wt[0]=0;   
 
    for(i=1;i<n;i++)
    {
        wt[i]=0;
        for(j=0;j<i;j++)
            wt[i]+=bt[j];
            wt[i] = wt[i] - at[i];
    }
 
    printf("\nProcess\t\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time");
 
    for(i=0;i<n;i++)
    {
        tat[i]=bt[i]+wt[i];
        avwt+=wt[i];
        avtat+=tat[i];
        printf("\nP[%d]\t\t%d\t\t%d\t\t%d\t\t%d",i+1,at[i],bt[i],wt[i],tat[i]);
    }
 
    avwt=avwt/n;
    avtat = avtat/n;
    printf("\nAverage Waiting Time:%.2lf",avwt);
    printf("\nAverage Turnaround Time:%.2lf",avtat);
    printf("\n\nGhart Chart:\n");
    printf("__________________________________________");
    printf("\n");
    printf("|");
    
    for(int i=0;i<n;i++){
        printf("| P[%d] |",i+1);
    }
    printf("|");
    printf("\n");
    printf("__________________________________________");
    printf("\n");
    return 0;
}
