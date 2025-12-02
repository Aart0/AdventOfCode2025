#include <stdlib.h>
#include <stdio.h>
#define MAX_LINE_LEN 10

void read_files(char *argv[], FILE **fp_in);
int to_the_left(int amount, int start_pos, int *counter);
int to_the_right(int amount, int start_pos, int *counter);

int main(int argc, char *argv[]){
    if (argc < 2){
        printf("not enough program arguments!! try again please!\n");
       exit(1);
    }
    
    FILE *fp_in = NULL;
    read_files(argv, &fp_in);
    char line[MAX_LINE_LEN+1];
    int position = 50;
    int zero_counter = 0;
    int actual_zero_hits = 0;

    printf("- The dial starts by pointing at %d.\n", position);

    while (fscanf(fp_in, "%s",line) == 1){
        char direction = line[0];
        int amount = atoi(line + 1);
        //printf("%c - %d\n", direction, amount);
    
        if (direction == 'L'){
            position = to_the_left(amount, position, &zero_counter);
        }

        if (direction == 'R'){
            position = to_the_right(amount, position, &zero_counter);
        }
        
        if (position == 0){
            actual_zero_hits++;
        }

        printf("- The dial is rotated %s to point at %d.\n",line, position);
    }

     
    printf("the amount of 0's is = %d\n",actual_zero_hits);
    printf("the amount of passing the 0 is = %d\n",zero_counter);
    fclose(fp_in);
    return 0;
}

int to_the_left(int amount, int start_pos, int *counter){
     for (int i = 0; i < amount; i++){
       
      if(start_pos == 0){
            (*counter)++;
        }

        start_pos--;
    
        if (start_pos < 0){
            start_pos = 99;
        }

     }

    return start_pos;
}

int to_the_right(int amount, int start_pos, int *counter){
     for (int i = 0; i < amount; i++){
         if(start_pos == 0){
            (*counter)++;
        }

         start_pos++;
    
        if (start_pos > 99){
            start_pos = 0;
        }

     }

    return start_pos;
}


void read_files(char *argv[], FILE **fp_in){

    *fp_in = fopen(argv[1], "r");

    if (*fp_in == NULL){ 
        printf("error opening the files!!!");
        exit(1);
    }
}


