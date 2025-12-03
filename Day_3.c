#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LEN 150

int main(int argc, char *argv[]){
    if (argc < 2){
        printf("Not enough arguments!\n");
        exit(1);
    }
    FILE *fp_in = NULL;
    fp_in = fopen(argv[1], "r");
    if (fp_in == NULL){
        printf("error opening the files!!!");
        exit(1);
    }
     
    int total_jolt = 0;
    char line[MAX_LINE_LEN];

    while(fgets(line, MAX_LINE_LEN, fp_in) != NULL){
        int line_len = strlen(line);
        char first = line[0], second = line[1]; 

        for (int i = 2; i<line_len;i++){
            printf("STEP: %d => first = %c, Second = %c, CURRENT CHAR = %c\n",i,first, second, line[i]);
            if(line[i] > first){
                first = line[i];
                continue;
            } 

            if(line[i] > second){
                second = line[i];
                continue;
            }
        }
    }

    

    fclose(fp_in);
    return 0;
}

