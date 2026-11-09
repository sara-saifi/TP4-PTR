
#include <stdio.h>
#include <pthread.h>

#define N 1000000

long solde = 10000000;

void *retrait(void *arg)
{
    int montant = *(int *)arg;

    for (int i = 0; i < N; i++) {
        solde = solde - montant;
    }

    return NULL;
}

int main(void)
{
    pthread_t T1, T2;

    int montant1 = 2;
    int montant2 = 3;

    printf("===== PARTIE 1 : RACE CONDITION =====\n");

    printf("Solde initial : %ld DH\n", solde);

    pthread_create(&T1, NULL, retrait, &montant1);
    pthread_create(&T2, NULL, retrait, &montant2);

    pthread_join(T1, NULL);
    pthread_join(T2, NULL);

    printf("Solde final obtenu : %ld DH\n", solde);
    printf("Solde theorique : 5000000 DH\n");

    return 0;
}
