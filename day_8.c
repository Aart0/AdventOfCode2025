#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define BOX_AMOUNT 1000
#define LIMIT 1000
//#define BOX_AMOUNT 20

typedef struct{
    int x,y,z;
}junction_box;

typedef struct{
    int box1, box2;
    double distance;
}edge;

void read_file(int argc, char *argv[], FILE **fp_in);
void initialize_tree(int n, int id[], int sz[]);
int find(int x, int id[]);
int union_sets(int x, int y, int id[], int sz[]);
int compareEdges(const void *a, const void *b); 
int compareInts(const void *a, const void *b);

int main(int argc, char *argv[]){
    FILE *fp_in;
    read_file(argc, argv, &fp_in);
    int id[BOX_AMOUNT], sz[BOX_AMOUNT]; 
    
    junction_box *boxes = malloc(BOX_AMOUNT * sizeof(junction_box));
    if (boxes == NULL){
        printf("memory allocation error!!!\n");
        exit(1);
    }
    int readed_box = 0;
    while(fscanf(fp_in, "%d,%d,%d",&boxes[readed_box].x, &boxes[readed_box].y, &boxes[readed_box].z  ) == 3){
        readed_box++;
    }
    fclose(fp_in);

    int num_of_edges = (readed_box * (readed_box -1)) / 2;
    edge *edges = malloc(num_of_edges * sizeof(edge));
    if (edges == NULL){
        printf("memory allocation error!!!\n");
        exit(1);
    }
    int edge_count = 0;

    for (int i = 0; i < readed_box; i++) {
        for (int j = i + 1; j < readed_box; j++) {
            long long dx = (long long) boxes[i].x - (long long)boxes[j].x;
            long long dy = (long long)boxes[i].y - (long long)boxes[j].y;
            long long dz = (long long)boxes[i].z - (long long)boxes[j].z;
            
            edges[edge_count].box1 = i;
            edges[edge_count].box2 = j;
            edges[edge_count].distance = sqrt((double)(dx*dx + dy*dy + dz*dz));
            edge_count++;
        }
    }
    qsort(edges, num_of_edges, sizeof(edge), compareEdges);
 
    initialize_tree(readed_box, id, sz);
 
    int limit = LIMIT;
    if (edge_count < LIMIT) 
        limit = edge_count;

    for (int i = 0; i < limit; i++){
        union_sets(edges[i].box1, edges[i].box2, id, sz);
    }

    int circuit_sizes[readed_box];
    for (int i = 0; i < readed_box; i++){
        circuit_sizes[i] = 0;  
    }
    for (int i = 0; i < readed_box; i++){
       int root = find(i, id);
       circuit_sizes[root] = sz[root];
    }

    int unique = 0;
    int sizes[readed_box];
    for (int i = 0; i < readed_box; i++){
        if (circuit_sizes[i] > 0){
            sizes[unique++] = circuit_sizes[i];
        }
    }

    qsort(sizes, unique, sizeof(int), compareInts);
    
    printf("\nIn total, there are %d circuits\n", unique);
    printf("Biggest three junction circuits: %d, %d, %d\n", 
           sizes[unique-1], 
           sizes[unique-2], 
           sizes[unique-3]);
    
    long long result = (long long)sizes[unique-1] * (long long)sizes[unique-2] * (long long)sizes[unique-3];
    printf("result: %lld\n", result);

    free(edges);
    free(boxes);
    return 0;
}

int find(int x, int id[]) {
    if (id[x] != x) {
        id[x] = find(id[x], id); 
    }
    return id[x];
}

void initialize_tree(int n, int id[], int sz[]){
    for (int i = 0; i < n;i++){
        id[i] = i;
        sz[i] = 1;
    }
}

int union_sets(int x, int y, int id[], int sz[]){
    int rootX = find(x, id);
    int rootY = find(y, id);

    if (rootX == rootY){
        return 0;
    }

    if(sz[rootX] <= sz[rootY]){
        id[rootX] = rootY;
        sz[rootY] += sz[rootX];
    } 
    else {
        id[rootY] = rootX;
        sz[rootX] += sz[rootY];
    }
    
    return 1;
}

int compareEdges(const void *a, const void *b) {
    edge *e1 = (edge *)a;  
    edge *e2 = (edge *)b; 
    
    if (e1->distance < e2->distance) return -1;  
    if (e1->distance > e2->distance) return 1;  
    return 0;  
}

int compareInts(const void *a, const void *b) {
    int x = *(int *)a;
    int y = *(int *)b;
    return x - y; 
}

void read_file(int argc, char *argv[], FILE **fp_in){
    if (argc < 2){
        printf("Not enough arguments!\n");
        exit(1);
    } 

    *fp_in = fopen(argv[1], "r");
    if (*fp_in == NULL){
        printf("ERROR, opening the file!\n");
        exit(1);
    }
}
