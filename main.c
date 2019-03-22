#include "defs.h"
#include "router.h"
#include "processor.h"

// TODO:    Número de linha dinâmico.
//          Nome do arquivo dinâmico (input).
//          Número de roteadores depende do input.
//          Transformar decimal para (x, y).
//          Depois disso, escolher tipo de topologia e fazer roteamentos.
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

    for (int i = 0; i < NUM_LINES; i++) {
        fscanf(file, "%d %d \"%[^\"]\" %d", &data.source[i], &data.target[i], data.str[i], &data.end[i]);
    }

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