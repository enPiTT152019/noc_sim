void *router(void *arg)
{
    pthread_mutex_lock(&mutex);
    struct processing_element *id = arg;
    int resultX = 0;
    int resultY  = 0; 

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

            resultX = id->x - datax.destiny[i];
            resultY = id->y - datay.destiny[i];

            if(resultX <0){
                resultX = resultX * -1;
                signalX = 1;
            }else{
                signalX = 0;
            }

            if(resultY <0)
                resultY = resultY * -1;
                signalY = 1;

            }else{
                signalY = 0;

            }

            for(int j =0; j <resultX;j++){
                if(signalX){
                    printf("Mensagem enviada pelo Leste %d %d",(id->x+1), id->y);
                }else{
                    printf("Mensagem enviada pelo Oeste %d %d",(id->x-1), id->y);
                }

            }

            for(int k =0; k< resultY; k++){
                 if(signalY){
                    printf("Mensagem enviada pelo Sul %d %d",id->x, (id->y+1));
                 }else{
                    printf("Mensagem enviada pelo Norte %d %d",id->x, (id->y-1));
                }

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

