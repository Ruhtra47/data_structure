#include <stdio.h>
#include <stdlib.h>

int solve(int base, int expoente)
{
    if (expoente == 0)
        return 1;

    return base * solve(base, expoente - 1);
}

int main()
{
    int base, expoente;
    scanf("%d %d", &base, &expoente);

    printf("%d\n", solve(base, expoente));
}