#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LEN 150


int glue_two_char(char a, char b);

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
        line[strcspn(line, "\n")] = 0;
        int line_len = strlen(line);
        char first = line[0], second = line[line_len-1];  
        int max_num_pos = 0;
        //printf("starting first = %c, starting second = %c\n\n",first, second);
        for (int i = 1; i<line_len-1;i++){
            if(line[i] > first){
                first = line[i];
                max_num_pos = i;
            } 
        }
        //printf("oh your first number is %c in the position of %d\n\n",first, max_num_pos);
        for (int j = max_num_pos+1; j < line_len; j++){
            if(line[j] > second){
                second = line[j];
            }
        }
        int num =  glue_two_char(first, second);
        total_jolt += num;
        printf("the FINAL number you got is %d\n",num);
    }

    printf("total output joltage is = %d",total_jolt);
    fclose(fp_in);
    return 0;
}

int glue_two_char(char a, char b){
    int result;
    char s[3];
    
    s[0] = a;
    s[1] = b;
    s[2] = '\0';
    
    result = atoi(s);
    return result;
}

