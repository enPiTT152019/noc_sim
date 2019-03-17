#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

// TODO:    Número de linha dinâmico.
//          Nome do arquivo dinâmico (input).
//          Número de roteadores depende do input.
//          Transformar decimal para (x, y).
//          Depois disso, escolher tipo de topologia e fazer roteamentos.

#define NUM_ROUTERS 2
#define NUM_LINES   11
#define LENGTH      30

struct dataline
{
    int source[NUM_LINES];
    int target[NUM_LINES];
    int end[NUM_LINES];
    char **str;
};

struct processing_element
{
    int x, y, id;
};

struct processor
{
    int id;
    char **str;
};

int qt_nodes_x, qt_nodes_y;
struct dataline data;
struct processor cpu;
pthread_t routers[NUM_ROUTERS], processors[NUM_ROUTERS];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *processor(void *arg)
{
    pthread_mutex_lock(&mutex);
    unsigned int id = *((unsigned int *) arg);

    for (int i = 0; i < NUM_LINES; i++) {
        if (id == data.target[i])
            printf("Processor %d: %s\n", id, data.str[i]);
    }
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}

void *router(void *arg)
{
    pthread_mutex_lock(&mutex);
    struct processing_element *id = arg;

    if (pthread_create(&processors[id->id], NULL, &processor, &id->id)) {
        printf("Error creating Processor %d!\n", id->id);
        exit(-2);
    }

    // Trocar id para xy. OK
    // Ler linha.
    // Verificar se this não é source. Se não for, ignora a linha. 
    // Se for, pegar ID do target e realizar cálculo de distância.
    // O resultado será a quantidade de steps nos eixos x e y.
    // Enviar pra porta correta a mensagem e printar a direção.

    for (int i = 0; i < NUM_LINES; i++) {
        if (id->x != data.source[i] || id->y != data.source[i])
            continue;
        else {

        }
    }

    /*
    for (int i = 0; i < NUM_LINES; i++) {
        if (id != data.source[i])
            continue;
        else {
            cpu.id = id;
            cpu.str = malloc(NUM_LINES * sizeof(char*));
            for (int i = 0; i < NUM_LINES; i++)
                cpu.str[i] = malloc((LENGTH + 1) * sizeof(char));
            strcpy(cpu.str[i], data.str[i]);
            if (id == data.target[i])
                printf("Router %d sent to its processor the message: %s\n", id, cpu.str[i]);
            else
                printf("Router %d sent to %d the message: %s\n", id, data.target[i], cpu.str[i]);
        }
    }
    */

    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}

int main (void)
{
    FILE *file;
    int total_columns = 4;
    char line[1024];
    struct processing_element id;

    file = fopen("./input/listamensagens", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        exit(-1);
    }

    for (int i = 0; i < 2; i++)
        fgets(line, sizeof(line), file);

    data.str = malloc(NUM_LINES * sizeof(char*));
    for (int i = 0; i < NUM_LINES; i++)
        data.str[i] = malloc((LENGTH + 1) * sizeof(char)); 

    for (int i = 0; i < NUM_LINES; i++)
        fscanf(file, "%d %d \"%[^\"]\" %d", &data.source[i], &data.target[i], data.str[i], &data.end[i]);

    for (int i = 0; i < NUM_ROUTERS; i++) {
        id.id = i;
        if (pthread_create(&routers[i], NULL, &router, (void *) &id)) {
            printf("Error creating Router %d%d!\n", id.x, id.y);
            exit(-2);
        }

        if (id.x < qt_nodes_x - 1)
            id.x++;
        else if (id.y < qt_nodes_y - 1) {
            id.x = 0;
            id.y++;
        }
        else
            id.y = 0;
    }

    for (int i = 0; i < NUM_ROUTERS; i++) {
        pthread_join(routers[i], NULL);
        pthread_join(processors[i], NULL);
    }

    free(data.str);

    return (0);
}