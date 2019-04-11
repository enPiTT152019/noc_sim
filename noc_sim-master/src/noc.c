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
                     right[id]=right[id] + 1;
                    printf("Message %d sent to Right (%d%d).\n", i, src.x[i], src.y[i]);
                }
                else if (tgt.x[i] < pe.x[id]) {
                    src.x[i] -= 1;
                    left[id]=left[id] + 1;
                    printf("Message %d sent to Left (%d%d).\n", i, src.x[i], src.y[i]);  
                }
            }
            while (src.y[i] != tgt.y[i]) {
                if (tgt.y[i] > pe.y[id]) {
                    src.y[i] += 1;
                    top[id]=top[id] + 1;
                    printf("Message %d sent to Top (%d%d).\n", i, src.x[i], src.y[i]);  
                }
                else if (tgt.y[i] < pe.y[id]) {
                    src.y[i] -= 1;
                    bottom[id]=bottom[id] + 1;
                    printf("Message %d sent to Bottom (%d%d).\n", i, src.x[i], src.y[i]);  
                }
            }

            countMes[id] = countMes[id] + 1;
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
            local[id] = local[id] + 1;
            printf("Processor %d%d: %s\n", pe.x[i - 1], pe.y[i - 1], data.str[i]);
       
    }

    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}