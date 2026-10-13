#include <stdio.h>

int main()
{
    int MAXSIZE = 5;
    int QUEUE[5];
    int FRONT = 0, REAR = -1, COUNT = 0;
    int ITEM;
    int i, n, pos;


    printf("How many elements in queue? ");
    scanf("%d", &n);

    if (n > MAXSIZE)
    {
        printf("Queue size exceeds limit\n");
        return 0;
    }

    printf("Enter queue elements:\n");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &QUEUE[i]);
        REAR++;
        COUNT++;
    }

    printf("Enter position to dequeue (1 to %d): ", COUNT);
    scanf("%d", &pos);

    if (pos < 1 || pos > COUNT)
    {
        printf("Invalid position\n");
        return 0;
    }


    ITEM = QUEUE[pos - 1];


    for (i = pos - 1; i < COUNT - 1; i++)
    {
        QUEUE[i] = QUEUE[i + 1];
    }

    COUNT--;
    REAR--;

    printf("Dequeued element: %d\n", ITEM);

    return 0;
}
