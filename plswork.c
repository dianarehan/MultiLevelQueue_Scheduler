#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MID(a, b, c) ((a) > (b) ? ((a) < (c) ? (a) : (b) > (c) ? (b) : (c)) : ((b) < (c) ? (b) : (a) > (c) ? (a) : (c)))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h> 
#include "queue.h"

int insCount=0;
char* programName1="Program_1.txt";
char* programName2="Program_2.txt";
char* programName3="Program_3.txt";
char myInstructionsToMem[9][50];
int o=0;
struct data memory[60];
int memCounter=0;
int quan1=1;
int quan2=2;
int quan3=4;
int quan4=8;
int blockingFlag=0;
char instOp[50] = "";
char x[50] = "";
char y[50] = "";
char z[50] = "";
char content[500] = "";  // Initialize the content array with an empty string
int fileIndex;
int clkCycles;
//our queues
Queue q1;
Queue q2;
Queue q3;
Queue q4;
Queue blocked;

struct mutex{
  int pid;
  int value;//0 or 1 depending on m3 had aw la 0 unavailable 1 you can take it
  Queue queue; 
};

struct mutex userInput;
struct mutex userOutput;
struct mutex file;

//helpers declarartions
char* itoa(int value, char* result, int base);
int determineInsCount(char* program);
void fill(char instruction[]);
void readFromFile(char* program);
void semWait(struct mutex *m, struct data processID);
void semSignal(struct mutex *m,struct data processID);
void print(char* var, char* pid);
void assign(char* newVariable, char* value, char* program);
void getFileNameRead(char* varName, char* pid);
void readFile(char* fileName);
void getFileNameWrite(char* varName, char* value, char* pid);
void writeFile(char* fileName, char* newData);
void printFromTo(int start, int end);
void getStartEnd(char* start, char* end, char* pid);
int get2ndprocessindex();
int get3rdprocessindex();
int getUB(struct data progID);
int getLB(struct data progID);
int getPcIndex(struct data progID);
void setPrority(struct data processID,char* pirority);
void setState(struct data processID,char* state);
void setpcIndex(int pcindex);
void scheduler();
void separate(char instruction[], struct data pid);



void init() {
    initializeQueue(&q1);
    initializeQueue(&q2);
    initializeQueue(&q3);
    initializeQueue(&q4);
    initializeQueue(&blocked);
    initializeQueue(&userInput.queue);
    initializeQueue(&userOutput.queue);
    initializeQueue(&file.queue);
    userInput.value = 1;
    userOutput.value = 1;
    file.value = 1;
}

