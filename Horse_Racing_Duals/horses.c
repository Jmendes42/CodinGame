#include <stdlib.h>
#include <stdio.h>

int     cmpr_nr(const void *a, const void *b)
{
    return(*(int *)a - *(int *)b);
}

int     difference(int *horses, int N)
{
    int min = horses[1] - horses[0];

    for (int i = 0; i + 1 < N; i++)
    {
        if (horses[i + 1] - horses[i] < min)
            min = horses[i + 1] - horses[i];
    }
    return (min);
}

int     *horseArray(int N)
{
    int *horses = malloc(sizeof(int) * N);

    for (int i = 0; i < N; i++) 
    {
        int pi;
        scanf("%d", &pi);
        horses[i] = pi;
    }
    return (horses);
}

int     main()
{
    int N;
    scanf("%d", &N);
    int *horses;

    horses = horseArray(N);
    qsort(horses, N, sizeof(int), cmpr_nr);
    printf("%d\n", difference(horses, N));
    free(horses);
    return 0;
}
