#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_MAX_LEN 50
#define INTERVAL_CAPACITY 200

typedef struct item {
    long long start;
    long long end;
} *interval;

void line_to_interval(char line[LINE_MAX_LEN], interval **interval_list, int counter);
void read_files(char *argv[], FILE **fp_in);

int main(int argc, char *argv[]){
    if (argc < 2){
        printf("NOT ENOUGH ARGUMENTS!\n");
        exit(1);
    } 
    int counter = 0;
    int deliminator_flag = 0;
    interval *interval_list = malloc(INTERVAL_CAPACITY * sizeof(interval));
    if (interval_list == NULL){
            printf("memory allocation error!!\n");
            exit(1);
    }
    int available_ids = 0;

    char line[LINE_MAX_LEN]; 
    FILE *fp_in = NULL;
    read_files(argv, &fp_in);
    
    while(fgets(line, LINE_MAX_LEN,fp_in) != NULL){
        int line_length = strlen(line);
        if (line_length == 1){
            deliminator_flag = 1;
        }
        
        if (deliminator_flag == 0){
            line_to_interval(line, &interval_list, counter);
            counter++; 
        }

        if (deliminator_flag == 1){
            long long num;
            if (fscanf(fp_in, "%lld", &num) == 1){
                for (int j = 0; j < counter; j++){
                    if ((num <= interval_list[j]->end) && (num >=interval_list[j]->start)){
                        available_ids++;
                        printf("this num is available = %lld AND Total IDs = %d\n",num, available_ids);
                        break;
                    }
                }
            }
        }
    }

    printf("---SECOND PART---\n"); // currently NOT WORKING, could take the same ID more than once from different intervals!!!
    long long total_sum = 0;

        
    for (int i = 0; i < counter; i++){
        total_sum = interval_list[i]->end - interval_list[i]->start + 1 + total_sum;
        printf("sum: %lld\n", total_sum);
        free(interval_list[i]);
    }   //freeing up the allocated memory

    free(interval_list);
    fclose(fp_in);

    printf("result of the second part: %lld\n", total_sum);

    return 0;
}

void read_files(char *argv[], FILE **fp_in){
    *fp_in = fopen(argv[1], "r");
    if (*fp_in == NULL){ 
        printf("error opening the files!!!");
        exit(1);
    }
}

void line_to_interval(char line[LINE_MAX_LEN], interval **interval_list, int counter){  
    long long first, last;
    interval data;
    if (sscanf(line, "%lld-%lld",&first, &last) != EOF){
        data = malloc(sizeof(struct item));
        if (data == NULL){
            printf("memory allocation error!!\n");
            exit(1);
        }

        data->start = first;
        data->end = last;
        (*interval_list)[counter] = data;
    }   
}