int main(){
    init();
    int time1;
    int time2;
    int time3;
    int totalCycles=determineInsCount(programName1)+determineInsCount(programName2)+determineInsCount(programName3);
     clkCycles=0;

    printf("Enter the arrival time of the first process\n");
    scanf("%d",&time1);

    printf("Enter the arrival time of the second process\n");
    scanf("%d",&time2);

    printf("Enter the arrival time of the third process\n");
    scanf("%d",&time3);

    struct data lowerBoundary2;
    struct data lowerBoundary3;

    for(int i=0;i<totalCycles;i++){
        int x= MIN(time2,time3);
        if(i==MIN(time1,x)){
            char* program=malloc(50);
            if(i==time1)
                program=programName1;
            else if(i==time2)
                program=programName2;
            else program=programName3;

            myInstructionsToMem[determineInsCount(program)][10];
            readFromFile(program);
            struct data ProcessID;
            ProcessID.name="ID";
            ProcessID.value="1";
            memory[memCounter]=ProcessID;
            memCounter++;
            enqueue(&q1,ProcessID);
            struct data processState;
            processState.name="State:";
            processState.value=malloc(50);
            strcpy(processState.value,"Ready");
            memory[memCounter]=processState;
            memCounter++;

            struct data currentPriority;
            currentPriority.name="currentPriority";
            currentPriority.value=malloc(50);
            strcpy(currentPriority.value,"1");
            memory[memCounter]=currentPriority;
            memCounter++;

            struct data programCounter;
            programCounter.name="PC_1";
            programCounter.value=malloc(10);
            memory[memCounter]=programCounter;
            memCounter++;

            struct data lowerBoundary;
            lowerBoundary.name="lowerB of P1";
            lowerBoundary.value="0";
            memory[memCounter]=lowerBoundary;
            memCounter++;

            struct data upperBoundary;
            upperBoundary.name="upperB of P1";
            upperBoundary.value=malloc(10);
            memory[memCounter]=upperBoundary;
            memCounter++;

            struct data var1;
            var1.name = malloc(sizeof("temp")+1);
            strcpy(var1.name,"temp");
            var1.value=malloc(50);
            strcpy(var1.value,"0");
            memory[memCounter]=var1;
            memCounter++;

            struct data var2;
            var2.name=malloc(sizeof("temp")+1);
            strcpy(var2.name,"temp");
            var2.value=malloc(50);
            strcpy(var2.value,"0");
            memory[memCounter]=var2;
            memCounter++;

            struct data var3;
            var3.name=malloc(sizeof("temp")+1);
            strcpy(var3.name,"temp");
            var3.value=malloc(2);
            strcpy(var3.value,"0");
            memory[memCounter]=var3;
            memCounter++;

            sprintf(programCounter.value, "%d", memCounter);
            struct data ins[insCount];
            for(int i =0;i<insCount;i++){ 
                char* name = malloc(strlen("Instruction ") +5);
                sprintf(name, "%s%d", "Instruction ",i+1);
                ins[i].name = name;
                ins[i].value= malloc(50);
                strcpy(ins[i].value,myInstructionsToMem[i]);
                memory[memCounter]=ins[i];
                memCounter++;
            }
            
            
            sprintf(upperBoundary.value, "%d", memCounter-1);
            insCount=0;    
            o=0; 

            lowerBoundary2.value=malloc(2);
            sprintf(lowerBoundary2.value, "%d", memCounter);
            lowerBoundary2.name="lowerB of P2";
        }

        if(i==MID(time1,time2,time3)){
        char* program=malloc(5);
            if(i==time1)
                program=programName1;
            else if(i==time2)
                program=programName2;
            else program=programName3;
            myInstructionsToMem[determineInsCount(program)][10];
            readFromFile(program);
            struct data ProcessID2;
            ProcessID2.name="ID";
            ProcessID2.value="2";
            memory[memCounter]=ProcessID2;
            memCounter++;
            enqueue(&q1,ProcessID2);
            struct data processState2;
            processState2.name="State:";
            processState2.value=malloc(50);
            strcpy(processState2.value,"Ready");
            memory[memCounter]=processState2;
            memCounter++;

            struct data currentPriority2;
            currentPriority2.name="currentPriority";
            currentPriority2.value=malloc(50);
            strcpy(currentPriority2.value,"1");
            memory[memCounter]=currentPriority2;
            memCounter++;

            struct data programCounter2;
            programCounter2.name="PC_2";
            programCounter2.value=malloc(2);
            memory[memCounter]=programCounter2;
            memCounter++;
            
            memory[memCounter]=lowerBoundary2;
            memCounter++;

            struct data upperBoundary2;
            upperBoundary2.name="upperB of P2";
            upperBoundary2.value=malloc(2);
            memory[memCounter]=upperBoundary2;
            memCounter++;

            struct data var11;
            var11.name=malloc(4);
            strcpy(var11.name,"a");
            var11.value=malloc(50);
            strcpy(var11.value,"777");
            memory[memCounter]=var11;
            memCounter++;

            struct data var22;
            var22.name=malloc(4);
            strcpy(var22.name,"temp");
            var22.value=malloc(50);
            strcpy(var22.value,"0");
            memory[memCounter]=var22;
            memCounter++;

            struct data var33;
            var33.name=malloc(4);
            strcpy(var33.name,"temp");
            var33.value=malloc(50);
            strcpy(var33.value,"0");
            memory[memCounter]=var33;
            memCounter++;

            sprintf(programCounter2.value, "%d", memCounter);
            struct data ins2[insCount];
            for(int i =0;i<insCount;i++){ 
                char* name = malloc(strlen("Instruction ") +5);
                sprintf(name, "%s%d", "Instruction ",i+1);
                ins2[i].name = name;
                ins2[i].value= malloc(50);
                strcpy(ins2[i].value,myInstructionsToMem[i]);
                memory[memCounter]=ins2[i];
                memCounter++;
            }
            
            
            sprintf(upperBoundary2.value, "%d", memCounter-1);
            insCount=0;    
            o=0;
            lowerBoundary3.value=malloc(2);
            sprintf(lowerBoundary3.value, "%d", memCounter);
            lowerBoundary3.name="lowerB of P3";
        } 

        int y= MAX(time1,time2);
        if(i==MAX(time3,y)){
            char* program=malloc(5);
            if(i==time1)
                program=programName1;
            else if(i==time2)
                program=programName2;
            else program=programName3;
            myInstructionsToMem[determineInsCount(program)][10];
            readFromFile(program);
            struct data ProcessID3;
            ProcessID3.name="ID";
            ProcessID3.value="3";
            memory[memCounter]=ProcessID3;
            memCounter++;
            enqueue(&q1,ProcessID3);
            struct data processState3;
            processState3.name="State:";
            processState3.value=malloc(50);
            strcpy(processState3.value,"Ready");
            memory[memCounter]=processState3;
            memCounter++;

            struct data currentPriority3;
            currentPriority3.name="currentPriority";
            currentPriority3.value=malloc(50);
            strcpy(currentPriority3.value,"1");
            memory[memCounter]=currentPriority3;
            memCounter++;

            struct data programCounter3;
            programCounter3.name="PC_3";
            programCounter3.value=malloc(2);
            memory[memCounter]=programCounter3;
            memCounter++;
            
            memory[memCounter]=lowerBoundary3;
            memCounter++;

            struct data upperBoundary3;
            upperBoundary3.name="upperB of P3";
            upperBoundary3.value=malloc(2);
            memory[memCounter]=upperBoundary3;
            memCounter++;

            struct data var111;
            var111.name=malloc(4);
            strcpy(var111.name,"temp");
            var111.value=malloc(50);
            strcpy(var111.value,"0");
            memory[memCounter]=var111;
            memCounter++;

            struct data var222;
            var222.name=malloc(4);
            strcpy(var222.name,"temp");
            var222.value=malloc(50);
            strcpy(var222.value,"0");
            memory[memCounter]=var222;
            memCounter++;

            struct data var333;
            var333.name=malloc(4);
            strcpy(var333.name,"temp");
            var333.value=malloc(50);
            strcpy(var333.value,"0");
            memory[memCounter]=var333;
            memCounter++;

            sprintf(programCounter3.value, "%d", memCounter);

            struct data ins3[insCount];
            for(int i =0;i<insCount;i++){ 
                char* name = malloc(strlen("Instruction ") +5);
                sprintf(name, "%s%d", "Instruction ",i+1);
                ins3[i].name = name;
                ins3[i].value= malloc(5);
                strcpy(ins3[i].value,myInstructionsToMem[i]);
                memory[memCounter]=ins3[i];
                memCounter++;
            }
            
            sprintf(upperBoundary3.value, "%d", memCounter-1);
            insCount=0;    
            o=0;
        } 
        printf("watch out execute is about to happen starting from clock cycle %i\n",clkCycles);
        scheduler();
        clkCycles++;
    }

    printf("<---------------THE GREATEST MEMORY----------->\n");
    printf("<------------printing the pcb for the each process---->\n");
            for(int i=0;i<memCounter;i++){
                printf("name is %s value is ",memory[i].name);
                printf("%s\n",memory[i].value);
            }
    printf("<--------------------enddddd------------------->\n");

    return 0;
}

