#include <stdio.h>
#include <stdlib.h>

#define MAX 5

// Queue Data
int orderQueue[MAX];
int pizzaQueue[MAX];
int front = 0, rear = -1, count = 0;

// Stack Data
int orderStack[MAX];
int pizzaStack[MAX];
int top = -1;

// Pizza Menu
char *pizzaMenu[] = {
    "New York Style",
    "Detroit Pizza",
    "Neapolitan",
    "Vegan Pizza"
};

// Price List
int pizzaPrice[] = {400, 400, 500, 300};

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Add order to queue
void addOrder(int orderID, int pizzaID) {
    if (count == MAX) {
        printf("Queue Overflow! Cannot add more orders.\n");
        return;
    }

    if (rear == MAX - 1)
        rear = 0;
    else
        rear++;

    orderQueue[rear] = orderID;
    pizzaQueue[rear] = pizzaID;
    count++;

    printf("Order %d (%s - %d tk) added to queue.\n",
           orderID, pizzaMenu[pizzaID - 1], pizzaPrice[pizzaID - 1]);
}

// Serve order
int serveOrder(int *pizzaID) {
    if (count == 0) {
        printf("No pending orders.\n");
        return -1;
    }

    int order = orderQueue[front];
    *pizzaID = pizzaQueue[front];
    count--;

    if (count == 0) {
        front = 0;
        rear = -1;
    } else {
        front = (front + 1) % MAX;
    }

    return order;
}

// Push completed
void pushCompleted(int orderID, int pizzaID) {
    if (top == MAX - 1) {
        printf("Stack Overflow! Cannot push.\n");
        return;
    }

    top++;
    orderStack[top] = orderID;
    pizzaStack[top] = pizzaID;

    printf("Order %d (%s - %d tk) is completed.\n",
           orderID, pizzaMenu[pizzaID - 1], pizzaPrice[pizzaID - 1]);
}

// Display pending orders
void displayPending() {
    printf("Pending Orders:\n");

    if (count == 0) {
        printf("None.\n");
        return;
    }

    int i = front;
    for (int c = 0; c < count; c++) {
        printf("%d. Order %d - %s - %d tk\n",
               c + 1,
               orderQueue[i],
               pizzaMenu[pizzaQueue[i] - 1],
               pizzaPrice[pizzaQueue[i] - 1]);
        i = (i + 1) % MAX;
    }
}

// Display completed orders
void displayCompleted() {
    printf("Completed Orders:\n");

    if (top == -1) {
        printf("None.\n");
        return;
    }

    for (int i = top, num = 1; i >= 0; i--, num++) {
        printf("%d. Order %d - %s - %d tk\n",
               num,
               orderStack[i],
               pizzaMenu[pizzaStack[i] - 1],
               pizzaPrice[pizzaStack[i] - 1]);
    }
}

int main() {
    int choice, pizzaChoice, orderID = 1;

    while (1) {
        printf("\n====== FOOD ORDERING SYSTEM ======\n");
        printf("1. Order Pizza\n");
        printf("2. Serve Next Order\n");
        printf("3. Show Pending Orders\n");
        printf("4. Show Completed Orders\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        clearScreen();

        switch (choice) {
        case 1:
            printf("Select Pizza:\n");
            printf("1. New York Style (400 tk)\n");
            printf("2. Detroit Pizza (400 tk)\n");
            printf("3. Neapolitan (500 tk)\n");
            printf("4. Vegan Pizza (300 tk)\n");
            printf("Your choice: ");
            scanf("%d", &pizzaChoice);

            if (pizzaChoice < 1 || pizzaChoice > 4)
                printf("Invalid!\n");
            else {
                addOrder(orderID, pizzaChoice);
                orderID++;
            }
            break;

        case 2: {
            int pizzaID;
            int served = serveOrder(&pizzaID);

            if (served != -1) {
                printf("Serving Order %d (%s - %d tk)...\n",
                       served,
                       pizzaMenu[pizzaID - 1],
                       pizzaPrice[pizzaID - 1]);

                pushCompleted(served, pizzaID);
            }
            break;
        }

        case 3:
            displayPending();
            break;

        case 4:
            displayCompleted();
            break;

        case 5:
            printf("Goodbye!\n");
            return 0;

        default:
            printf("Invalid choice.\n");
        }

        printf("\nPress Enter to continue...");
        getchar();
        getchar();
        clearScreen();
    }
    return 0;
}
