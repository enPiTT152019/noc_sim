#include "defs.h"
#include "noc.h"

int main(int argc, char **argv)
{
    FILE *file;
    FILE *f = fopen("json.txt", "w");
    char line[1024];
    unsigned int topology;
    unsigned int kindOutput;;

    file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Error: Could not open the file.\n");
        exit(-1);
    }

    printf("Topology (0: Mesh, 1: Lorem, 2: Ipsum): ");
    scanf("%d", &topology);

    switch (topology) {
    default:
    case 0:
        printf("MESH:\n");
        printf("No. of lines: ");
        scanf("%d", &qt_nodes_x);
        printf("No. of columns: ");
        scanf("%d", &qt_nodes_y);
        printf("Kind of output: (0: Json, 1: XML) ");
        scanf("%d", &kindOutput);
       
    	
		

        num_routers = qt_nodes_x * qt_nodes_y;
        if (qt_nodes_x != qt_nodes_y) {
            printf("Error: Mesh must be squared.\n");
            exit(1);
        }
        if (qt_nodes_x < 2 || qt_nodes_y < 2) {
            printf("Error: Mesh must be greater than 1x1.\n");
            exit(1);
        }

        break;
    case 1:
        printf("Error: Not implemented yet.\n");
        exit(1);
        break;
    case 2:
        printf("Error: Not implemented yet.\n");
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
            printf("Error: Arguments missing in line %d of the input file.\n", i + 2);
            exit(1);
        }

        if (data.source[i] < 0 || data.target[i] < 0) {
            printf("Error: Invalid router address.\n");
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

        if (src.x[i] >= qt_nodes_x || src.y[i] >= qt_nodes_x || tgt.x[i] >= qt_nodes_x || tgt.x[i] >= qt_nodes_x) {
            printf("Error: Invalid router address.\n");
            exit(1);
        }
    }

    pthread_t routers[num_routers], processors[num_routers];

    for (int i = 0; i < num_routers; i++) {
        pe.x[i] = aux_x;
        pe.y[i] = aux_y;

        if (pthread_create(&routers[i], NULL, &router, (void *) &i)) {
            printf("Error: Router %d%d could not be created!\n", pe.x[i], pe.y[i]);
            exit(-2);
        }
        
        
        if (aux_x < qt_nodes_x - 1)
            aux_x++;
        else if (aux_y < qt_nodes_y - 1) {
            aux_x = 0;
            aux_y++;
        }
    }

    if (pthread_create(&processors[0], NULL, &processor, (void *))) {
            printf("Error: Processor could not be created!\n");
            exit(-2);
     }
    
    

    for (int i = 0; i < num_routers; i++) {
        pthread_join(routers[i], NULL);
        pthread_join(processors[0], NULL);
       
    }

	if(!kindOutput)
   		creatJson();
   	else
   		creatXML();
    free(data.str);

    return (0);
}

void creatJson(){
	readNeighborJson();
    execRouterJson();
    execProcJson();

}