char* itoa(int value, char* result, int base) {
    if (base < 2 || base > 36) { *result = '\0'; return result; }

    char* ptr = result, *ptr1 = result, tmp_char;
    int tmp_value;

    do {
        tmp_value = value;
        value /= base;
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
    } while ( value );

    if (tmp_value < 0) *ptr++ = '-';
    *ptr-- = '\0';
  
    while(ptr1 < ptr) {
        tmp_char = *ptr;
        *ptr--= *ptr1;
        *ptr1++ = tmp_char;
    }
    return result;
}

int determineInsCount(char* program){
    insCount=0;
    FILE *file = fopen(program, "r");
    if (file == NULL) {
        perror("an error happened while opening the file");
        return -1;
    }
    char line[200];
    while (fgets(line, sizeof(line), file) != NULL) {
        char *newline = strchr(line, '\n');
        if (newline != NULL) {
            *newline = '\0';
        }
        if (strcmp(line, "") == 0) {
            continue;
        }  
        insCount++;        
    }
    fclose(file); 
    return insCount;
}

void fill(char instruction[]){
    strcpy(myInstructionsToMem[o], instruction);
    o++;
}

void readFromFile(char* program){
    FILE *file = fopen(program, "r");
    if (file == NULL) {
        perror("an error happened while opening the file");
        return;
    }
    char line[200];
    while (fgets(line, sizeof(line), file) != NULL) {
        char *newline = strchr(line, '\n');
        if (newline != NULL) {
            *newline = '\0';
        }
        if (strcmp(line, "") == 0) {
            continue;
        }  
        fill(line);       
    }
    fclose(file);
}

void semWait(struct mutex* m, struct data processID) {
    if (m->value == 1) {
        printf("i aquired the resource\n");
        m->pid = atoi(processID.value);
        m->value = 0;
    } 
    else {
        printf("I GOT BLOCKEDD\n");
        enqueue(&m->queue, processID);
        printf("current process id is %s and its state is Blocked\n",processID.value);
        setState(processID,"Blocked");
        blockingFlag=1;
        enqueue(&blocked, processID);
    }
}

