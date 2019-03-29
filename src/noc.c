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
    }

    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}

void *processor(void *arg)
{
    pthread_mutex_lock(&mutex);
    int id = *((int *) arg);

    for (int i = 0; i < num_lines + 1; i++) {
        if (pe.x[id] == tgt.x[i] && pe.y[id] == tgt.y[i]) {
            //printf("Processor %d%d: %s\n", pe.x[i - 1], pe.y[i - 1], data.str[i]);
        }
    }

    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}
