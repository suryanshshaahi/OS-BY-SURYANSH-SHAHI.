#include <stdio.h>

int main() {
    int n, m;
    printf("Enter number of processes and resources: ");
    scanf("%d %d", &n, &m);

    int alloc[n][m], max[n][m], avail[m];
    int finish[n], work[m], safeSequence[n];
    int count = 0;

    printf("Enter Allocation Matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

    printf("Enter Max Matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &max[i][j]);

    printf("Enter Available Resources:\n");
    for (int j = 0; j < m; j++)
        scanf("%d", &avail[j]);

    for (int i = 0; i < m; i++)
        work[i] = avail[i];

    for (int i = 0; i < n; i++)
        finish[i] = 0;

    int changed;
    do {
        changed = 0;
        for (int i = 0; i < n; i++)
            {
                if (!finish[i])
                {
                    int j;
                    int canAllocate = 1;
                    for (j = 0; j < m; j++)
                    {
                         int need = max[i][j] - alloc[i][j];
                         if (need > work[j])
                         {
                                canAllocate = 0;
                                break;
                         }
                }

                if (canAllocate)
                {
                    for (int k = 0; k < m; k++)
                        work[k] += alloc[i][k];
                    finish[i] = 1;
                    safeSequence[count++] = i;
                    changed = 1;
                }
            }
        }
    } while (changed);

    int deadlock = 0;
    for (int i = 0; i < n; i++)
    {
            if (!finish[i])
            {
                deadlock = 1;
                printf("Process P%d is in deadlock.\n", i);
            }
        }

        if (!deadlock)
            {
                printf("System is in safe state.\n");
                printf("Safe sequence is: ");
                for (int i = 0; i < count; i++)
                {
                    printf("P%d", safeSequence[i] + 1);
                    if (i != count - 1)
                        printf(" -> ");
                }
            printf("\n");
            } else
            {
                printf("System is in unsafe state.\n");
    }

    return 0;
}