void semSignal(struct mutex *m, struct data processID) {
    if (m->pid == atoi(processID.value)) {
        if (isEmpty(&(m->queue))) {
            printf("i'm in semsignal when the queue is empty so releasing resource\n");
            m->value = 1;
            m->pid = 0;
        } else {
            int indexofhighest = 0;
            int highestpriority = 10;
            int currentpriority = 0;
            int queueLength = lengthqueue(&(m->queue));
            struct data processes[queueLength];
            // Dequeue all processes and find the one with the highest priority
            for (int i = 0; i < queueLength; i++) {
                processes[i] = dequeue(&(m->queue));
                if (atoi(processes[i].value) == 1) {
                    currentpriority = atoi(memory[2].value);
                } else if (atoi(processes[i].value) == 2) {
                    currentpriority = atoi(memory[get2ndprocessindex() + 2].value);
                } else if (atoi(processes[i].value) == 3) {
                    currentpriority = atoi(memory[get3rdprocessindex() + 2].value);
                }

                if (currentpriority < highestpriority) {
                    highestpriority = currentpriority;
                    indexofhighest = i;
                }
                //enqueue(&(m->queue),p)
            }
            // Re-enqueue all processes except the one with the highest priority
            for (int i = 0; i < queueLength; i++) {
                if (i != indexofhighest) {
                    enqueue(&(m->queue), processes[i]);
                }
            }
            // Process the highest priority process
            struct data process = processes[indexofhighest];
            int c = lengthqueue(&blocked);
            for (int i = 0; i < c; i++) {
                struct data curr = peekFront(&blocked);
                if (strcmp(curr.value, process.value) == 0) {
                    dequeue(&blocked);
                } else {
                    struct data huh = dequeue(&blocked);
                    enqueue(&blocked, huh);
                }
            }
            m->pid = atoi(process.value);
            switch (highestpriority) {
                case 1:
                    enqueue(&q1, process);
                    setState(process,"Ready");
                    printf("process with ID %s state is now Ready\n",process.value);
                    break;
                case 2:
                    enqueue(&q2, process);
                    setState(process,"Ready");
                    printf("process with ID %s state is now Ready\n",process.value);
                    break;
                case 3:
                    enqueue(&q3, process);
                    setState(process,"Ready");
                    printf("process with ID %s state is now Ready\n",process.value);
                    break;
                case 4:
                    enqueue(&q4, process);
                    setState(process,"Ready");
                    printf("process with ID %s state is now Ready\n",process.value);
                    break;
            }
        }
    }
}

void getFileNameRead(char* varName, char* pid){
    int flag = 0;
    if(strcmp(pid,"1")==0){
        //printf("im in program 1\n");
        for(int i=6; i<9; i++){
            if(strcmp(memory[i].name,varName)==0){
                readFile(memory[i].value);
                flag = 1;
                break;
            }
        }
        if(flag==0){
            printf("i couldn't find the file name in the variables \n");
        }
    }
    else if(strcmp(pid,"2")==0){
        //printf("im in program 2");
        int pid2 = get2ndprocessindex();
        for(int i=pid2+6; i<pid2+9; i++){
            if(strcmp(memory[i].name,varName)==0){
                readFile(memory[i].value);
                flag = 1;
                break;
            }
        }
        if(flag==0){
            printf("i couldn't find the file name in the variables \n");
        }
    }
    else{
        int pid3 = get3rdprocessindex();
        for(int i=pid3+6; i<pid3+9; i++){
            if(strcmp(memory[i].name,varName)==0){
                readFile(memory[i].value);
                flag = 1;
                break;
            }
        }
        if(flag==0){
            printf("i couldn't find the file name in the variables \n");
        }
    }
}

void readFile(char* fileName) {
    printf("my file name is %s\n",fileName);
    FILE *file;
    char buffer[50];      
    size_t content_length = 0; 
    file = fopen(fileName, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        size_t buffer_length = strlen(buffer);
        if (content_length + buffer_length < sizeof(content)) {
            strcat(content, buffer);
            content_length += buffer_length;
        } 
        else {
            fprintf(stderr, "Error: content array is too small to hold the file content.\n");
            fclose(file);
            return;
        }
    }
    if (ferror(file)) {
        perror("Error reading file");
        fclose(file);
        return;
    }
    fclose(file);
    // printf("File content:\n%s\n", content);
}

void assign(char* varName, char* value, char* pid) {
    if(strcmp(pid,"1")==0){
        printf("in program 1\n");
        for(int i=6; i<9; i++){
            if(strcmp(memory[i].name,varName)==0){
                strcpy(memory[i].value,value);
                printf("i found the var \n");
                return;
            }
        }
        for(int j=6; j<9; j++){
            if(strcmp(memory[j].name,"temp")==0){
                strcpy(memory[j].name,varName);
                strcpy(memory[j].value,value);
                return;
            }
        }
    }
    else if(strcmp(pid,"2")==0){
        int pid2 = get2ndprocessindex();
        for(int i=pid2+6; i<pid2+9; i++){
            if(strcmp(memory[i].name,varName)==0){
                strcpy(memory[i].value,value);
                return;
            }
        }
        for(int i=pid2+6; i<pid2+9; i++){
            if(strcmp(memory[i].name,"temp")==0){
                strcpy(memory[i].name,varName);
                strcpy(memory[i].value,value);
                return;
            }
        }
    }
    else{
        int pid3 = get3rdprocessindex();
        for(int i=pid3+6; i<pid3+9; i++){
            if(strcmp(memory[i].name,varName)==0){
                strcpy(memory[i].value,value);
                return;
            }
        }
        for(int i=pid3+6; i<pid3+9; i++){
            if(strcmp(memory[i].name,"temp")==0){
                strcpy(memory[i].name,varName);
                strcpy(memory[i].value,value);
                return;
            }
        }
    }
}

