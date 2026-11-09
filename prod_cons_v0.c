#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define TAILLE 5
#define N 10

int tampon[TAILLE];
int in = 0, out = 0, compteur = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t non_vide = PTHREAD_COND_INITIALIZER;
pthread_cond_t non_plein = PTHREAD_COND_INITIALIZER;

void *producteur(void *arg)
{
    for (int i = 1; i <= N; i++)
    {
        pthread_mutex_lock(&mutex);
        while (compteur == TAILLE)
        {
            printf("[Producteur] Tampon plein, j'attends...\n");
            pthread_cond_wait(&non_plein, &mutex);
        }
        tampon[in] = i;
        in = (in + 1) % TAILLE;
        compteur++;
        printf("[Producteur] Produit : %d (compteur=%d)\n", i, compteur);
        pthread_cond_signal(&non_vide);
        pthread_mutex_unlock(&mutex);
        sleep(2);
    }
    return NULL;
}

void *consommateur(void *arg)
{
    for (int i = 1; i <= N; i++)
    {
        pthread_mutex_lock(&mutex);
        while (compteur == 0)
        {
            printf("[Consommateur] Tampon vide, j'attends...\n");
            pthread_cond_wait(&non_vide, &mutex);
        }
        int valeur = tampon[out];
        out = (out + 1) % TAILLE;
        compteur--;
        printf("[Consommateur] Consomme : %d (compteur=%d)\n", valeur, compteur);
        pthread_cond_signal(&non_plein);
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
    return NULL;
}

int main(void)
{
    pthread_t prod, cons;
    pthread_create(&prod, NULL, producteur, NULL);
    pthread_create(&cons, NULL, consommateur, NULL);
    pthread_join(prod, NULL);
    pthread_join(cons, NULL);
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&non_vide);
    pthread_cond_destroy(&non_plein);
    return 0;
}
