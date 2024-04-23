 /* 2. i. Consider an online delivery app, which delivers the product to the customer
          who have booked online. The app always chooses the nearest customer first
          for deliver and then next customer. Suppose 2 customers are booking the product
          at the same time then the nearest customer will be chosen first.Consider the
          booking time as arrival time. Choose an appropriate scheduling algorithm to 
          delivery the product in an efficient manner(bustime = distance)

      ii. For the same app compute for the frequent customer will be given discount 
          and consider that the customer is chosen with discount code as highest 
          protity(busttime = distance, priority = frequency)

    Write a program in c to implement 2 scheduling algorithm for case i and ii.
    Display all results on screen.
 */

#include <stdio.h>
#include <stdlib.h>
typedef struct {
    int id;
    int arrival_time;
    int distance;
    int priority; // Priority for case ii
} Customer;

void findWaitingTimeSJF(Customer customers[], int n, int waiting_time[]) {
    int service_time[n];
    service_time[0] = 0;
    waiting_time[0] = 0;

    for (int i = 1; i < n; i++) {
        service_time[i] = service_time[i - 1] + customers[i - 1].distance;
        waiting_time[i] = service_time[i] - customers[i].arrival_time;

        if (waiting_time[i] < 0)
            waiting_time[i] = 0;
    }
}

void findWaitingTimePriority(Customer customers[], int n, int waiting_time[]) {
    int service_time[n];
    service_time[0] = 0;
    waiting_time[0] = 0;

    for (int i = 1; i < n; i++) {
        service_time[i] = service_time[i - 1] + customers[i - 1].distance;
        waiting_time[i] = service_time[i] - customers[i].arrival_time;

        if (waiting_time[i] < 0)
            waiting_time[i] = 0;
    }
}

void findTurnAroundTime(Customer customers[], int n, int waiting_time[], int turnaround_time[]) {
    for (int i = 0; i < n; i++) {
        turnaround_time[i] = customers[i].distance + waiting_time[i];
    }
}

void findAvgTime(Customer customers[], int n) {
    int waiting_time[n], turnaround_time[n];

    findWaitingTimeSJF(customers, n, waiting_time);
    findTurnAroundTime(customers, n, waiting_time, turnaround_time);

    printf("Customer ID\t Arrival Time\t Distance\t Waiting Time\t Turnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t %d\t\t %d\t\t %d\t\t %d\n", customers[i].id, customers[i].arrival_time, 
               customers[i].distance, waiting_time[i], turnaround_time[i]);
    }

    printf("\nGantt Chart:\n");
    for (int i = 0; i < n; i++) {
        printf("| Customer %d ", customers[i].id);
    }
    printf("|\n");

    int total_waiting_time = 0, total_turnaround_time = 0;
    for (int i = 0; i < n; i++) {
        total_waiting_time += waiting_time[i];
        total_turnaround_time += turnaround_time[i];
    }
    printf("\nAverage Waiting Time: %.2f\n", (float)total_waiting_time / (float)n);
    printf("Average Turnaround Time: %.2f\n", (float)total_turnaround_time / (float)n);
}

int main() {
    int n;

    printf("Enter the number of customers: ");
    scanf("%d", &n);

    Customer *customers = (Customer*)malloc(n * sizeof(Customer));

    for (int i = 0; i < n; i++) {
        customers[i].id = i + 1;
        printf("\nEnter details for Customer %d:\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &customers[i].arrival_time);
        printf("Distance: ");
        scanf("%d", &customers[i].distance);
        // For case ii
        printf("Priority/Frequency: ");
        scanf("%d", &customers[i].priority);
    }

    printf("\nResults for SJF (Shortest Job First):\n");
    findAvgTime(customers, n);

    printf("\nResults for Priority Scheduling:\n");
    findAvgTime(customers, n);

    free(customers);

    return 0;
}




/*
#include <stdio.h>

typedef struct {
    int customer_id;
    int distance;
} Customer;

void nearestCustomerFirst(Customer customers[], int n) {
    printf("Nearest Customer First Algorithm:\n");
    printf("---------------------------------------------------------\n");
    printf("| Customer ID | Distance from Delivery Point | Delivery Order |\n");
    printf("---------------------------------------------------------\n");

    int delivery_order[n];
    int visited[n];
    for (int i = 0; i < n; i++) {
        visited[i] = 0;
    }

    int current_distance = 0;
    for (int i = 0; i < n; i++) {
        int min_distance = 999999; // Initialize to a large value
        int nearest_customer = -1;
        for (int j = 0; j < n; j++) {
            if (!visited[j] && customers[j].distance < min_distance) {
                min_distance = customers[j].distance;
                nearest_customer = j;
            }
        }
        visited[nearest_customer] = 1;
        delivery_order[i] = nearest_customer;
        current_distance += min_distance;

        printf("|     %2d      |            %3d             |       %2d       |\n",
               customers[nearest_customer].customer_id, min_distance, i + 1);
    }

    printf("---------------------------------------------------------\n");
    printf("Total Distance Covered: %d units\n", current_distance);
}

int main() {
    int n;
    printf("Enter the number of customers: ");
    scanf("%d", &n);

    Customer customers[n];
    printf("Enter customer ID and distance from delivery point:\n");
    for (int i = 0; i < n; i++) {
        printf("Customer %d: ", i + 1);
        scanf("%d %d", &customers[i].customer_id, &customers[i].distance);
    }

    nearestCustomerFirst(customers, n);

    return 0;
}



/*
#include <stdio.h>

typedef struct {
    int customer_id;
    int distance;
    int frequency;
} Customer;

void frequentCustomerPriority(Customer customers[], int n) {
    printf("\nFrequent Customer Priority Algorithm:\n");
    printf("---------------------------------------------------------\n");
    printf("| Customer ID | Distance from Delivery Point | Priority |\n");
    printf("---------------------------------------------------------\n");

    int delivery_order[n];
    int visited[n];
    for (int i = 0; i < n; i++) {
        visited[i] = 0;
    }

    int current_distance = 0;
    for (int i = 0; i < n; i++) {
        int max_priority = -1;
        int priority_customer = -1;
        for (int j = 0; j < n; j++) {
            if (!visited[j] && customers[j].frequency > max_priority) {
                max_priority = customers[j].frequency;
                priority_customer = j;
            }
        }
        visited[priority_customer] = 1;
        delivery_order[i] = priority_customer;
        current_distance += customers[priority_customer].distance;

        printf("|     %2d      |            %3d             |    %2d    |\n",
               customers[priority_customer].customer_id, customers[priority_customer].distance,
               customers[priority_customer].frequency);
    }

    printf("---------------------------------------------------------\n");
    printf("Total Distance Covered: %d units\n", current_distance);
}

int main() {
    int n;
    printf("Enter the number of customers: ");
    scanf("%d", &n);

    Customer customers[n];
    printf("Enter customer ID, distance from delivery point, and frequency of purchase:\n");
    for (int i = 0; i < n; i++) {
        printf("Customer %d: ", i + 1);
        scanf("%d %d %d", &customers[i].customer_id, &customers[i].distance, &customers[i].frequency);
    }

    frequentCustomerPriority(customers, n);

    return 0;
}

*/
*/
