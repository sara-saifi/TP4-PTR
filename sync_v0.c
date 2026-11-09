#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

// Thread T1 : validation du virement
void *validation(void *arg)
{
    printf("[T1] Validation du virement en cours...\n");

    sleep(1);  // Simulation du temps de traitement

    printf("[T1] Virement VALIDE\n");

    return NULL;
}

// Thread T2 : exécution du virement
void *execution(void *arg)
{
    printf("[T2] Exécution du virement\n");

    return NULL;
}

int main(void)
{
    pthread_t t1, t2;

    // Création de T2 avant T1
    pthread_create(&t2, NULL, execution, NULL);
    pthread_create(&t1, NULL, validation, NULL);

    // Attente de la terminaison des deux threads
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}