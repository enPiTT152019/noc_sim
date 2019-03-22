#include "router.h"

void *router(void *arg)
{
    pthread_mutex_lock(&mutex);
    struct processing_element *id = arg;
    int result_x = 0;
    int result_y = 0;

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
        if (id->x != datax.source[i] || id->y != datay.source[i])
            continue;
        else {
            result_x = id->x - datax.destiny[i];
            result_y = id->y - datay.destiny[i];

            if (result_x < 0) {
                result_x = result_x * -1;
                signal_x = 1;
            }
            else
                signal_x = 0;

            if (result_y < 0) {
                result_y = result_y * -1;
                signal_y = 1;
            }
            else
                signal_y = 0;
        }

        for (int j = 0; j < result_x; j++) {
            if (signal_x)
                printf("Message sent to East %d%d.\n", (id->x + 1), id->y);
            else
                printf("Message sent to West %d%d.\n", (id->x - 1), id->y);
        }

        for (int k = 0; k < result_y; k++) {
            if (signal_y)
                printf("Message sent to South %d%d.\n", id->x, (id->y + 1));
            else
                printf("Message sent to North %d%d.\n", id->x, (id->y - 1));
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
