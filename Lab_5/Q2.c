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



#include <stdio.h>
#include <stdlib.h>

struct Customer {
    int distance;
    int booking_time;
    int frequency;
    int discount;
};

// Function to compare booking times for sorting
int compare_booking_time(const void *a, const void *b) {
    return (*(struct Customer *)a).booking_time - (*(struct Customer *)b).booking_time;
}

// Function to compare distances for sorting
int compare_distance(const void *a, const void *b) {
    return (*(struct Customer *)a).distance - (*(struct Customer *)b).distance;
}

// Function to compare frequencies for sorting
int compare_frequency(const void *a, const void *b) {
    return (*(struct Customer *)b).frequency - (*(struct Customer *)a).frequency;
}

// Function to schedule deliveries based on nearest customer (case i)
void schedule_nearest_customer(struct Customer customers[], int n) {
    // Sort customers by distance
    qsort(customers, n, sizeof(struct Customer), compare_distance);

    // Display schedule
    printf("\nDelivery Schedule (Nearest Customer First):\n");
    printf("--------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("Customer %d - Distance: %d, Booking Time: %d\n", i + 1, customers[i].distance, customers[i].booking_time);
    }
    printf("\n");
}

// Function to schedule deliveries based on frequency (case ii)
void schedule_frequent_customer(struct Customer customers[], int n) {
    // Sort customers by frequency (priority)
    qsort(customers, n, sizeof(struct Customer), compare_frequency);

    // Display schedule
    printf("\nDelivery Schedule (Frequent Customer First):\n");
    printf("----------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("Customer %d - Frequency: %d, Booking Time: %d\n", i + 1, customers[i].frequency, customers[i].booking_time);
    }
    printf("\n");
}

int main() {
    int n;
    printf("Enter the number of customers: ");
    scanf("%d", &n);

    struct Customer customers[n];

    printf("Enter distance, booking time, frequency, and discount (1 for yes, 0 for no) for each customer:\n");
    for (int i = 0; i < n; i++) {
        printf("Customer %d:\n", i + 1);
        printf("Distance: ");
        scanf("%d", &customers[i].distance);
        printf("Booking Time: ");
        scanf("%d", &customers[i].booking_time);
        printf("Frequency: ");
        scanf("%d", &customers[i].frequency);
        printf("Discount (1 for yes, 0 for no): ");
        scanf("%d", &customers[i].discount);
    }

    // Schedule deliveries based on nearest customer
    schedule_nearest_customer(customers, n);

    // Schedule deliveries based on frequent customer
    schedule_frequent_customer(customers, n);

    return 0;
}
