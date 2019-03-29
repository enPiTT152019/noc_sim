#include "noc.h"

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *router(void *arg)
{
    pthread_mutex_lock(&mutex);
    int id = *((int *) arg);

    for (int i = 0; i < num_lines; i++) {
        if (pe.x[id] != src.x[i] || pe.y[id] != src.y[i]) {
            continue;
        }
        else {
            while (src.x[i] != tgt.x[i]) {
                if (tgt.x[i] > pe.x[id]) {
                    src.x[i] += 1;
                    printf("Message %d sent to East (%d%d).\n", i, src.x[i], src.y[i]);
                }
                else if (tgt.x[i] < pe.x[id]) {
                    src.x[i] -= 1;
                    printf("Message %d sent to West (%d%d).\n", i, src.x[i], src.y[i]);  
                }
            }
            while (src.y[i] != tgt.y[i]) {
                if (tgt.y[i] > pe.y[id]) {
                    src.y[i] += 1;
                    printf("Message %d sent to North (%d%d).\n", i, src.x[i], src.y[i]);  
                }
                else if (tgt.y[i] < pe.y[id]) {
                    src.y[i] -= 1;
                    printf("Message %d sent to South (%d%d).\n", i, src.x[i], src.y[i]);  
                }
            }
        }
        
        /*
        if (data.source[i] < 10) {
            if (pe.x[id] != 0 || pe.y[id] != data.source[i])
                continue;
        }
        else {        
            if ((pe.x[id] != data.source[i] / 10) || (pe.y[id] != data.source[i] % 10))
                continue;
            else {
                if (data.target[i] < 10) {
                    result_x = pe.x[id] - 0;
                    result_y = pe.y[id] - data.target[i];
                }
                else {
                    result_x = pe.x[id] - data.target[i] / 10;
                    result_y = pe.y[id] - data.target[i] % 10;
                }

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
        }
        for (int j = 0; j < result_x; j++) {
            if (signal_x)
                printf("Message sent to East %d%d.\n", (pe.x[j] + 1), pe.y[j]);
            else
                printf("Message sent to West %d%d.\n", (pe.x[j] - 1), pe.y[j]);
        }

        for (int k = 0; k < result_y; k++) {
            if (signal_y)
                printf("Message sent to South %d%d.\n", pe.x[k], (pe.y[k] + 1));
            else
                printf("Message sent to North %d%d.\n", pe.x[k], (pe.y[k] - 1));
        }
        */
    }

    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}

void *processor(void *arg)
{
    pthread_mutex_lock(&mutex);
    int id = *((int *) arg);

    for (int i = 0; i < num_lines; i++) {
        if (pe.x[id] == tgt.x[i] && pe.y[id] == tgt.y[i]) {
            printf("Processor %d%d: %s\n", pe.x[i], pe.y[i], data.str[i]);
        }
        else {
            continue;
        }
    }

    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}
