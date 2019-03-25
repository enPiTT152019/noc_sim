#include "defs.h"
#include "noc.h"

// TODO:
//          Nome do arquivo dinâmico (input).
//          Depois disso, escolher tipo de topologia e fazer roteamentos.
int main(void)
{
    FILE *file;
    char line[1024];
    struct processing_element id;
    struct dataline data;

    file = fopen("./input/testemesh2d.txt", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        exit(-1);
    }

    printf("Topology Mesh:\n");
    printf("No. of lines: ");
    scanf("%d", &qt_nodes_x);
    printf("No. of columns: ");
    scanf("%d", &qt_nodes_y);

    num_routers = qt_nodes_x * qt_nodes_y;

    for (int c = getc(file); c != EOF; c = getc(file)) {
        if (c == '\n')
            num_lines++;
    }

    for (int i = 0; i < 2; i++) {
        num_lines--;
        fgets(line, sizeof(line), file);
    }

    data.source = malloc(num_lines * sizeof(int));
    data.target = malloc(num_lines * sizeof(int));
    data.end = malloc(num_lines * sizeof(int));

    data.str = malloc(num_lines * sizeof(char*));
    for (int i = 0; i < num_lines; i++)
        data.str[i] = malloc((LENGTH + 1) * sizeof(char)); 

    for (int i = 0; i < num_lines; i++) {
        fscanf(file, "%d %d \"%[^\"]\" %d", &data.source[i], &data.target[i], data.str[i], &data.end[i]);

        if (data.source[i] < 10) {
            id.x[i] = 0;
            id.y[i] = data.source[i];
        }
        else {
            id.x[i] = data.source[i] / 10;
            id.y[i] = data.source[i] % 10;
        }
    }

    id.x = malloc(num_routers * sizeof(int));
    id.y = malloc(num_routers * sizeof(int));
    id.id = malloc(num_routers * sizeof(int));

    pthread_t routers[num_routers], processors[num_routers];

    for (int i = 0; i < num_routers; i++) {
        id.id[i] = i;
        if (pthread_create(&routers[i], NULL, &router, (void *) &id)) {
            printf("Error creating Router %d%d!\n", id.x[i], id.y[i]);
            exit(-2);
        }

        if (pthread_create(&processors[i], NULL, &processor, (void *) &id)) {
            printf("Error creating Processor %d%d!\n", id.x[i], id.y[i]);
            exit(-2);
        }

        if (aux_x < qt_nodes_x - 1)
            aux_x++;
        else if (aux_y < qt_nodes_y - 1) {
            aux_x = 0;
            aux_y++;
        }
    }

    for (int i = 0; i < num_routers; i++) {
        pthread_join(routers[i], NULL);
        pthread_join(processors[i], NULL);
    }

    free(data.source);
    free(data.target);
    free(data.end);
    free(data.str);
    free(id.x);
    free(id.y);
    free(id.id);

    return (0);
}