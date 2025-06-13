#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define CADEIRAS 3

sem_t clientes;
sem_t barbeiro;
pthread_mutex_t mutex;
int esperando = 0;

void* func_cliente(void* arg) {
    pthread_mutex_lock(&mutex);
    if (esperando < CADEIRAS) {
        esperando++;
        printf("Cliente entrou. Clientes esperando: %d\n", esperando);
        sem_post(&clientes);
        pthread_mutex_unlock(&mutex);

        sem_wait(&barbeiro);
        printf("Cliente está cortando o cabelo.\n");
    } else {
        printf("Sala cheia. Cliente foi embora.\n");
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void* func_barbeiro(void* arg) {
    while (1) {
        sem_wait(&clientes);
        pthread_mutex_lock(&mutex);
        esperando--;
        pthread_mutex_unlock(&mutex);

        printf("Barbeiro está cortando o cabelo.\n");
        sleep(2);
        sem_post(&barbeiro);
    }
    return NULL;
}

int main() {
    pthread_t barbeiro_t;
    pthread_t clientes_t[10];

    sem_init(&clientes, 0, 0);
    sem_init(&barbeiro, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&barbeiro_t, NULL, func_barbeiro, NULL);

    for (int i = 0; i < 10; i++) {
        sleep(rand() % 3);
        pthread_create(&clientes_t[i], NULL, func_cliente, NULL);
    }

    for (int i = 0; i < 10; i++) {
        pthread_join(clientes_t[i], NULL);
    }

    pthread_cancel(barbeiro_t); // Força o término após os clientes

    sem_destroy(&clientes);
    sem_destroy(&barbeiro);
    pthread_mutex_destroy(&mutex);

    return 0;
}