void getFileNameWrite(char* varName, char* content, char* pid){
    int flag1 = 0;
    int flag2 = 0;
    char var[50] = "";
    char val[50] = "";
    if(strcmp(pid,"1")==0){
        for(int i=6; i<9; i++){
            if(strcmp(memory[i].name,varName)==0){
                strcpy(var,memory[i].value);
                flag1 = 1;
                break;
            }
        }
        for(int i=6; i<9; i++){
            if(strcmp(memory[i].name,content)==0){
                strcpy(val,memory[i].value);
                flag2 = 1;
                break;
            }
        }
    }
    else if(strcmp(pid,"2")==0){
        int pid2 = get2ndprocessindex();
        for(int i=pid2+6; i<pid2+9; i++){
            if(strcmp(memory[i].name,varName)==0){
                strcpy(var,memory[i].value);
                flag1 = 1;
                break;
            }
        }
        for(int i=pid2+6; i<pid2+9; i++){
            if(strcmp(memory[i].name,content)==0){
                strcpy(val,memory[i].value);
                flag2 = 1;
                break;
            }
        }
    }
    else{
        int pid3 = get3rdprocessindex();
        for(int i=pid3+6; i<pid3+9; i++){
            if(strcmp(memory[i].name,varName)==0){
                strcpy(var,memory[i].value);
                flag1 = 1;
                break;
            }
        }
        for(int i=pid3+6; i<pid3+9; i++){
            if(strcmp(memory[i].name,varName)==0){
                strcpy(val,memory[i].value);
                flag2 = 1;
                break;
            }
        }
    }

    if(flag1!=0 && flag2!=0){
        writeFile(var,val);
    }
    else{
        printf("i couldn't find the file name/content in the variables \n");
    }
}

void writeFile(char* fileName, char* newData){
  FILE *file = fopen(fileName, "a");
  if (file == NULL) {
    perror("Error opening file");
    return;
  }
  
  int i =fprintf(file, "%s", newData);
  printf("length of the text written is %d\n",i);
  fclose(file);
}

void getStartEnd(char* start, char* end, char* pid){
    int intStart = -999;
    int intEnd = -999;
    
    if(strcmp(pid,"1")==0){
        for(int i=6; i<9; i++){
            if(strcmp(memory[i].name,start)==0){
                intStart = atoi(memory[i].value);
                break;
            }
        }
        for(int i=6; i<9; i++){
            if(strcmp(memory[i].name,end)==0){
                intEnd= atoi(memory[i].value) ;
                break;
            }
        }

    }

    else if(strcmp(pid,"2")==0){
        int pid2 = get2ndprocessindex();
        for(int i=pid2+6; i<pid2+9; i++){
            if(strcmp(memory[i].name,start)==0){
                intStart = atoi(memory[i].value);
                break;
            }
        }
        for(int i=pid2+6; i<pid2+9; i++){
            if(strcmp(memory[i].name,end)==0){
                intEnd= atoi(memory[i].value) ;
                break;
            }
        }

    }

    else{
        int pid3 = get3rdprocessindex();
        for(int i=pid3+6; i<pid3+9; i++){
            if(strcmp(memory[i].name,start)==0){
                intStart = atoi(memory[i].value);
                break;
            }
        }
        for(int i=pid3+6; i<pid3+9; i++){
            if(strcmp(memory[i].name,end)==0){
                intEnd= atoi(memory[i].value) ;
                break;
            }
        }

    }

    if(intStart != -999&&intEnd != -999){
        printFromTo(intStart,intEnd);
    }
    else{
        printf("no start/end variables found");
    }


}

void printFromTo(int start, int end){
    printf("I am printing from %d to %d\n",start, end);
    for(int i=start;  i<=end; i++){
        printf("%d\n",i);
  }
}