void readNeighborJson(){


fprintf(f, "[\n", text);
fprintf(f, "\t{\n", text);
fprintf(f, "\t\t\"project\":\n" , text);
fprintf(f, "{\t\t\n", text);
fprintf(f, "\t\t\t\"noc\":\n" , text);
fprintf(f, "\t\t\t{\n", text);
fprintf(f, "\t\t\t\t\"x\":\"" + std::to_string(qt_nodex_x) ",\"\n" , text);
fprintf(f, "\t\t\t\t\"y\":\"" + std::to_string(qt_nodex_y) ",\"\n" , text);
fprintf(f, "\t\t\t\t\"topology\":\"MESH 2D"",\"\n" ,text);
fprintf(f, "\t\t\t\t\"routers\":\"""\"\n" ,text);
fprintf(f, "\t\t\t\t[{,\n" text);

for (i=0; i<= numrouters; i++){


		fprintf(f, "\t\t\t\t\t\"pe\":\n" , text);
		fprintf(f, "\t\t\t\t\t{\n", text);
		fprintf(f, "\t\t\t\t\t\t\"id\":\"" + std::to_string(data.source[i]) + ",\"\n" ,text);
		
		

		if(neighborTop(src.x[i],src.y[y]>0)) {

			fprintf(f, "\t\t\t\t\t\t\"top\":""\"" + std::to_string(src.x[i]) + std::to_string(neighborTop(src.x[i],src.y[i])) + """\""",\n" , text);

		}

		if(neighborBotom(src.x[i],src.y[y]>0).c_str()){
			fprintf(f, "\t\t\t\t\t\t\"bottom\":""\"" + std::to_string(src.x[i]) + std::to_string(neighborBottom(src.x[i],src.y[i])) + """\""",\n", text);

		}

		

		if(neighborRight(src.x[i],src.y[y]>0).c_str()){
			fprintf(f, "\t\t\t\t\t\t\"right\":""\""+ std::to_string(neighborRight(src.x[i],src.y[i])) + std::to_string(src.x[i]) + """\""",\n", text);

		}

	    if(neighborLeft(src.x[i],src.y[y]>0).c_str()){
			fprintf(f, "\t\t\t\t\t\t\"left\":""\"" + std::to_string(neighborLeft(src.x[i],src.y[i])) + std::to_string(src.x[i]) + """\""",\n", text);

		}


	    fprintf(f, "\t\t\t\t\t\t\"local\": proc" + """\"" + procID """\""",\n", text);
        fprintf(f, "\t\t\t\t\t},\n" text);

	    procID ++;
	}

	fprintf(f, "\t\t\t\t}],\n", text);
	fprintf(f, "\t\t\t},\n", text);


}

void execRouterJson(){



int total =0;
int percR =0;
int percL =0;
int percT =0;
int percB =0;
int percLoc =0;

fprintf(f, "\t\t\t\"communication\":\n" :, text);
fprintf(f, "\t\t\t{,\n", text);
fprintf(f, "\t\t\t\t\"volume\":\n" :, text);
fprintf(f, "\t\t\t\t[{,\n" text);

for(int i =0; i<numrouters;i++){
	total = right[i] + left[i] + top[i] + bottom[i];
	percR = right[i]*100/total;
	percL = left[i]*100/total;
	percT = top[i]*100/total;
	percB = bottom[i]*100/total;
	percLoc = local[i]*100/total;

	fprintf(f, "\t\t\t\t\t\"router\":\n" :, text);	
    fprintf(f, "\t\t\t\t\t{,\n" text);

	fprintf(f, "\t\t\t\t\t\t\"id\": ""\"" + std::to_string(src.x[i]) + std::to_string(src.y[i]) + """\""",\n", text);
	fprintf(f, "\t\t\t\t\t\t\"message_count\":""\"" + std::to_string(countMes[i]) + """\""",\n", text);
	fprintf(f, "\t\t\t\t\t\t\"ports\":\"" "\n", text);
	fprintf(f, "\t\t\t\t\t\t{,\n" text);
	fprintf(f, "\t\t\t\t\t\t\t\"top\":""\"" + std::to_string(percT) + "%""\""",\n" , text);	
	fprintf(f, "\t\t\t\t\t\t\t\"bottom\":""\"" + std::to_string(percB) + "%""\""",\n" , text);	
	fprintf(f, "\t\t\t\t\t\t\t\"left\":""\"" + std::to_string(percL) + "%""\""",\n" , text);	
	fprintf(f, "\t\t\t\t\t\t\t\"right\":""\"" + std::to_string(percR) + "%""\""",\n" , text);	
	fprintf(f, "\t\t\t\t\t\t\t\"local\":""\"" + std::to_string(percLoc) + "%""\""",\n" , text);	
	fprintf(f, "\t\t\t\t\t\t},\n", text);
	fprintf(f, "\t\t\t\t\t},\n" ,text);
}



fprintf(f, "\t\t\t\t}],\n" ,text);

fprintf(f, "\t\t\t},\n", text);
fprintf(f, "\t\t\t\"execution\":\n" :, text);

fprintf(f, "\t\t\t[{,\n" ,text);


}

void execProJJsonson(){

	for(int i =0; i<numrouters;i++){
		fprintf(f, "\t\t\t\t\"proc\":\n" :, text);
		fprintf(f, "\t\t\t\t{,\n" ,text);


		fprintf(f, "\t\t\t\t\t\"id\": ""\"" + "Proc"+std::to_string(i)+ """\""",\n", text);
		fprintf(f,"\t\t\t\t\t\"requests\":""\"" + std::to_string(local[i]) + """\""",\n", text);
		
		fprintf(f, "\t\t\t\t},\n", text);
	}



fprintf(f, "\t\t\t}],\n" ,text);
fprintf(f, "\t\t},\n" ,text);
fprintf(f, "\t}\n" ,text);
fprintf(f, "],\n" ,text);

}

int neighborTop(int x, int y){
	if(y >= qt_nodes_y -1){
		return 0;
		
	}else{

		return  (y +1);


	}

}

int neighborBottom(int x, int y){
	if(y == 0){
		return 0;
	}else{

		return y -1;


	}

}

int neighborRight(int x, int y){
	if(x>=qt_nodes_x -1){
		return 0;
	}else{

		return  x +1;


	}

}

int neighborLeft(int x, int y){
	if(x==0){
		return 0;
	}else{

		return x -1;


		}

}

void creatXML(){

	fprintf(f, "<?xml version=" + "\"1.0\"" + "encoding=" + "\"UTF-8\"" + "?> \n" , text);
fprintf(f, "<project>\n", text);
fprintf(f, "\t<noc>:\n" , text);<x>2</x>
fprintf(f, "\t\t<x>" + std::to_string(qt_nodex_x) + "</x>\n" , text);
fprintf(f, "\t\t<y>" + std::to_string(qt_nodex_y) + "</y>\n" , text);
fprintf(f, "\t\t<topology>Mesh 2D</topology>\n" ,text);
fprintf(f, "\t\t<routers>\n" ,text);
fprintf(f, "\t\t\t<routers>\n" text);

for (i=0; i<= numrouters; i++){


		fprintf(f, "\t\t\t\t <node> \n" , text);
		fprintf(f, "\t\t\t\t\t<id>" + std::to_string(data.source[i]) + "</id>\n" ,text);
		
		

		if(neighborTop(src.x[i],src.y[y]>0)) {

			fprintf(f, "\t\t\t\t\t <top>" + std::to_string(src.x[i]) + std::to_string(neighborTop(src.x[i],src.y[i])) + "</top>\n" , text);

		}

		if(neighborBotom(src.x[i],src.y[y]>0).c_str()){
			fprintf(f, "\t\t\t\t\t\t\"bottom\":""\"" + std::to_string(src.x[i]) + std::to_string(neighborBottom(src.x[i],src.y[i])) + """\""",\n", text);

		}

		

		if(neighborRight(src.x[i],src.y[y]>0).c_str()){
			fprintf(f, "\t\t\t\t\t\t\"right\":""\""+ std::to_string(neighborRight(src.x[i],src.y[i])) + std::to_string(src.x[i]) + """\""",\n", text);

		}

	    if(neighborLeft(src.x[i],src.y[y]>0).c_str()){
			fprintf(f, "\t\t\t\t\t\t\"left\":""\"" + std::to_string(neighborLeft(src.x[i],src.y[i])) + std::to_string(src.x[i]) + """\""",\n", text);

		}


	    fprintf(f, "\t\t\t\t\t\t\"local\": proc" + """\"" + procID """\""",\n", text);
        fprintf(f, "\t\t\t\t\t},\n" text);

	    procID ++;
	}

	fprintf(f, "\t\t\t\t}],\n", text);
	fprintf(f, "\t\t\t},\n", text);


}