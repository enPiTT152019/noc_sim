#include "defs.h"
#include "noc.h"

int main(int argc, char **argv)
{
    FILE *file;
    char line[1024];
    unsigned int topology;

    file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        exit(-1);
    }

    printf("Topology (0 - Mesh, 1 - Lorem, 2 - Ipsum): ");
    scanf("%d", &topology);

    switch (topology) {
    case 0:
        printf("MESH:\n");
        printf("No. of lines: ");
        scanf("%d", &qt_nodes_x);
        printf("No. of columns: ");
        scanf("%d", &qt_nodes_y);

        num_routers = qt_nodes_x * qt_nodes_y;
        break;
    case 1:
        printf("Not implemented yet!\n");
        exit(1);
        break;
    case 2:
        printf("Not implemented yet!\n");
        exit(1);
        break;
    }

    for (int c = getc(file); c != EOF; c = getc(file)) {
        if (c == '\n')
            num_lines++;
    }

    rewind(file);

    for (int i = 0; i < 2; i++) {
        num_lines--;
        fgets(line, sizeof(line), file);
    }

    data.str = malloc(num_lines * sizeof(char*));
    for (int i = 0; i < num_lines; i++)
        data.str[i] = malloc((LENGTH + 1) * sizeof(char)); 

    for (int i = 0; i < num_lines; i++) {        
        if (fscanf(file, "%d %d \"%[^\"]\" %d", &data.source[i], &data.target[i], data.str[i], &data.end[i]) != 4) {
            printf("Error reading file: Arguments missing in line %d.\n", i + 2);
            exit(1);
        }

        if (data.source[i] < 10) {
            src.x[i] = 0;
            src.y[i] = data.source[i];
        }
        else {
            src.x[i] = data.source[i] / 10;
            src.y[i] = data.source[i] % 10;
        }

        if (data.target[i] < 10) {
            tgt.x[i] = 0;
            tgt.y[i] = data.target[i];
        }
        else {
            tgt.x[i] = data.target[i] / 10;
            tgt.y[i] = data.target[i] % 10;
        }
    }

    pthread_t routers[num_routers], processors[num_routers];

    for (int i = 0; i < num_routers; i++) {
        pe.x[i] = aux_x;
        pe.y[i] = aux_y;

        if (pthread_create(&routers[i], NULL, &router, (void *) &i)) {
            printf("Error creating Router %d%d!\n", pe.x[i], pe.y[i]);
            exit(-2);
        }
        if (pthread_create(&processors[i], NULL, &processor, (void *) &i)) {
            printf("Error creating Processor %d%d!\n", pe.x[i], pe.y[i]);
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

    free(data.str);

    return (0);
}