void print(char* var,char* pid){
    int flag = 0;
    if(strcmp(pid,"1")==0){
        for(int i=6; i<9; i++){
            if(strcmp(memory[i].name,var)==0){
                printf("------> %s <-----\n",memory[i].value);
                flag = 1;
                break;
            }
        }
    }
    else if(strcmp(pid,"2")==0){
        int pid2 = get2ndprocessindex();
        for(int i=pid2+6; i<pid2+9; i++){
            if(strcmp(memory[i].name,var)==0){
                printf("------> %s <-----\n",memory[i].value);
                flag = 1;
                break;
            }
        }
    }
    else{
        int pid3 = get3rdprocessindex();
        for(int i=pid3+6; i<pid3+9; i++){
            if(strcmp(memory[i].name,var)==0){
                printf("------> %s <-----\n",memory[i].value);
                flag = 1;
                break;
            }
        }
    }
    if(flag==0){
        printf("i couldn't find your variable\n");
    }
}

void separate(char instruction[], struct data pid){
        
    //4 parts = assign b readFile a
    if(sscanf(instruction, "%s %s %s %s", &instOp, &x, &y, &z)==4){
        printf("im assigning to readFile for pid %s\n",pid.value);
        getFileNameRead(&z, pid.value);
        assign(&x,content,pid.value);
    }
    
    //3 parts (assign, writeFile, printFromTo)
    else if(sscanf(instruction, "%s %s %s", &instOp, &x, &y)==3){
        
        // assign
        if(strcmp(instOp, "assign")==0){
            printf("im assigning input for pid %s\n",pid.value);
            printf("Please enter a value\n");
            char input[100]=""; 
            scanf("%s", &input);
            assign(&x,input,pid.value);
        }

        // write
        else if(strcmp(instOp,"writeFile")==0){
            printf("im writing in a file for pid %s\n",pid.value);
            getFileNameWrite(&x, &y, pid.value);
        }

        // printFromTo
        else if(strcmp(instOp,"printFromTo")==0){
            printf("im printing from a to b for pid %s\n",pid.value);
            getStartEnd(&x,&y,pid.value);
        }
    }

    //2 parts (print, readFile, semSignal, semWait)
    else if (sscanf(instruction, "%s %s %s", &instOp, &x, &y)==2){
        
        //print
        if(strcmp(instOp, "print")==0){
            print(&x,pid.value);
        }

        //readFile 
        else if(strcmp(instOp, "readFile")==0){
            printf("im printing a file for pid %s\n",pid.value);
            getFileNameRead(&x, pid.value);
        }

        //semSignal
        else if(strcmp(instOp, "semSignal")==0){
            printf("im id (%s) semSignal-ing\n",pid.value);
             if(strcmp(x,"userInput")==0){
                semSignal(&userInput,pid);
            }
            if(strcmp(x,"userOutput")==0){
                semSignal(&userOutput,pid);
            }
            if(strcmp(x,"file")==0){
                semSignal(&file,pid);
            }
        }

        //semWait
        else if(strcmp(instOp, "semWait")==0){
            printf("i am id (%s) semWait-ing\n",pid.value);
            if(strcmp(x,"userInput")==0){
                semWait(&userInput,pid);
            }
            if(strcmp(x,"userOutput")==0){
                semWait(&userOutput,pid);
            }
            if(strcmp(x,"file")==0){
                semWait(&file,pid);
            }
        }
    }

    memset(instOp,0,sizeof(instOp));
    memset(x,0,sizeof(x));
    memset(y,0,sizeof(y));
    memset(z,0,sizeof(z));
    //memset(content,0,sizeof(content));
}

int get2ndprocessindex(){
    for(int i=0;i<memCounter;i++){
        if(strcmp(memory[i].name,"ID")==0&&strcmp(memory[i].value,"2")==0){
            return i;
        }
    }
}

int get3rdprocessindex(){
    for(int i=0;i<memCounter;i++){
        if(strcmp(memory[i].name,"ID")==0&&strcmp(memory[i].value,"3")==0){
            return i;
        }
    }
}

int getUB(struct data progID){
    if(strcmp(progID.name,"ID")==0&&strcmp(progID.value,"2")==0)
        return get2ndprocessindex()+5;
    if(strcmp(progID.name,"ID")==0&&strcmp(progID.value,"3")==0)
        return get3rdprocessindex()+5;
}

int getLB(struct data progID){
    if(strcmp(progID.name,"ID")==0&&strcmp(progID.value,"2")==0)
        return get2ndprocessindex()+4;
    if(strcmp(progID.name,"ID")==0&&strcmp(progID.value,"3")==0)
        return get3rdprocessindex()+4;
}

int getPcIndex(struct data progID){
    if(strcmp(progID.name,"ID")==0&&strcmp(progID.value,"1")==0)
        return 3;

    else if (strcmp(progID.name,"ID")==0&&strcmp(progID.value,"2")==0)
        return get2ndprocessindex() + 3;

    else if (strcmp(progID.name,"ID")==0&&strcmp(progID.value,"3")==0)
       return get3rdprocessindex() + 3;
    
     
}

