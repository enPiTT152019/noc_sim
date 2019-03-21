void *processor(void *arg)
{
    pthread_mutex_lock(&mutex);
    unsigned int id = *((unsigned int *) arg);

    for (int i = 0; i < NUM_LINES; i++) {
        if (id->x == datax.destiny[i] && id->y == datay.destiny[i])
            printf("Processor %d %d: %s\n", datax.destiny[i],datax.destiny[i], data.str[i]);
    }
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}
