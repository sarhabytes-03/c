#include <stdio.h>
int main()
{
    int STACKSIZE = 5;
    int STACK[5];
    int TOP, ITEM;

    printf("Enter current TOP (-1 to 4): ");
    scanf("%d", &TOP);

    if (TOP < -1 || TOP >= STACKSIZE) {
        printf("Invalid TOP value!\n");
        return 0;
    }

    if (TOP >= 0) {
        printf("Enter stack elements:\n");
        for (int i = 0; i <= TOP; i++)
            scanf("%d", &STACK[i]);
    }

    printf("Enter ITEM to PUSH: ");
    scanf("%d", &ITEM);

    if (TOP == STACKSIZE - 1)
    {
        printf("OVERFLOW / Stack Full\n");
    }
    else
    {
        TOP = TOP + 1;
        STACK[TOP] = ITEM;
        printf("PUSHED: %d\n", ITEM);
    }

    if (TOP >= 0) {
        printf("Stack: ");
        for (int i = 0; i <= TOP; i++)
            printf("%d ", STACK[i]);
    } else {
        printf("Stack is empty");
    }

    return 0;
}
