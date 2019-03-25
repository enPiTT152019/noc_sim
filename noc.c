#include "noc.h"

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *router(void *arg)
{
    pthread_mutex_lock(&mutex);
    struct processing_element *id = arg;
    int result_x = 0;
    int result_y = 0;

    for (int i = 0; i < num_lines; i++) {
        if (data->source[i] < 10) {
            if (id->x[i] != 0 || id->y[i] != data->source[i])
                continue;
        }
        else {        
            if ((id->x[i] != data->source[i] / 10) || (id->y[i] != data->source[i] % 10))
                continue;
            else {
                if (data->target[i] < 10) {
                    result_x = id->x[i] - 0;
                    result_y = id->y[i] - data->target[i];
                }
                else {
                    result_x = id->x[i] - data->target[i] / 10;
                    result_y = id->y[i] - data->target[i] % 10;
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
                printf("Message sent to East %d%d.\n", (id->x[j] + 1), id->y[j]);
            else
                printf("Message sent to West %d%d.\n", (id->x[j] - 1), id->y[j]);
        }

        for (int k = 0; k < result_y; k++) {
            if (signal_y)
                printf("Message sent to South %d%d.\n", id->x[k], (id->y[k] + 1));
            else
                printf("Message sent to North %d%d.\n", id->x[k], (id->y[k] - 1));
        }     
    }

    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}

void *processor(void *arg)
{
    pthread_mutex_lock(&mutex);
    struct processing_element *id = arg;

    for (int i = 0; i < num_lines; i++) {
        if (data->source[i] < 10) {
            if (id->x[i] == 0 && id->y[i] == data->target[i])
                printf("Processor %d%d: %s\n", id->x[i], id->y[i], data->str[i]);
        }
        else {
            if ((id->x[i] == data->target[i] / 10) && (id->y[i] == data->target[i] % 10))
                printf("Processor %d%d: %s\n", id->x[i], id->y[i], data->str[i]);
        }
    }
    
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}
