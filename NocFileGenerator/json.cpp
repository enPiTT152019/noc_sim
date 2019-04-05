#include <cstdio>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include <pthread.h>


FILE *f = fopen("json.txt", "w");
tm =30;

int procID = 0;
numrouters =2;
int right[numrouters], left[numrouters], top[numrouters], bottom[numrouters], local[numrouters], countMes[numrouters];






//node

for (i=0; i<= numrouters; i++){


		fprintf(f, "\"pe\":\n" :, text);
		fprintf(f, "{\n", text);
		fprintf(f, "\t\"id\":\"" + std::to_string(data.source[i]) + ",\"\n" ,text);
		
		

		if(neighborTop(src.x[i],src.y[y]>0)) {

			fprintf(f, "\t\"top\":""\"" + std::to_string(src.x[i]) + std::to_string(neighborTop(src.x[i],src.y[i])) + """\""",\n" , text);

		}

		if((neighborBotom(src.x[i],src.y[y]>0).c_str()){
			fprintf(f, "\t\"bottom\":""\"" + std::to_string(src.x[i]) + std::to_string(neighborBottom(src.x[i],src.y[i])) + """\""",\n", text);

		}

		

		if((neighborRight(src.x[i],src.y[y]>0).c_str()){
			fprintf(f, "\t\"right\":""\""+ std::to_string(neighborRight(src.x[i],src.y[i])) + std::to_string(src.x[i]) + """\""",\n", text);

		}

	    if((neighborLeft(src.x[i],src.y[y]>0).c_str()){
			fprintf(f, "\t\"left\":""\"" + std::to_string(neighborLeft(src.x[i],src.y[i])) + std::to_string(src.x[i]) + """\""",\n", text);

		}


	    fprintf(f, "\t\"local\": proc" + """\"" + procID """\""",\n", text);
        fprintf(f, "\t},\n" text);

    	procID ++;
}


	
	fprintf(f, "}],\n", text
	fprintf(f, "},\n", text);
	fprintf(f, "\t\"communication\":\n" :, text);
	fprintf(f, "\t\"volume\":\n" :, text);
	fprintf(f, "\t[{,\n" text);
	fprintf(f, "\t\"router\":\n" :, text);	
	fprintf(f, "{,\n" text);

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
                	 right[id]=right[id] + 1;;
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

int total =0;
int percR =0;
int percL =0;
int percT =0;
int percB =0;
int percLoc =0;

for(int i =0; i<numrouters;i++){
	total = right[i] + left[i] + top[i] + bottom[i];
	percR = right[i]*100/total;
	percL = left[i]*100/total;
	percT = top[i]*100/total;
	percB = bottom[i]*100/total;
	percLoc = local[i]*100/total;

	fprintf(f, "\t\"id\": ""\"" + std::to_string(src.x[i]) + std::to_string(src.y[i]) + """\""",\n", text);
	fprintf(f, "\t\"message_count\":""\"" + std::to_string(countMes[i]) + """\""",\n", text);
	fprintf(f, "\t\"ports\":\"" "\n", text);
	fprintf(f, "\t{,\n" text);
	fprintf(f, "\t\"top\":""\"" + std::to_string(percT) + "%""\""",\n" , text);	
	fprintf(f, "\t\"bottom\":""\"" + std::to_string(percB) + "%""\""",\n" , text);	
	fprintf(f, "\t\"left\":""\"" + std::to_string(percL) + "%""\""",\n" , text);	
	fprintf(f, "\t\"right\":""\"" + std::to_string(percR) + "%""\""",\n" , text);	
	fprintf(f, "\t\"local\":""\"" + std::to_string(percLoc) + "%""\""",\n" , text);	
}

    
fprintf(f, "},\n", text);
fprintf(f, "},\n" ,text);

fprintf(f, "},\n", text);
fprintf(f, "}],\n" ,text);

fprintf(f, "},\n", text);
fprintf(f, "\t\"communication\":\n" :, text);

fprintf(f, "[{,\n" ,text);
fprintf(f, "\t\"proc\":\n" :, text);

fprintf(f, "{,\n" ,text);


for(int i =0; i<numrouters;i++){
	local[i]
	fprintf(f, "\t\"id\": ""\"" + "Proc"+std::to_string(i)+ """\""",\n", text);
	fprintf(f, "\t\"requests\":""\"" + std::to_string(local[i]) + """\""",\n", text);
}


fprintf(f, "},\n", text);
fprintf(f, "}],\n" ,text);
fprintf(f, "},\n" ,text);
fprintf(f, "}\n" ,text);
fprintf(f, "],\n" ,text);


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

