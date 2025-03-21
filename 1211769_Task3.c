#include <stdio.h>
#include <ctype.h>
/*
 * Abalrhman Juber 1211769
 * section 1
 */


struct process{
    int Allocation[10]; // 10 for maximum resource number
    int Request[10];
};
int N; // Number of processes
int R; // Number of Resources

char File_Allocation[255]="C:\\Users\\a-ahm\\OneDrive\\Desktop\\files\\Allocation.csv";
char File_Request[255]="C:\\Users\\a-ahm\\OneDrive\\Desktop\\files\\Request.csv";
char File_Available[255] = "C:\\Users\\a-ahm\\OneDrive\\Desktop\\files\\Available.csv";

void Number_0f_processes(FILE *file){
    N=-1; //-1 for removing the header
    char line;
    file = fopen(File_Allocation,"r");

    if (file == NULL) {
        printf("Error opening the file.\n");

    }

    // Read and print each line of the file
    while ((line = fgetc(file)) != EOF) {
        if(line == '\n')
            N++;

    }
    fclose(file);

}
int Number_0f_Resources(FILE *file){
    R = 0;
    char line;
    file = fopen(File_Allocation,"r");

    if (file == NULL) {
        printf("Error opening the file.\n");
    }

    // Read and print each line of the file
    while ((line = fgetc(file)) != EOF ) {
        if(line == '\n')
            break;
        if(line == ',')
            R++;

    }
    fclose(file);

}

void Initialize(struct process *processes,FILE *file){
    char line;
    int i = -1;
    int j = -1;
    int skip = 0; // for skipping first line
    int ON =0;
    file = fopen(File_Allocation,"r");
    if (file == NULL) {
        printf("Error opening the file.\n");
    }

    // Read from file then write the data on struct process
    while ((line = fgetc(file)) != EOF) {
        if(line == '\n') {
            skip = 1;
            i++;
        }
        if(line == ',' && skip) {
            j++;
            ON = 1;
        }
        if(skip && isdigit(line) && ON){
            processes[i].Allocation[j] = line - '0'; // Convert from character to integer
            ON = 0;
        }
        if(j==R) {
            j = 0;
        }
    }
    fclose(file);
    i = -1;
    j = -1;
    skip = 0; // for skipping first line
    ON =0;
    file = fopen(File_Request,"r");
    if (file == NULL) {
        printf("Error opening the file.\n");
    }
    // Read from file then write the data on struct process
    while ((line = fgetc(file)) != EOF) {
        if(line == '\n') {
            skip = 1;
            i++;
        }
        if(line == ',' && skip) {
            j++;
            ON = 1;
        }
        if(skip && isdigit(line) && ON){
            processes[i].Request[j] = line - '0'; // Convert from character to integer
            ON = 0;
        }
        if(j==R) {
            j = 0;
        }
    }
    //Checking if the Dimensions are consistent
    if(N != i)
        printf("!!!!!!Dimensions are not consistent for Processes!!!!!\n");

    fclose(file);
}
void Read_Available(FILE *file,int *array){
    char line;
    int i = 0;
    int ON = 0;
    file = fopen(File_Available,"r");

    if (file == NULL) {
        printf("Error opening the file.\n");
    }
    // Read and print each line of the file
    while ((line = fgetc(file)) != EOF ) {
        if(line == '\n')
            ON = 1;
        if(line == ',' && ON)
            i++;
        if(ON && isdigit(line)){
            array[i] = line - '0';
        }
    }
    //Checking if the Dimensions are consistent
    if(R != i+1)
        printf("!!!!!!Dimensions are not consistent for Resource!!!!!\n");
    fclose(file);

}
int Check(struct process processes,int Available[R]){
    int check = 0;
    for (int i = 0; i < R; ++i) {
        if(processes.Request[i] <= Available[i])
            check = 1;
        else {
            return 0;
        }

    }

    return 1;
}
void Deadlock_Detection(struct process *processes,int Available[R]){
    int Deadlock = 0; // 1 for deadlock  And 0 for no deadlock
    int array[N];   //Saving the processes that didnt have deadlock
    for (int i = 0; i < N; ++i) {
        array[i] = 0;
    }
    int *ptr = array;
    int Finish[N];
    //Initialize vectors with false allocation if not empty and true otherwise
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < R; ++j) {
            if(processes[i].Allocation[j] == 0)
                Finish[i] = 1;
            else {
                Finish[i] = 0;
                break;
            }
        }
    }
    for (int i = 0; i < N; ++i) {
        if(Finish[i]){
            *ptr = i+1;
            ptr++;
        }
    }
    //Finding an index i such that both Finish equals false and request
    //less than or equals Available
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
                if( !Finish[j] && Check(processes[j],Available)) {
                    for (int k = 0; k < R ; ++k) {
                        Available[k] = Available[k] +processes[j].Allocation[k];
                        Finish[j] = 1;

                         }
                    *ptr = j+1;
                    ptr++;
                    }
                }
        }

    //Checking if their is a deadlock or not
    for (int i = 0; i < N; ++i) {
        if(Finish[i] == 0) {
            Deadlock =1;
            printf("DeadLock occurred on those processes : \n");
            break;
        }

    }

    if(Deadlock){
        for (int i = 0; i < N; ++i) {
            if(Finish[i] == 0) {
                printf("P%d ,",i+1);
            }
        }
    }

    if(!Deadlock){
        printf("No Deadlock occurred : The list of processes are : \n");
        for (int i = 0; i < N; ++i) {
            if(array[i] != 0)
                printf("P%d  ,",array[i]);
        }


    }
}
int main() {
    FILE *file;
    Number_0f_processes(file); //Calculate the number of processes
    struct process processes[N];
    Number_0f_Resources(file); //Calculate the number of Resources
    Initialize(processes,file);
    int Available[R];
    Read_Available(file,Available);
    Deadlock_Detection(processes,Available);
    return 0;
}