void setPrority(struct data processID,char* pirority){
    if(strcmp(processID.name,"ID")==0&&strcmp(processID.value,"1")==0){
        strcpy(memory[2].value,pirority); 
    }
    else if(strcmp(processID.name,"ID")==0&&strcmp(processID.value,"2")==0){
        strcpy(memory[get2ndprocessindex()+2].value,pirority);
    }
    else if(strcmp(processID.name,"ID")==0&&strcmp(processID.value,"3")==0){
        strcpy(memory[get3rdprocessindex()+2].value,pirority);
    }
}

void setState(struct data processID,char* state){
    if(strcmp(processID.name,"ID")==0&&strcmp(processID.value,"1")==0){
            strcpy(memory[1].value,state); 
        }
    else if(strcmp(processID.name,"ID")==0&&strcmp(processID.value,"2")==0){
        strcpy(memory[get2ndprocessindex()+1].value,state);
    }
    else if(strcmp(processID.name,"ID")==0&&strcmp(processID.value,"3")==0){
        strcpy(memory[get3rdprocessindex()+1].value,state);
    }
}

void setpcIndex(int pcindex){
    int curVal = atoi(memory[pcindex].value) + 1;
    char *newVal = malloc(2); 
    sprintf(newVal, "%d", curVal);
    strcpy(memory[pcindex].value, newVal);
}

void execute(struct data progID){
    int pc;
    pc = getPcIndex(progID);
    int instIndex = atoi(memory[pc].value);
    separate(memory[instIndex].value,progID);
    setpcIndex(pc);
}

void printAllQueues(){
printf("<---------------QUE?----------->\n");
displayQueue(&q1);
printf("\n");
displayQueue(&q2);
printf("\n");
displayQueue(&q3);
printf("\n");
displayQueue(&q4);
printf("\n");
printf("<---------------QUE?----------->\n");
}

