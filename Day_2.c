#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE_LEN 10000
#define MAX_NUM_LEN 10000 


void read_files(char *argv[], FILE **fp_in);
void interval_checker(char interval[], long long *invalid_sum);
int main(int argc, char *argv[]){
    if (argc < 2){
        printf("Not enough arguments!\n");
        exit(1);
    }

    FILE *fp_in = NULL;
    read_files(argv, &fp_in);
    char *file_to_str;
    char interval[MAX_LINE_LEN];
    char line[MAX_LINE_LEN];
    long long invalid_sum = 0;
    
    while (fgets(line,MAX_LINE_LEN, fp_in) != NULL){
        line[strcspn(line, "\n")] = 0;
        file_to_str = strtok(line, ",");
 
        while (file_to_str != NULL){
            strcpy(interval, file_to_str);
            interval_checker(interval, &invalid_sum);            
            file_to_str = strtok(NULL, ",");
        }
    }

    printf("\n---total sum = %lld---\n",invalid_sum);

    fclose(fp_in);
    return 0;
}


void interval_checker(char interval[], long long *invalid_sum){
    long long start, end;
    int len, invalid_counter;

    char number_str[MAX_NUM_LEN];
    if (sscanf(interval, "%lld-%lld", &start, &end) == 2){
        invalid_counter = 0;
        for (long long i = start; i <= end; i++){
            sprintf(number_str, "%lld", i);
            len = strlen(number_str);
            if (len % 2 == 0){
                char first_half[MAX_NUM_LEN/2];
                strncpy(first_half, number_str, len/2);
                first_half[len/2] = '\0';
                long long num1 = atoi(first_half);

                char second_half[MAX_NUM_LEN/2];
                strcpy(second_half, number_str + len/2);
                long long num2 = atoi(second_half);

                if (num1 == num2){
                    invalid_counter++;
                    (*invalid_sum) = (*invalid_sum) + i;
                }
            }
        }
    }

   printf("- %lld-%lld has %d invalid IDs\n", start,end,invalid_counter);    

    
}


void read_files(char *argv[], FILE **fp_in){
    *fp_in = fopen(argv[1], "r");
    if (*fp_in == NULL){ 
        printf("error opening the files!!!");
        exit(1);
    }
}