void scheduler(){//be sure to put this in main; diana make sure when a new process arrives it is put in q1;
    int stopval=0;
    if (!isEmpty(&q1) && quan2==2 && quan3==4 && quan4==8){
        printf("something is in queue 1 so i'm there to execute\n");
        struct data curprocess= peekFront(&q1);
        setState(curprocess,"Running");
        printf("current process id is %s and its state is Running\n",curprocess.value);
        //printAllQueues();
        execute(curprocess);
        
        //printAllQueues();
        printf("current quantum is %d\n",quan1);

        quan1--;
        if (atoi(curprocess.value)==1){
            stopval=atoi(memory[5].value) + 1;
            //printf("current process id in the scheduler is 1\n");
        }
        else if (atoi(curprocess.value)==2){
            stopval=atoi(memory[get2ndprocessindex()+5].value)+1;
            //printf("current process id in the scheduler is 2\n");
        }
        else if (atoi(curprocess.value)==3){
            stopval=atoi(memory[get3rdprocessindex()+5].value)+1; 
            //printf("current process id in the scheduler is 3\n");
        }  
        if (quan1==0 && atoi(memory[getPcIndex(curprocess)].value)!=stopval && blockingFlag==0){//solve the condition
            enqueue(&q2,curprocess);
            setState(curprocess,"Ready");
            setPrority(curprocess,"2");
            dequeue(&q1);
            quan1=1;
            //return;
        }
        if (blockingFlag==1){//solve the condition
            blockingFlag=0;
            //printf("im GETTING BLOCKED HELP ME\n");
            if(quan1==0)
                setPrority(curprocess, "2");
            dequeue(&q1);
            quan1=1;
        }
        if (atoi(memory[getPcIndex(curprocess)].value)==stopval){ //check if this condition is missing
            quan1=1;
            setState(curprocess,"Finished");
            printf("this process with id %s has finished\n",curprocess.value);
            dequeue(&q1);
        }
        printf("After executing in cycle %i the queues hold:\n",clkCycles+1);
        printAllQueues();
    }
     else if (!isEmpty(&q2) && quan1==1 && quan3==4 && quan4==8){
        printf("something is in queue 2 so i'm there to execute\n");
        struct data curprocess= peekFront(&q2);
        //printAllQueues();
        printf("current process id is %s and its state is Running\n",curprocess.value);
        execute(curprocess);
        setState(curprocess,"Running");
        //printf("execute is called\n");
        //printAllQueues();

        quan2--;
        if (atoi(curprocess.value)==1){
            stopval=atoi(memory[5].value) + 1;
            //printf("current process id in scheduler is 1\n");
        }
        else if (atoi(curprocess.value)==2){
            stopval=atoi(memory[get2ndprocessindex()+5].value)+1;
            //printf("current process id in scheduler is 2\n");
        }
        else if (atoi(curprocess.value)==3){
            stopval=atoi(memory[get3rdprocessindex()+5].value)+1; 
            //printf("current process id in scheduler is 3\n");
        }  
        if (quan2==0 && atoi(memory[getPcIndex(curprocess)].value)!=stopval && blockingFlag==0){
            enqueue(&q3,curprocess);
            setPrority(curprocess,"3");
            dequeue(&q2);
            quan2=2;
            //return;
        }
        if (blockingFlag==1){//solve the condition
            blockingFlag=0;
            if(quan2==0)
                setPrority(curprocess, "3");
            //printf("im GETTING BLOCKED HELP ME\n");
            dequeue(&q2);
            quan2=2;
        }
        if (atoi(memory[getPcIndex(curprocess)].value)==stopval){ //check if this condition is missing
            quan2=2;
            printf("this process with id %s has finished\n",curprocess.value);
            setState(curprocess,"Finished");
            dequeue(&q2);
        }
        printf("After executing in cycle %i the queues hold:\n",clkCycles+1);
        printAllQueues();
    }
     else if (!isEmpty(&q3) && quan1==1 && quan2==2 && quan4==8){
        printf("something is in queue 3 so i'm there to execute\n");
        struct data curprocess= peekFront(&q3);
        //printAllQueues();
        printf("current process id is %s and its state is Running\n",curprocess.value);
        execute(curprocess);
        setState(curprocess,"Running");
        //printf("execute is called\n");
        //printAllQueues();

        quan3--;
        if (atoi(curprocess.value)==1){
            stopval=atoi(memory[5].value) + 1;
            //printf("current process id in scheduler is 1\n");
        }
        else if (atoi(curprocess.value)==2){
            stopval=atoi(memory[get2ndprocessindex()+5].value)+1;
            //printf("current process id in scheduler is 2\n");
        }
        else if (atoi(curprocess.value)==3){
            stopval=atoi(memory[get3rdprocessindex()+5].value)+1; 
            //printf("current process id in scheduler is 3\n");
        }  
        if (quan3==0 && atoi(memory[getPcIndex(curprocess)].value)!=stopval && blockingFlag==0){
            enqueue(&q4,curprocess);
            setPrority(curprocess,"4");
            dequeue(&q3);
            quan3=4;
            //return;
        }
        if (blockingFlag==1){//solve the condition
            blockingFlag=0;
            if(quan3==0)
                setPrority(curprocess, "4");
            //printf("im GETTING BLOCKED HELP ME\n");
            dequeue(&q3);
            quan3=4;

        }

        if (atoi(memory[getPcIndex(curprocess)].value)==stopval){ //check if this condition is missing
            quan3=4;
            printf("this process with id %s has finished\n",curprocess.value);
            setState(curprocess,"Finished");
            dequeue(&q3);
        }
        printf("After executing in cycle %i the queues hold:\n",clkCycles+1);
        printAllQueues();
    }
     else if (!isEmpty(&q4) && quan1==1 && quan2==2 && quan3==4){
        printf("something is in queue 4 so i'm there to execute\n");
        struct data curprocess= peekFront(&q4);
        //printAllQueues();
        printf("current process id is %s and its state is Running\n",curprocess.value);
        execute(curprocess);
        setState(curprocess,"Running");
        //printf("execute is called \n");
        //printAllQueues();
        quan4--;
        if (atoi(curprocess.value)==1){
            stopval=atoi(memory[5].value) + 1;
            //printf("current process id in scheduler is 1\n");
        }
        else if (atoi(curprocess.value)==2){
            stopval=atoi(memory[get2ndprocessindex()+5].value)+1;
            //printf("current process id in scheduler is 2\n");
        }
        else if (atoi(curprocess.value)==3){
            stopval=atoi(memory[get3rdprocessindex()+5].value)+1; 
            //printf("current process id in scheduler is 3\n");
        }  
        if (quan4==0 && atoi(memory[getPcIndex(curprocess)].value)!=stopval && blockingFlag==0){//and blockingflag==0??
            dequeue(&q4);
            enqueue(&q4, curprocess);
            quan4=8;
            //return;
        }
        if ( blockingFlag==1){//solve the condition
            blockingFlag=0;
            //printf("im GETTING BLOCKED HELP ME\n");
            dequeue(&q4);
            quan4=8;
        }
        if (atoi(memory[getPcIndex(curprocess)].value)==stopval){ //check if this condition is missing, diana make sure that the pc can go to mem. boundary +1 for this case, and for other cases upperboundary + 1;
            quan4=8;
            printf("this process with id %s has finished\n",curprocess.value);
            setState(curprocess,"Finished");
            dequeue(&q4);
        }
        printf("After executing in cycle %i the queues hold:\n",clkCycles+1);
        printAllQueues();
    }
    else {
        printf("MLFQ is done\n");

     }
}